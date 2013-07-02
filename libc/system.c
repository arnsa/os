#include "../include/types.h"

inline void outb(u16_t port, u8_t value) {
	asm volatile("outb %0, %1"::"a"(value), "Nd"(port));
}

inline char inb(u16_t port) {
	u8_t value;
	asm volatile("inb %1, %0":"=a"(value):"Nd"(port));
	return value;
}

inline void io_wait(void) {
	asm volatile("outb %%al, $0x80"::"a"(0));
}

inline void i386_cli(void) {
	asm("cli");
}

inline void i386_sti(void) {
	asm("sti");
}

inline void i386_hlt(void) {
	asm("hlt");
}
