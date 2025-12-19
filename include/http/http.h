#ifndef CORE_HTTP_H
#define CORE_HTTP_H

enum http_method {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE,
    HTTP_PATCH,
    HTTP_HEAD
};

struct http_response {
    int status;
    char *body;
    int body_len;
    char *raw;
    int raw_len;
};

int http_request(
    enum http_method method,
    const char *ip,
    const char *host,
    int port,
    const char *path,
    const char *body,
    int body_len,
    struct http_response *resp
);

#endif
