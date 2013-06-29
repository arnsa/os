#include <types.h>
#include <system.h>
#include "include/pic.h"
#include "include/rtc.h"

#define PIC_MASTERC	0x20
#define PIC_MASTERD 0x21
#define PIC_SLAVEC	0xA0
#define PIC_SLAVED	0xA1

void pic_eoi(u32_t N) {
	if((N-32) >= 8){
		outb(PIC_SLAVEC, 0x20);
		outb(PIC_MASTERC, 0x20);	
	}else
		outb(PIC_MASTERC, 0x20);
}

void pic_init(void) {
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
