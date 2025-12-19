#include "libc/print.h"

int http_get(const char *ip, const char *host, int port, const char *path);

int main() {
    b_println("API Buddy starting...");

    http_get(
        "192.168.0.157",
        "localhost",
        80,
        "/"
    );

    return 0;
}

