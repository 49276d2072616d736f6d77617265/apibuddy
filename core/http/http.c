#include "http/http.h"
#include "libc/string.h"
#include "libc/sys.h"
#include "libc/print.h"
#include "libc/num.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define REQ_BUF 1024
#define RES_BUF 8192

static const char *method_str(enum http_method m) {
    switch (m) {
        case HTTP_GET: return "GET";
        case HTTP_POST: return "POST";
        case HTTP_PUT: return "PUT";
        case HTTP_DELETE: return "DELETE";
        case HTTP_PATCH: return "PATCH";
        case HTTP_HEAD: return "HEAD";
    }
    return "GET";
}

static int parse_status(const char *buf, int len) {
    if (len < 12) return -1;
    return (buf[9]-'0')*100 + (buf[10]-'0')*10 + (buf[11]-'0');
}

int http_request(
    enum http_method method,
    const char *ip,
    const char *host,
    int port,
    const char *path,
    const char *body,
    int body_len,
    struct http_response *resp
) {
    int sock;
    struct sockaddr_in addr;
    static char req[REQ_BUF];
    static char res[RES_BUF];
    int len = 0, r, total = 0;
    int content_len = -1;
    int header_end = -1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return -1;
    }

    /* ==== REQUEST ==== */

    const char *m = method_str(method);

    b_memcpy(req+len, m, b_strlen(m)); len += b_strlen(m);
    b_memcpy(req+len, " ", 1); len++;
    b_memcpy(req+len, path, b_strlen(path)); len += b_strlen(path);
    b_memcpy(req+len, " HTTP/1.1\r\n", 11); len += 11;

    b_memcpy(req+len, "Host: ", 6); len += 6;
    b_memcpy(req+len, host, b_strlen(host)); len += b_strlen(host);
    b_memcpy(req+len, "\r\n", 2); len += 2;

    if (body && body_len > 0) {
        b_memcpy(req+len, "Content-Length: ", 16); len += 16;
        len += b_itoa(body_len, req+len);
        b_memcpy(req+len, "\r\n", 2); len += 2;
    }

    b_memcpy(req+len, "Connection: close\r\n\r\n", 21); len += 21;

    if (body && body_len > 0) {
        b_memcpy(req+len, body, body_len);
        len += body_len;
    }

    sys_write(sock, req, len);

    /* ==== RESPONSE: HEADERS ==== */

    while ((r = read(sock, res+total, RES_BUF-total)) > 0) {
        total += r;

        for (int i = 0; i < total-3; i++) {
            if (res[i]=='\r'&&res[i+1]=='\n'&&
                res[i+2]=='\r'&&res[i+3]=='\n') {
                header_end = i + 4;
                goto headers_done;
            }
        }
    }

headers_done:

    if (header_end < 0) {
        close(sock);
        return -1;
    }

    /* ==== PARSE CONTENT-LENGTH ==== */

    char *cl = b_strstr(res, "Content-Length:");
    if (cl) {
        cl += 15;
        while (*cl == ' ') cl++;
        content_len = b_atoi(cl);
    } else {
        content_len = 0;
    }

    /* ==== READ BODY ==== */

    int body_read = total - header_end;

    while (body_read < content_len && total < RES_BUF) {
        r = read(sock, res+total, RES_BUF-total);
        if (r <= 0) break;
        total += r;
        body_read += r;
    }

    close(sock);

    /* ==== RESPONSE STRUCT ==== */

    resp->raw = res;
    resp->raw_len = total;
    resp->status = parse_status(res, total);
    resp->body = res + header_end;
    resp->body_len = content_len;

    return 0;
}

