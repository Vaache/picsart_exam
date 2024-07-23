#include "header.h"

void getViewTask() {
    FILE *fd = fopen("TaskManager.txt", "r");
    char buff[1024] = {0};

    fgets(buff, sizeof(buff), fd);


    while (fgets(buff, sizeof(buff), fd))
        dprintf(1, "%s", buff);
    printf("Tasks are listed in order of priority.\n");
    return ;
}