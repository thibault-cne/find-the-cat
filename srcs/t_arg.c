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

void create_t_args_get_subdir(t_args_get_subdir *a, path_list_t *pl, thread *t, const char *path)
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

void create_t_arg_validation(t_arg_validation *a, path_list_t *pl, token_list *tl, thread *t, struct dirent *entry, const char *path, int or_mode)
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

void create_t_arg_exec(t_arg_exec *a, parser_t *p, token_list *l, path_list_t *pl, thread_collection *t, const char *path)
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

void create_arg_exec_t(arg_exec_t *a, int beg, int end, pthread_mutex_t *mutex, entry_list_t *el, int or_mode, token_list *tl, path_list_t *pl) {
	a->beg = beg;
	a->end = end;
	a->mutex = mutex;
	a->el = el;
	a->or_mode = or_mode;
	a->tl = tl;
	a->pl = pl;
}

