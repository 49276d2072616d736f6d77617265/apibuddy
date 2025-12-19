#include "markdown/markdown.h"
#include "libc/print.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 5) {
        b_printf("Usage: %s <file.md> <IP> <host> <port>\n", argv[0]);
        return 1;
    }

    const char *md_path = argv[1];
    const char *ip = argv[2];
    const char *host = argv[3];
    int port = atoi(argv[4]);

    // Read the .md file
    FILE *f = fopen(md_path, "r");
    if (!f) {
        b_printf("Error opening file: %s\n", md_path);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc(fsize + 1);
    if (!buf) {
        fclose(f);
        b_printf("Memory error\n");
        return 1;
    }

    fread(buf, 1, fsize, f);
    buf[fsize] = 0;
    fclose(f);

    // Execute parsing
    parse_readme(buf, ip, host, port);

    free(buf);
    return 0;
}
