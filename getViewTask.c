#include "header.h"

void getViewTask() {
    FILE *fd = fopen("TaskManager.txt", "r");
    char buff[1024] = {0};

    fgets(NULL, 0, fd);


    while (fgets(buff, sizeof(buff), fd))
        dprintf(1, "%s", buff);
    return ;
}