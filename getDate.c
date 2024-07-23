#include "header.h"

const int* getDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int* data = (int*)malloc(3 * sizeof(int));
    if (data == NULL) {
        perror("malloc");
        return NULL;
    }
    
    data[0] = tm.tm_year + 1900;
    data[1] = tm.tm_mon + 1;
    data[2] = tm.tm_mday;

    return data;
}