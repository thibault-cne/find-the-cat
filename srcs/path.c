/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// path.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/25 19/09/21
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/path.h"

void create_path_list(PathList *l, int size)
{
    l->data = (char **)malloc(sizeof(char *) * size);
    l->ptr = 0;
    l->size = size;
}

void add_path_list(PathList *l, char *path)
{
    if (l->ptr >= l->size)
    {
        l->size *= 2;
        l->data = (char **)realloc(l->data, sizeof(char *) * l->size);
    }

    char *p;

    p = malloc(sizeof(char) * PATH_MAX_SIZE);
    strncpy(p, path, PATH_MAX_SIZE);

    l->data[l->ptr++] = p;
}

char *get_path_list_index(PathList *l, int i)
{
    if (i >= l->size)
    {
        return NULL;
    }

    return l->data[i];
}

void remove_path_list_index(PathList *l, int i)
{
    if (i >= l->size)
    {
        return;
    }

    free(l->data[i]);
    l->data[i] = NULL;
}

void destroy_path_list(PathList *l)
{
    int i;

    i = -1;

    while (++i < l->ptr)
    {
        if (l->data[i] != NULL)
        {
            free(l->data[i]);
        }
    }

    free(l->data);
}
