#include "header.h"

int my_strlen(char *str) {
    int i = 0;
    while (str && str[i])
        i++;
    return i;
}