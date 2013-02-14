#include "include/i386_idt.h"
#include "../include/stdio.h"

char const * exceptions[32] = {"Divide Error Exception",
            "Debug Exception",
            "NMI Interrupt",
            "Breakpoint Exception",
            "Overflow Exception",
            "Bound Range Exceed Exception",
            "Invalid Opcode Exception",
            "Devict Not Available Exception",
            "Double Fault Exception",
            "Coprocessor Segment Overrun",
            "Invalid TSS Exception",
            "Segment Not Present",
            "Stack Fault Exception",
            "General Protection Exception",
            "Page Fault Exception",
            "x87 FPU Floating-Point Error",
            "Alignment Check Exception",
            "Machine-Check Exception",
            "SIMD Floating-Point Exception"
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved"} ;

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);

struct _idt idt[19];

void i386_idt_install(void * base, u16_t limit) {
	treg_t idtr = {limit,base};
	asm("lidt %0" :: "m"(idtr));
}

void i386_set_gate(u8_t N, u32_t address, u16_t selector, u16_t flags) {
	idt[N].selector = selector;
	idt[N].flags = flags;
	idt[N].low = address & 0xFFFF;
	idt[N].high = (address >> 16) & 0xFFFF;
} 

void i386_isrs_install(void) {
	u8_t i;
	void (*isrs[])(void) = {isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9,
				   isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18};
	for(i = 0; i < 19; i++)
		i386_set_gate(i, (unsigned)isrs[i], 0x08, 0x8E00);
}

void i386_handle_exception(struct registers *reg) {
	if(reg->N < 32){
		print(exceptions[reg->N]);
		print(". System has beed halted.");
		for(;;);
	}
}

int main(int argc, char **argv) {
	i386_isrs_install();
	i386_idt_install((void *)idt , sizeof(idt));
	for(;;);
	return 0;
}
