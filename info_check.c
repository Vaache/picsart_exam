#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        // perror("read");
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
        perror("open");
        return NULL;
    }

    // Allocate memory for line buffer
    char line[256];
    
    // Read the number of tasks from the first line
    if (fgets(line, sizeof(line), file) == NULL) {
        // perror("fgets");
        fclose(file);
        return NULL;
    }
    if (sscanf(line, "%d", taskCount) != 1) {
        perror("sscanf");
        fclose(file);
        return NULL;
    }

    // Allocate memory for tasks
    Info* tasks = malloc(*taskCount * sizeof(Info));
    if (tasks == NULL) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    // Read and parse each task
    for (int i = 0; i < *taskCount; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            perror("fgets");
            freeTasks(tasks, i); // Free allocated tasks before returning
            fclose(file);
            return NULL;
        }

        char title[512] = {0}, priorityStr[512] = {0}, due[32] = {0};
        int scanned = sscanf(line, "%*d. %[^[[] [%[^]]] Due: %[^ ]", title, priorityStr, due);
        
        if (scanned < 2) {
            // If the line does not match the expected format, skip it or handle as needed
            fprintf(stderr, "Warning: Line %d does not match expected format: %s", i + 2, line);
            tasks[i].title = strdup("Unknown");
            tasks[i].description = NULL;
            tasks[i].due = strdup("Unknown");
            tasks[i].priority = LOW; // Default priority if unknown
        } else {
            tasks[i].title = strdup(title);
            tasks[i].description = NULL;
            tasks[i].due = strdup(due);
            tasks[i].priority = parsePriority(priorityStr);
        }
    }

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
        perror("fopen");
        return;
    }

    // Write the number of tasks as the first line
    fprintf(file, "%d\n", taskCount);

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d. %s[%s] Due: %s Status: Pending\n", i + 1, tasks[i].title,
                tasks[i].priority == HIGH ? "High" :
                tasks[i].priority == MEDIUM ? "Medium" : "Low",
                tasks[i].due);
    }

    fclose(file);
}

void freeTasks(Info* tasks, int taskCount) {
    for (int i = 0; i < taskCount; i++) {
        free(tasks[i].title);
        free(tasks[i].due);
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
