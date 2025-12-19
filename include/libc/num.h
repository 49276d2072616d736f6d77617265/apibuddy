#ifndef LIBC_NUM_H
#define LIBC_NUM_H

int  b_atoi(const char *s);
int b_itoa(int v, char *buf);
int b_utoa(unsigned int v, char *buf);
int b_utohex(unsigned long v, char *buf);

#endif
