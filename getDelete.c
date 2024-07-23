#include "header.h"

extern const char *id;

bool getDeleteTask(char **av) {
    if (strcmp(av[2], id) != 0) {
        return false;
    }

    FILE *fd = fopen("TaskManager.txt", "r");
    if (fd == NULL) {
        perror("Error opening TaskManager.txt");
        return false;
    }


    char buff[1024] = {0};


    if (fgets(buff, sizeof(buff), fd) == NULL) {
        perror("Error reading number of tasks");
        fclose(fd);
        return false;
    }
    buff[strcspn(buff, "\n")] = '\0';
    int lcount = atoi(buff);

    int idToDelete = atoi(av[3]);
    if (lcount < idToDelete) {
        fclose(fd);
        dprintf(1, "Invalid ID !!!\n");
        return false;
    }
    int nfd = open("new.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (nfd < 0) {
        perror("Error opening new.txt");
        fclose(fd);
        return false;
    }

    dprintf(nfd, "%s\n", buff);
    int lineIndex = 1;
    while (fgets(buff, sizeof(buff), fd) != NULL) {
        if (lineIndex != idToDelete) {
            dprintf(nfd, "%s", buff);
        }
        lineIndex++;
    }

    fclose(fd);
    close(nfd);

    if (remove("TaskManager.txt") != 0) {
        perror("remove");
        return false;
    }
    if (rename("new.txt", "TaskManager.txt") != 0) {
        perror("rename");
        return false;
    }

    printf("Task deleted successfully.\n");
    return true;
}
