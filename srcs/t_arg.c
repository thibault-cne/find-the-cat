/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// t_arg.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 22/19/45
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/t_arg.h"

void create_t_args_get_subdir(t_args_get_subdir *a, path_list *pl, thread *t, const char *path)
{
    a->pl = pl;
    a->t = t;
    a->path = (char *)malloc(sizeof(char) * strlen(path) + 1);
    strcpy(a->path, path);
}

void destroy_t_args_get_subdir(t_args_get_subdir *a)
{
    free(a->path);
}

void create_t_arg_validation(t_arg_validation *a, path_list *pl, token_list *tl, thread *t, struct dirent *entry, const char *path, int or_mode)
{
    a->pl = pl;
    a->tl = tl;
    a->t = t;
    a->entry = entry;

    a->path = (char *)malloc(sizeof(char) * strlen(path) + 1);
    strcpy(a->path, path);

    a->or_mode = or_mode;
}

void destroy_t_arg_validation(t_arg_validation *a)
{
    free(a->path);
}

void create_t_arg_exec(t_arg_exec *a, parser *p, token_list *l, path_list *pl, thread_collection *t, const char *path)
{
    a->p = p;
    a->l = l;
    a->pl = pl;
    a->t = t;
    a->path = (char *)malloc(sizeof(char) * strlen(path) + 1);
    strcpy(a->path, path);
}

void destroy_t_arg_exec(t_arg_exec *a)
{
    free(a->path);
}
