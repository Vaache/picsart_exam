#include "header.h"

void	free_2d(char **s, size_t i)
{
	while (i-- >= 0)
		free (s[i]);
	free(s);
}

void remStruct(Info ** info) {
    free((*info)->description);
    free((*info)->title);
    free((*info)->due);
    free(*info);
}