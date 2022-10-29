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

    if (stat(file_path, &st) == 0)
    {
        time_t t = st.st_mtime;
        time_t now = time(NULL);

        return difftime(now, t);
    }

    return -1;
}

int regex_match(const char *str, const char *pattern)
{
    regex_t regex;
    int reti;

    reti = regcomp(&regex, pattern, 0);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex %s\n", pattern);
        exit(1);
    }

    return regexec(&regex, str, 0, NULL, 0);
}

char *get_last_dir(const char *path)
{
    char *temp;
    char *ptr;
    char *last;

    temp = strdup(path);

    ptr = strtok(temp, "/");

    while (ptr != NULL)
    {
        last = ptr;
        ptr = strtok(NULL, "/");
    }

    return last;
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
