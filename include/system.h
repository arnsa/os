#ifndef SYSTEM_H
#define SYSTEM_H

inline void outb(u16_t, u8_t);
inline char inb(u16_t port);
inline void io_wait(void);
inline void i386_cli(void);
inline void i386_sti(void);
inline void i386_hlt(void);

#endif
