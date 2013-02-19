#include <types.h>
#include "include/i386.h"
#include "include/idt.h"
#include "include/pic.h"
#include <_printf.h>

#pragma pack(push,1)

typedef struct{
	u16_t limit;
	void * base;
} treg_t;

struct _idt {
	u16_t low;
	u16_t selector;
	u16_t flags;
	u16_t high;
};

struct registers{
	u16_t ss,gs,fs,es,ds;
    u32_t 
        edi, esi, edx, ecx, ebx, eax, ebp, esp,
        N, errorcode,
        eip, cs, eflags;
	u16_t old_esp, old_ss, old_es, old_ds, olds_fs, old_gs;
};

#pragma pack(pop)

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


struct _idt idt[48];

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
				   isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19,
				   isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28,
				   isr29, isr30, isr31, isr32, isr33, isr34, isr35, isr36, isr37,
				   isr38, isr39, isr40, isr41, isr42, isr43, isr44, isr45, isr46, isr47};
	for(i = 0; i < 48; i++)
		i386_set_gate(i, (unsigned)isrs[i], 0x08, 0x8E00);
	i386_idt_install((void *)idt , sizeof(idt));
}
 
void i386_handle_exception(struct registers *reg) {
	if(reg->N < 32){
		_printf("%d. System has beed halted. ", exceptions[reg->N]);
		for(;;);
	}else if(reg->N < 48){
		PIC_EOI(reg->N);
	}
}

