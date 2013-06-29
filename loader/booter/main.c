#include "include/i386.h"
#include "include/pic.h"
#include "include/rtc.h"
#include <_printf.h>
#include <system.h>

int kmain(int argc, char **argv) {
	pic_init();
	i386_isrs_install();	
	rtc_init();
	i386_sti();
	for(;;)
	return 0;
}
