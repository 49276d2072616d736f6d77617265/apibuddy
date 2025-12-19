#include "libc/print.h"
#include "libc/sys.h"
#include "libc/string.h"
#include "markdown/markdown.h"

#define README_PATH "TEST.md"

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    char buf[8192];
    int fd;
    int n;

    b_println("API Buddy starting...");

    fd = sys_open(README_PATH);
    if (fd < 0) {
        b_println("Failed to open README");
        return 1;
    }

    n = sys_read(fd, buf, sizeof(buf)-1);
    sys_close(fd);

    buf[n] = 0;

    parse_readme(buf, "192.168.0.157", "localhost", 80);

    return 0;
}
