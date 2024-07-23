#include "header.h"

Info* readTasksFromFile(const char* filename, int* taskCount);
void sortTasksByPriority(Info* tasks, int taskCount);
void writeTasksToFile(const char* filename, Info* tasks, int taskCount);
void freeTasks(Info* tasks, int taskCount);
lvl parsePriority(const char* priorityStr);

void* info_sort(void * arg) {
    const char* filename = "TaskManager.txt";
    int taskCount = 0;

    Info* tasks = readTasksFromFile(filename, &taskCount);

    if (tasks == NULL) {
        return NULL;
    }

    sortTasksByPriority(tasks, taskCount);

    writeTasksToFile(filename, tasks, taskCount);

    freeTasks(tasks, taskCount);

    return NULL;
}

Info* readTasksFromFile(const char* filename, int* taskCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    char line[1024] = {0};

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return NULL;
    }
    if (sscanf(line, "%d", taskCount) != 1) {
        fclose(file);
        return NULL;
    }

    Info* tasks = malloc(*taskCount * sizeof(Info));
    if (tasks == NULL) {
        fclose(file);
        return NULL;
    }

    int actualTaskCount = 0;

    for (int i = 0; i < *taskCount; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            freeTasks(tasks, actualTaskCount);
            fclose(file);
            return NULL;
        }
        char **arr = split(line, ' ');
        char *title = strjoin(arr[1], " ", 0);
        title = strjoin(title, arr[2], 1);
        char *trimed = strtrim(arr[3], "[]");
        char *priorityStr = trimed;
        char *due = strdup(arr[5]);
        char *status = strdup(arr[7]);

        tasks[actualTaskCount].title = strdup(title);
        tasks[actualTaskCount].due = strdup(due);
        tasks[actualTaskCount].priority = parsePriority(priorityStr);
        tasks[actualTaskCount].status = strdup(status);

        free_2d(arr);
        free(title);
        free(due);
        free(status);
        actualTaskCount++;
    }

    *taskCount = actualTaskCount;
    fclose(file);
    return tasks;
}

void sortTasksByPriority(Info* tasks, int taskCount) {
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = i + 1; j < taskCount; j++) {
            if (tasks[i].priority > tasks[j].priority) {
                Info temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

void writeTasksToFile(const char* filename, Info* tasks, int taskCount) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        // perror("fopen");
        return;
    }

    fprintf(file, "%d\n", taskCount);

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d. %s [%s] Due: %s Status: %s", i + 1, tasks[i].title,
                tasks[i].priority == HIGH ? "High" :
                tasks[i].priority == MEDIUM ? "Medium" : "Low",
                tasks[i].due, tasks[i].status);
    }

    fclose(file);
}

void freeTasks(Info* tasks, int taskCount) {
    for (int i = 0; i < taskCount; i++) {
        free(tasks[i].title);
        free(tasks[i].due);
        free(tasks[i].status);
    }
    free(tasks);
}

lvl parsePriority(const char* priorityStr) {
    if (strcmp(priorityStr, "High") == 0) {
        return HIGH;
    } else if (strcmp(priorityStr, "Medium") == 0) {
        return MEDIUM;
    } else {
        return LOW;
    }
}
