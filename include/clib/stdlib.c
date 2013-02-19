#include "../_string.h"

char *_itoa(int value, char *str) {
    int i = 0;
    while(value != 0){
        str[i] = (char)(((int)'0') + (value % 10));
        value /= 10;
        i++;
    }
    str[i] = '\0';
    return reverse(str);
}
