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

// Get file size in bytes of a dirent
long get_file_size(const char *file_path)
{
    struct stat st;

    if (stat(file_path, &st) == 0)
    {
        return st.st_size;
    }

    return -1;
}

double get_seconds_from_last_modification(const char *file_path)
{
    struct stat st;
    char *cp_path;

    cp_path = (char *)malloc(sizeof(char) * (strlen(file_path) + 1));
    strcpy(cp_path, file_path);

    if (stat(cp_path, &st) == 0)
    {
        time_t t = st.st_mtime;
        time_t now = time(NULL);

        // Free memory
        free(cp_path);

        return difftime(now, t);
    }

    // Free memory
    free(cp_path);

    return -1;
}

int regex_match(const char *str, const char *pattern)
{
    regex_t regex;
    int reti;
    int res;

    reti = regcomp(&regex, pattern, 0);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex %s\n", pattern);
        exit(1);
    }

    res = regexec(&regex, str, 0, NULL, 0);

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);
    return res;
}

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
