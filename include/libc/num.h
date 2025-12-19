#ifndef LIBC_NUM_H
#define LIBC_NUM_H

int  atoi(const char *s);
void itoa(int v, char *buf);
void utoa(unsigned int v, char *buf);
void utohex(unsigned long v, char *buf);

#endif
