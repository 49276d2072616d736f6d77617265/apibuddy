#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include "types.h"

ssize_t b_strlen(const char *s);
int     b_strcmp(const char *a, const char *b);
int     b_strncmp(const char *a, const char *b, ssize_t n);
char   *b_strchr(const char *s, int c);
char   *b_strstr(const char *h, const char *n);

void   *b_memcpy(void *dst, const void *src, ssize_t n);
void   *b_memset(void *dst, int c, ssize_t n);

#endif
