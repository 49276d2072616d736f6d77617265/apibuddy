#include "libc/print.h"
#include "libc/string.h"
#include "libc/sys.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int http_get(const char *ip, const char *host, int port, const char *path) {
    int sock;
    struct sockaddr_in addr;
    char buf[1024];
    char req[512];
    int len = 0;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        b_println("socket failed");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        b_println("connect failed");
        close(sock);
        return -1;
    }

    /* ===== REQUEST HTTP 100% VÁLIDO ===== */

    memcpy(req + len, "GET ", 4); len += 4;
    memcpy(req + len, path, strlen(path)); len += strlen(path);
    memcpy(req + len, " HTTP/1.1\r\n", 11); len += 11;

    memcpy(req + len, "Host: ", 6); len += 6;
    memcpy(req + len, host, strlen(host)); len += strlen(host);
    memcpy(req + len, "\r\n", 2); len += 2;

    memcpy(req + len, "User-Agent: api-buddy/0.1\r\n", 28); len += 28;

    memcpy(req + len, "Connection: close\r\n", 19); len += 19;

    memcpy(req + len, "\r\n", 2); len += 2;

    /* =================================== */

    write(sock, req, len);

    b_println("=== RESPONSE ===");

    int r;
    while ((r = read(sock, buf, sizeof(buf))) > 0) {
        sys_write(1, buf, r);
    }

    close(sock);
    return 0;
}
