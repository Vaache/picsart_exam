#include "header.h"

int strlen_2d(const char ** arr) {
    int i = 0;

    while (arr && arr[i])
        i++;
    return i;
}