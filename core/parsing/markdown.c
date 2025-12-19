#include "markdown/markdown.h"
#include "libc/string.h"
#include "libc/print.h"
#include "http/http.h"
#include "libc/base.h"

#define MAX_HEADERS 16
#define BODY_BUF 8192

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
        /* skip empty lines and markdown headers */
        while (*p == '\n' || *p == '\r') p++;
        if (!*p) break;
        if (*p == '#') { while (*p && *p != '\n') p++; continue; }

        /* ==== parse method and path ==== */
        char *line = p;
        char *line_end = b_strchr(p, '\n');
        if (!line_end) break;
        *line_end = 0;
        p = line_end + 1;

        char *sp = b_strchr(line, ' ');
        if (!sp) continue;

        *sp = 0;
        char *method_str = line;
        char *path = sp + 1;

        /* trim trailing spaces */
        char *end = method_str + b_strlen(method_str) - 1;
        while (end > method_str && (*end == '\r' || *end == ' ')) { *end = 0; end--; }
        end = path + b_strlen(path) - 1;
        while (end > path && (*end == '\r' || *end == ' ')) { *end = 0; end--; }

        enum http_method method = parse_method(method_str);

        /* ==== parse headers ==== */
        struct http_header headers[MAX_HEADERS];
        int headers_count = 0;

        while (*p) {
            while (*p == '\n' || *p == '\r') p++;
            if (!*p) break;

            if (b_strncmp(p, "Header:", 7) == 0 && headers_count < MAX_HEADERS) {
                char *h_start = p + 7;
                while (*h_start == ' ' || *h_start == '\t') h_start++;

                if (*h_start == '\'') {
                    h_start++;
                    char *h_end = b_strchr(h_start, '\'');
                    if (!h_end) break;

                    *h_end = 0;
                    char *colon = b_strchr(h_start, ':');
                    if (colon) {
                        *colon = 0;
                        headers[headers_count].name = h_start;
                        headers[headers_count].value = colon + 1;
                        while (*(headers[headers_count].value) == ' ') headers[headers_count].value++;
                        headers_count++;
                    }

                    p = h_end + 1;
                    while (*p && *p != '\n') p++;
                    if (*p == '\n') p++;
                    continue;
                }
            }
            break; /* not a header */
        }

        /* ==== parse body ==== */
        static char body_buf[BODY_BUF];
        int body_len = 0;

        while (*p) {
            while (*p == '\n' || *p == '\r' || *p == ' ' || *p == '\t') p++;
            if (!*p) break;

            char *block_start = NULL;
            char *block_end = NULL;

            if (*p == '\'') { /* quoted block */
                block_start = p + 1;
                block_end = b_strchr(block_start, '\'');
                if (!block_end) break;
                /* do NOT zero out the closing quote */
                int blen = block_end - block_start;
                if (body_len + blen < BODY_BUF) {
                    b_memcpy(body_buf + body_len, block_start, blen);
                    body_len += blen;
                    body_buf[body_len++] = '\n';
                }
                p = block_end + 1;
            } else if (*p == '{') { /* json block */
                block_start = p;
                block_end = p;
                int braces = 0;
                while (*block_end) {
                    if (*block_end == '{') braces++;
                    else if (*block_end == '}') braces--;
                    block_end++;
                    if (braces == 0) break;
                }
                if (braces != 0) break; // malformed JSON
                /* include the closing } */
                int blen = block_end - block_start;
                if (body_len + blen < BODY_BUF) {
                    b_memcpy(body_buf + body_len, block_start, blen);
                    body_len += blen;
                    body_buf[body_len++] = '\n';
                }
                p = block_end;
            } else break;
        }

        char *body = (body_len > 0) ? body_buf : NULL;

        /* ==== make HTTP request ==== */
        struct http_response resp;
        http_request(method, ip, host, port, path, body, body_len, headers, headers_count, &resp);

        /* ==== log request ==== */
        b_printf("[%s] %s -> %d\n", method_str, path, resp.status);
    }
}
