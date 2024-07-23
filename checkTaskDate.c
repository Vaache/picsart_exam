#include "header.h"

char ** createFailMat(int id) {
    char ** res = (char ** ) malloc(sizeof(char *) * 7);

    res[0] = NULL;
    res[1] = NULL;
    res[2] = strdup("--id");
    char * identify = itoa(id);
    res[3] = strdup(identify);
    res[4] = strdup("--status");
    res[5] = strdup("Fail");

    free(identify);
    return res;
}

void* checkTaskDate(void *arg) {
    FILE * fd = fopen("TaskManager.txt", "r+");
    char buff[1024] = {0};
    int id = 0;

    fgets(buff, sizeof(buff), fd);

    while (fgets(buff, sizeof(buff), fd)) {
        id ++;
        int start = (int)strcspn(buff, ":");
        while (buff[start] && buff[start] == ' ')
            start ++;
        int end = 0;
        int i = 0;
        for (i = start; buff[i] && buff[i] != ' '; ++ i) ;

        end = i;
        char *date = substr(buff, start, end);

        char **mat_Date = split(date, '-');

        const int *tdate = getDate();

        int year = atoi(mat_Date[0]);
        int month = atoi(mat_Date[1]);
        int day = atoi(mat_Date[2]);

        if (tdate[0] != year || tdate[1] != month || tdate[2] != day)
        {
            char **sendArg = createFailMat(id);
            getUpdateTask(sendArg);
            free_2d(sendArg);
        }

        free(date);
        free((void *)tdate);
        free(mat_Date);
    }
    return NULL;
}