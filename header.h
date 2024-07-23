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

char	*itoa(int n);
int     my_strlen(char *str);
void    remStruct(Info ** info);
int     strlen_2d(const char ** arr);
void	free_2d(char **s, size_t i);
char	*strjoin(char *s1, char *s2, int flag);
char	*substr(char *s, unsigned int start, size_t len);
char	**split(char *s, char c);

const int*  getDate();
bool        getAddTask(const char ** av);

typedef enum s_lvl lvl;
typedef struct s_Info Info;

enum s_lvl {
    HIGHT,
    MEDIUM,
    LOW
};

struct s_Info {
    char * title;
    char * description;
    char * due;
    lvl priority;
};



#endif