#include <stdarg.h>
#include "../_stdlib.h"

unsigned short *screen = (unsigned short *)0xB8000;
unsigned long screen_idx = 0;

void _putch(char const ch) {
    screen[screen_idx++] = ch | 0x700;
}

char *dectohex(unsigned num) {
	char const hex[16] = "0123456789ABCDEF";
	static char str[128];
	char *s = str;
	_memset(str, 0, sizeof(str));

	while(num > 0){
		*s++ = hex[num % 16];
		num /= 16;
	}
	reverse(str);
	return str;
}

void _printf(const char *format, ...) {
	char _str[256], *str = _str;
	va_list ap;
	va_start(ap, format);
	unsigned char x = 0, y = 0, type = 0;

	while(*format) {
		if(*format == '%'){
			type = 1;
			format++;
			continue;
		}else if(*format == '\n'){
			while(x < 80){
				_putch(' ');
				x++;
			}
			format++;
			continue;
		}else if(type){
			type = 0;
			switch(*format){
				case 's':
					_memset(_str, 0, sizeof(_str));
					_strcpy(_str, va_arg(ap, char *));
					str = _str;
					while(*str){
						_putch(*str++);
                        x++;
                        if(x >= 80)
                            x = 0;
                    }
					break;
				case 'd':
					_memset(_str, 0, sizeof(_str));
					_itoa(va_arg(ap, int), _str);
					str = _str;
					while(*str){
						_putch(*str++);
                        x++;
                        if(x >= 80)
                            x = 0;
                    }
					break;
				case 'x':
					_memset(_str, 0, sizeof(_str));
					_strcpy(_str, dectohex(va_arg(ap, int)));
					str = _str;
					_putch('0');
					_putch('x');
					if(x < 78)
						x += 2;
					else
						x = 0;
					while(*str){
						_putch(*str++);
                        x++;
                        if(x >= 80)
                            x = 0;
                    }
					break;
				default:
					_putch('%');
					_putch(*format);
					if(x < 78)
						x += 2;
					else
						x = 0;
					break;
			}
			format++;
		}else{
			x++;
			_putch(*format);
			format++;
		}
	}
	va_end(ap);
}

void init_printf(char *str) {
	unsigned char y = (*(unsigned char *)0x450) + 1;
	screen_idx += (y * 80);
	_printf("%s", str);
}
