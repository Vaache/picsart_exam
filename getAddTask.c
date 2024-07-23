#include "header.h"

char * err;
const char * title = "--title";
const char * desc  = "--desc";
const char * priority = "--priority";
const char * due = "--due";

void setInfoInFile(Info * info);

bool check_Data(const char *data, Info ** info) {
    char ** arr = split(data, '-');
    if (!arr)
        return false;
    int year = atoi(arr[0]);
    int month = atoi(arr[1]);
    int day = atoi(arr[2]);

    int * tdata = getDate();

    if (year < tdata[0]) {
        err = "You entered an incorrect year date";
    } else if (month < 1 || month > 12 || month < tdata[1]) {
        err = "You entered an incorrect month date";
    } else if (day < 1 || day > 31 || day < tdata[2]) {
        err = "You entered an incorrect day date";
    }
    (*info)->due = strdup(data);
    free_2d(arr, strlen_2d(arr));
    free(tdata);
}

bool getAddTask(const char ** av) {
    Info *info = (Info *)malloc(sizeof(Info));

    info->title = NULL;
    info->description = NULL;
    info->due = NULL;

    for (int i = 2; av[i]; ++ i) {
        if (!strcmp(av[i], title)) {
            info->title = strdup(av[i + 1]);
        } else if (!strcmp(av[i], desc)) {
            info->description = strdup(av[i + 1]);
        } else if (!strcmp(av[i], priority)) {
            if (!strcmp(av[i + 1], "high")) {
                info->priority = HIGHT;
            }  else if (!strcmp(av[i + 1], "medium")) {
                info->priority = MEDIUM;
            } else if (!strcmp(av[i + 1], "low")) {
                info->priority = LOW;
            } else {
                printf("Your Entered Invalid Priority\n");
                remStruct(&info);
                return false;
            }
        } else if (!strcmp(av[i], due)) {
            if (check_Data(av[i + 1], &info)) {
                printf(err);
                remStruct(&info);
                return false;
            }
        }
    }
    setInfoInFile(info);
}

void setInfoInFile(Info * info) {
    
}