#include "libc/num.h"

int b_atoi(const char *s) {
    int r = 0;
    while (*s >= '0' && *s <= '9') {
        r = r * 10 + (*s - '0');
        s++;
    }
    return r;
}

int b_itoa(int v, char *buf) {
    char tmp[16];
    int i = 0, neg = 0;

    if (v < 0) {
        neg = 1;
        v = -v;
    }

    do {
        tmp[i++] = '0' + (v % 10);
        v /= 10;
    } while (v);

    if (neg) tmp[i++] = '-';

    int j = 0;
    while (i--) buf[j++] = tmp[i];
    buf[j] = 0;

    return j;
}

int b_utoa(unsigned int v, char *buf) {
    char tmp[16];
    int i = 0;

    do {
        tmp[i++] = '0' + (v % 10);
        v /= 10;
    } while (v);

    int j = 0;
    while (i--) buf[j++] = tmp[i];
    buf[j] = 0;

    return j;
}

int b_utohex(unsigned long v, char *buf) {
    const char *hex = "0123456789abcdef";
    char tmp[16];
    int i = 0;

    do {
        tmp[i++] = hex[v & 0xf];
        v >>= 4;
    } while (v);

    buf[0] = '0';
    buf[1] = 'x';

    int j = 2;
    while (i--) buf[j++] = tmp[i];
    buf[j] = 0;

    return j;
}
