#include <types.h>
#include "include/pic.h"

#define PIC_MASTERC	0x20
#define PIC_MASTERD 0x21
#define PIC_SLAVEC	0xA0
#define PIC_SLAVED	0xA1


static void outb(u16_t port, u8_t value) {
    asm volatile("outb %0, %1"::"a"(value), "Nd"(port));
}

static char inb(u16_t port) {
	u8_t value;
	asm volatile("inb %1, %0":"=a"(value):"Nd"(port));
	return value;
}

static inline void io_wait(void) {
	asm volatile("outb %%al, $0x80"::"a"(0));
}

void PIC_EOI(u32_t N) {
	if((N-32) > 8)
		outb(PIC_SLAVEC, 0x20);
	else
		outb(PIC_MASTERC, 0x20);
}

void init_PIC(void) {
	outb(PIC_MASTERC, 0x11);
	io_wait();
	outb(PIC_SLAVEC, 0x11);
	io_wait();
	outb(PIC_MASTERD, 0x20);
	io_wait();
	outb(PIC_SLAVED, 0x28);
	io_wait();
	outb(PIC_MASTERD, 0x04);
	io_wait();
	outb(PIC_SLAVED, 0x02);
	io_wait();
	outb(PIC_MASTERD, 0x01);
	io_wait();
	outb(PIC_SLAVED, 0x01);
	io_wait();
	outb(PIC_MASTERD, 0x00);
	io_wait();
	outb(PIC_SLAVED, 0x00);
	io_wait();
}
