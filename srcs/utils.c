/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// utils.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/27 19/03/27
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/utils.h"

char *get_last_dir(const char *path)
{	
	char *temp;
	char *ptr;
	char *last;
	char *res;

	temp = strdup(path);
    ptr = strtok(temp, "/");

    while (ptr != NULL)
    {
        last = ptr;
        ptr = strtok(NULL, "/");
    }

    res = strdup(last);
    free(temp);

    return res;
}

int is_dir(const char *path)
{
    struct stat st;

    if (!stat(path, &st))
        return S_ISDIR(st.st_mode);

    return 0;
}

char *format_entry_path(char *path)
{
    // Remove trailing slash if any
    if (path[strlen(path) - 1] == '/')
        path[strlen(path) - 1] = '\0';

    return path;
}

int get_entry_type(const char *path) {
	struct stat st;
	
	stat(path, &st);

	if (S_ISDIR(st.st_mode))
		return DT_DIR;
	if (S_ISREG(st.st_mode))
		return DT_REG;

	#ifndef _WIN32
		if (S_ISLNK(st.st_mode))
			return DT_LNK;
	#endif // _WIN32

	printf("Unknown\n");
	return DT_UNKNOWN;
}

int ft_superatoi(char *beg, char *end) {
	int size;
	int i;
	int res;

	size = (int)(end - beg);
	i = -1;
	res = 0;

	while(beg[++i] > 47 && beg[i] < 58) {
		res += (beg[i] - 48) * (int)pow(10, size - 1 - i);
	}

	return res;
} 
