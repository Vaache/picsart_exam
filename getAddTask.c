#include "header.h"

char * err;
const char * title = "--title";
const char * desc  = "--desc";
const char * priority = "--priority";
const char * due = "--due";

void setInfoInFile(Info * info);

bool check_Data(char *data, Info ** info) {
    char ** arr = split(data, '-');
    if (!arr)
        return false;
    int year = atoi(arr[0]);
    int month = atoi(arr[1]);
    int day = atoi(arr[2]);

    const int * tdata = getDate();

    if (year < tdata[0]) {
        err = "You entered an incorrect year date";
        free_2d(arr);
        free((void *)tdata);
        return false;
    } else if (month < 1 || month > 12 || month < tdata[1]) {
        err = "You entered an incorrect month date";
        free_2d(arr);
        free((void *)tdata);
        return false;
    } else if (day < 1 || day > 31 || day < tdata[2]) {
        err = "You entered an incorrect day date";
        free_2d(arr);
        free((void *)tdata);
        return false;
    }
    (*info)->due = strdup(data);
    free_2d(arr);
    free((void *)tdata);
    return true;
}

bool getAddTask(char ** av) {
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
                info->priority = HIGH;
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
            if (!check_Data(av[i + 1], &info)) {
                printf("%s\n", err);
                remStruct(&info);
                return false;
            }
        }
    }
    setInfoInFile(info);
    return true;
}

void setInfoInFile(Info * info) {
    int fd = open("TaskManager.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("open");
        remStruct(&info);
        exit (1);
    }
    int lcount;

    char buff[10] = {0};
    if (read(fd, buff, sizeof(buff)) <= 0) {
        write(fd, "1\n", 2);
        lcount = 1;
    } else {
        lseek(fd, 0, SEEK_SET);
        read(fd, buff, sizeof(buff));
        int i = 0;
        while (buff[i] && buff[i] != '\n')
            ++ i;
        buff[i] = '\0';

        lcount = atoi(buff) + 1;
        char *tmp = itoa(lcount);

        lseek(fd, 0, SEEK_SET);
        write(fd, tmp, my_strlen(tmp));
        lseek(fd, 0, SEEK_END);
        
        free(tmp);
    }

    char *prio = getPrio(info->priority);
    dprintf(fd, "%d. %s [%s] Due: %s Status: Pending\n", lcount, info->title, \
                prio, info->due);
    dprintf(1, "Task added successfully");
    free(prio);
    return ;
}
/*

taskmanager add --title "Submit Assignment" --desc "Submit by Friday" --priority high --due "2023-12-31"

1. Finish Project [High] Due: 2023-11-30 Status: Pending
2. Submit Assignment [High] Due: 2023-12-31 Status: Pending
3. Email Advisor [Medium] Due: 2023-10-15 Status: Completed
Tasks are listed in order of priority.

*/