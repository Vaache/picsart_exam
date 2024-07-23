#include "header.h"

const char * add = "add";
const char * view = "view";
const char * update = "update";
const char * delete = "delete";

extern char *title;
extern char *desc;
extern char *priority;
extern char *due;
pthread_t t1,t2;

int main(int ac, char **av) {
    pthread_create(&t1, NULL, checkTaskDate, NULL);
    pthread_join(t1, NULL);

    if (ac <= 1) {
        printf("Pleas Enter Command!!!\n");
        exit (1);
    }

    if (ac == 10 && !strcmp(av[1], add) && !strcmp(av[2], title) && !strcmp(av[4], desc)\
        && !strcmp(av[6], priority) && !strcmp(av[8], due)) {
        if (getAddTask(av) == false) {
            return 1;
        }
    }
    else if (ac == 3 && !strcmp(av[1], view) && !strcmp(av[2], "--all")) {
            getViewTask();
    } else if (!strcmp(av[1], update) && ac == 6) {
        if (getUpdateTask(av) == false) {
            return 1;
        }
    } else if (!strcmp(av[1], delete) && ac == 4) {
        if (getDeleteTask(av) == false) {
            return 1;
        }
    }
    else {
        printf("Your Entered Invalid Command!!!\n");
        return 1;
    }
    pthread_create(&t2, NULL, info_sort, NULL);
    pthread_join(t2, NULL);
    return 0;
}