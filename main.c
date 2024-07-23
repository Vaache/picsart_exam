#include "header.h"

// taskmanager add --title "Submit Assignment" --desc "Submit by Friday" --priority high --due "2023-12-31"

const char * add = "add";
const char * view = "view";
const char * update = "update";
const char * delete = "delete";

int main(int ac, char **av) {

    if (ac <= 1) {
        printf("Pleas Enter Command!!!\n");
        exit (1);
    }

    if (!strcmp(av[1], add) && ac == 10) {
        if (getAddTask(av) == false) {
            return 1;
        }
    } else if (!strcmp(av[1], view) && ac == 3) {
        if (getViewTask(av) == false) {
            return 1;
        }
    } else if (!strcmp(av[1], update) && ac == 6) {
        if (getUpdateTask(av) == false) {
            return 1;
        }
    } else if (!strcmp(av[1], delete) && ac == 4) {
        if (getDeleteTask(av) == false) {
            return 1;
        }
    } else {
        printf("Your Entered Invalid Command!!!\n");
        return 1;
    }


    return 0;
}