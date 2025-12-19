#include "libc/sys.h"

#include <unistd.h>
#include <fcntl.h>
#include "libc/string.h"

ssize_t sys_write(int fd, const void *buf, size_t len) {
    return write(fd, buf, len);
}

ssize_t sys_read(int fd, void *buf, size_t len) {
    return read(fd, buf, len);
}

int sys_open(const char *path) {
    return open(path, O_RDONLY);
}

int sys_close(int fd) {
    return close(fd);
}

void sys_exit(int code) {
    _exit(code);
}

ssize_t b_strlen(const char *s) {
    ssize_t len = 0;
    while (*s++) len++;
    return len;
}

void *b_memcpy(void *dst, const void *src, ssize_t n) {
    char *d = dst;
    const char *s = src;
    while (n--) *d++ = *s++;
    return dst;
}

char *b_strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c) return (char*)s;
        s++;
    }
    return NULL;
}

int b_strncmp(const char *a, const char *b, ssize_t n) {
    for (ssize_t i = 0; i < n; i++) {
        if (a[i] != b[i]) return (unsigned char)a[i] - (unsigned char)b[i];
        if (!a[i]) break;
    }
    return 0;
}

char *b_strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    for (; *haystack; haystack++) {
        ssize_t i = 0;
        while (haystack[i] && needle[i] && haystack[i] == needle[i]) i++;
        if (!needle[i]) return (char*)haystack;
    }
    return NULL;
}