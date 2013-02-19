#ifndef _PRINTF_H
#define _PRINTF_H

extern unsigned short *screen;
extern unsigned long screen_idx;

void putch(char const);
char *dectohex(unsigned);
void _printf(const char *, ...);

#endif
