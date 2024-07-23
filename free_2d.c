#include "header.h"

void	free_2d(char **s)
{
	for (int i = 0; s[i]; ++ i)
        free(s[i]);
	free(s);
}

void remStruct(Info ** info) {
    free((*info)->description);
    free((*info)->title);
    free((*info)->due);
    free(*info);
}