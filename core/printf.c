#include "libc/print.h"
#include "libc/string.h"
#include "libc/sys.h"
#include "libc/num.h"

#include <stdarg.h>

/* escreve 1 byte */
void b_putchar(char c) {
    sys_write(1, &c, 1);
}

void b_print(const char *s) {
    sys_write(1, s, b_strlen(s));
}

void b_println(const char *s) {
    b_print(s);
    b_putchar('\n');
}

/* printf mínimo */
void b_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    for (; *fmt; fmt++) {
        if (*fmt != '%') {
            b_putchar(*fmt);
            continue;
        }

        fmt++;
        char buf[32];

        if (*fmt == 's') {
            char *s = va_arg(ap, char*);
            b_print(s);
        } else if (*fmt == 'd') {
            b_itoa(va_arg(ap, int), buf);
            b_print(buf);
        } else if (*fmt == 'u') {
            b_utoa(va_arg(ap, unsigned int), buf);
            b_print(buf);
        } else if (*fmt == 'x') {
            b_utohex(va_arg(ap, unsigned long), buf);
            b_print(buf);
        } else if (*fmt == 'c') {
            b_putchar((char)va_arg(ap, int));
        }
    }

    va_end(ap);
}
