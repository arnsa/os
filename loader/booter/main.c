#include "include/i386.h"
#include "include/pic.h"
#include <_printf.h>

int main(int argc, char **argv) {
	_printf("WORKS!");
	init_PIC();
	i386_isrs_install();	
	asm("sti");
	for(;;);
	return 0;
}
