#include "header.h"

const char * id = "--id";
const char * status = "--status";

bool getUpdateTask(char **av) {

    if (strcmp(av[2], id))
        return false;
    if (strcmp(av[4], status))
        return false;
    FILE *fd = fopen("TaskManager.txt", "r+");

    char buff[1024] = {0};

    fgets(buff, sizeof(buff), fd);
    buff[strcspn(buff, "\n")] = '\0';

    int lcount = atoi(buff);
    int id = atoi(av[3]);
    if (lcount < id)
    {
        fclose(fd);
        dprintf(1, "Invalid ID !!!\n");
        return false;
    }
    int nfd = open("new.txt", O_CREAT | O_RDWR, 0644);
    for (int i = 0; i < id; ++ i, fgets(buff, sizeof(buff), fd))
    {
        dprintf(nfd, "%s", buff);
        if (i == 0)
            dprintf(nfd, "\n");
        bzero(buff, sizeof(buff));
    }

    int dot = 0;
    int i = 0;

    while (buff[i]) {
        if (buff[i] == ':')
            dot++;
        if (dot == 2)
        {
            i++;
            break;
        }
        i++;
    }
    while (buff[i] && buff[i] == ' ')
        i++;
    for (int j = 0; av[5][j]; ++ j)
        buff[i++] = av[5][j];
    buff[i++] = '\n';
    buff[i] = '\0';
    if (strcmp(buff, av[4])) {
        dprintf(nfd, "%s", buff);
        bzero(buff, sizeof(buff));
    }
    while (fgets(buff, sizeof(buff), fd))
    {
        dprintf(nfd, "%s", buff);
        bzero(buff, sizeof(buff));
    }

    remove("TaskManager.txt");

    rename("new.txt","TaskManager.txt");
    printf("Task updated successfully.\n");
    return true;
}