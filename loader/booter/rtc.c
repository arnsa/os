#include <types.h>
#include <system.h>
#include <_printf.h>
#include "include/pic.h"

static u32_t rtc_timems = 0;

void rtc_init() {
	i386_cli();
	outb(0x70, 0x8B);
	outb(0x70, 0x8B);
	outb(0x71, inb(0x71) | 0x40);
	i386_sti();
}

void rtc_isr() {
	outb(0x70, 0x0C);
	inb(0x71);
	rtc_timems++;
}

u32_t rtc_time() {
	return rtc_timems;
}

void rtc_sleep(u32_t ms) {
	u32_t tmp = rtc_timems	+ ms;
	while(rtc_timems < tmp)
		i386_hlt();
}
