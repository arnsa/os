#include "include/i386.h"
#include "include/pic.h"
#include <_printf.h>

int kmain(int argc, char **argv) {
	init_printf("[CPU] Remapping PIC and enabling interrupts... ");
	init_PIC();
	i386_isrs_install();	
	asm("sti");
	_printf("Done\n");
	for(;;);
	return 0;
}
