#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

typedef enum s_lvl lvl;
typedef struct s_Info Info;
char * err;

char	*itoa(int n);
int     my_strlen(char *str);
void    remStruct(Info ** info);
int     strlen_2d(char ** arr);
void	free_2d(char **s);
char	*strtrim(char *s1, char *set);
char	*strjoin(char *s1, char *s2, int flag);
char	*substr(char *s, unsigned int start, size_t len);
char	**split(char *s, char c);

const int   *getDate();
bool        getAddTask( char ** av);
char      *getPrio(lvl prio);
void    getViewTask();
void      *info_sort(void * arg);
bool    getUpdateTask(char **av);
bool getDeleteTask(char **av);
void *checkTaskDate(void *arg);


enum s_lvl {
    HIGH,
    MEDIUM,
    LOW,
};

struct s_Info {
    char * title;
    char * description;
    char * due;
    char * status;
    lvl priority;
};



#endif