unsigned short * screen = (unsigned short *)0xB8000;
unsigned long screen_idx = 0;

void print(char const *str) {
    while(*str){
        screen[screen_idx++] = *str | 0x700;
        ++str;
    }
}

