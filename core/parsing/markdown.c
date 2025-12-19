#include "markdown/markdown.h"
#include "libc/string.h"
#include "libc/print.h"
#include "http/http.h"
#include "libc/base.h"

static enum http_method parse_method(const char *s) {
    if (!b_strncmp(s, "GET", 3))    return HTTP_GET;
    if (!b_strncmp(s, "POST", 4))   return HTTP_POST;
    if (!b_strncmp(s, "PUT", 3))    return HTTP_PUT;
    if (!b_strncmp(s, "DELETE", 6)) return HTTP_DELETE;
    if (!b_strncmp(s, "PATCH", 5))  return HTTP_PATCH;
    if (!b_strncmp(s, "HEAD", 4))   return HTTP_HEAD;
    return -1;
}

void parse_readme(char *buf, const char *ip, const char *host, int port) {
    char *p = buf;

    while (*p) {

        /* skip empty lines and newlines */
        while (*p == '\n' || *p == '\r') p++;

        if (!*p) break;

        /* skip markdown headers */
        if (*p == '#') {
            while (*p && *p != '\n') p++;
            continue;
        }

        /* ==== full line ==== */
        char *line = p;
        char *line_end = b_strchr(p, '\n');
        if (!line_end) break;
        *line_end = 0;

        p = line_end + 1; /* advance cursor */

        /* ==== parse method ==== */
        char *sp = b_strchr(line, ' ');
        if (!sp) continue;

        *sp = 0;
        char *method_str = line;
        char *path = sp + 1;

        /* trim trailing \r or spaces */
        char *end = method_str + b_strlen(method_str) - 1;
        while (end > method_str && (*end == '\r' || *end == ' ')) {
            *end = 0;
            end--;
        }

        end = path + b_strlen(path) - 1;
        while (end > path && (*end == '\r' || *end == ' ')) {
            *end = 0;
            end--;
        }

        enum http_method method = parse_method(method_str);

        /* ==== parse body ==== */
        char *body = NULL;
        int body_len = 0;

        if (*p == '{' || *p == ' ' || *p == '\n') {
            /* skip spaces and newlines */
            while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;

            if (*p == '{') {
                body = p;
                /* find end of body: next line starting with GET/POST/PUT/DELETE or EOF */
                char *b_end = p;
                while (*b_end) {
                    if ((*b_end == 'G' && b_strncmp(b_end, "GET ", 4) == 0) ||
                        (*b_end == 'P' && b_strncmp(b_end, "POST ", 5) == 0) ||
                        (*b_end == 'P' && b_strncmp(b_end, "PUT ", 4) == 0) ||
                        (*b_end == 'D' && b_strncmp(b_end, "DELETE ", 7) == 0) ||
                        (*b_end == 'H' && b_strncmp(b_end, "HEAD ", 5) == 0) ||
                        (*b_end == 'P' && b_strncmp(b_end, "PATCH ", 6) == 0)) {
                        break;
                    }
                    b_end++;
                }
                body_len = b_end - body;
                p = b_end;
            }
        }

        /* ==== make HTTP request ==== */
        struct http_response resp;
        http_request(method, ip, host, port, path, body, body_len, &resp);

        /* ==== log request ==== */
        b_printf("[%s] %s -> %d\n", method_str, path, resp.status);
    }
}
