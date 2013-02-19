void *_memset(void *ptr, int value, unsigned num) {
	unsigned char *pointer = ptr;

	if(ptr != 0 && num > 0)
		while(num){
			*pointer++ = value;
			num--;
		}
	return ptr;
}

char *_strcpy(char *destination, const char *source) {
	while(*source)
		*destination++ = *source++;
	*destination = '\0';
	return destination;
}

unsigned _strlen(const char *str) {
	unsigned i = 0;
	while(*str) {
		i++;
		str++;
	}
	return i;
}

char *reverse(char str[]) {
    unsigned char i;
    unsigned len = _strlen(str), max = len;
    static char reversed[128];

    _memset(reversed, 0, sizeof(reversed));
    for(i = 0; i < max; i++)
        reversed[i] = str[--len];
	_strcpy(str, reversed);
    return reversed;
}
