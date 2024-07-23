#include "header.h"

int strlen_2d(char ** arr) {
    int i = 0;

    while (arr && arr[i])
        i++;
    return i;
}