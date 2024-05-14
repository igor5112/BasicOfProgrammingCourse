#include <stdio.h>

size_t strlen1(char *s) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
};