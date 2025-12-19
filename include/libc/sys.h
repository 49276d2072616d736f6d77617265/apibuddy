#ifndef LIBC_SYS_H
#define LIBC_SYS_H

#include "types.h"

ssize_t sys_write(int fd, const void *buf, size_t len);
ssize_t sys_read(int fd, void *buf, size_t len);
void    sys_exit(int code);
int sys_close(int fd);
int sys_open(const char *path);

#endif
