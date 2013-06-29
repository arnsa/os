#ifndef PIC_H
#define PIC_H

#include "types.h"

void pic_init(void);
void pic_eoi(u32_t);

#define IRQ_TIMER		0
#define IRQ_KEYBOARD	1
#define IRQ_CASCADE		2
#define IRQ_COM2OR4		3
#define IRQ_COM1OR3		4
#define IRQ_LPT2		5
#define IRQ_FDC			6
#define IRQ_LPT1		7
#define IRQ_RTC			8
#define IRQ_PS2_MOUSE	12
#define IRQ_FPU			13
#define IRQ_ATA1		14
#define IRQ_ATA2		15

#endif
