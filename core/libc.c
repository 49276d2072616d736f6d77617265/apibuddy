#include "libc/string.h"
#include "libc/sys.h"

#include <unistd.h>

ssize_t sys_write(int fd, const void *buf, size_t len) {
    return write(fd, buf, len);
}

ssize_t sys_read(int fd, void *buf, size_t len) {
    return read(fd, buf, len);
}

void sys_exit(int code) {
    _exit(code);
}


size_t strlen(const char *s) {
    size_t n = 0;
    while (s[n]) n++;
    return n;
}

int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++; b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

int strncmp(const char *a, const char *b, size_t n) {
    while (n && *a && (*a == *b)) {
        a++; b++; n--;
    }
    if (!n) return 0;
    return *(unsigned char*)a - *(unsigned char*)b;
}

void *memcpy(void *dst, const void *src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    while (n--) *d++ = *s++;
    return dst;
}

void *memset(void *dst, int c, size_t n) {
    unsigned char *d = dst;
    while (n--) *d++ = (unsigned char)c;
    return dst;
}

char *strchr(const char *s, int c) {
    while (*s) {
        if (*s == c) return (char*)s;
        s++;
    }
    return 0;
}
