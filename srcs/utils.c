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

    if (stat(path, &st) == 0)
    {
        return S_ISDIR(st.st_mode);
    }

    return 0;
}

char *format_entry_path(char *path)
{
    // Remove trailing slash if any
    if (path[strlen(path) - 1] == '/')
    {
        char *new_path = malloc(sizeof(char) * (strlen(path) + 1));
        strcpy(new_path, path);
        new_path[strlen(path) - 1] = '\0';

        strcpy((char *)path, new_path);
        free(new_path);
    }

    return path;
}

int get_entry_type(const char *path) {
	struct stat st;
	char *temp;
	
	temp = (char *)malloc(sizeof(char) * strlen(path) + 1);
	strcpy(temp, path);

	stat(temp, &st);

	free(temp);

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
