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

void create_arg_exec_t(arg_exec_t *a, int beg, int end, pthread_mutex_t *mutex, entry_list_t *el, int or_mode, token_list *tl, path_list_t *pl, int nm) {
	a->beg = beg;
	a->end = end;
	a->mutex = mutex;
	a->el = el;
	a->or_mode = or_mode;
	a->tl = tl;
	a->pl = pl;
	a->name_mode = nm;
}

void create_arg_fetch_t(arg_fetch_t *a, entry_list_t *el, const char *path, int link_mode, pthread_mutex_t *m) {
	a->el = el;
	
	a->path = (char *)malloc(sizeof(char) * strlen(path) + 1);
	strcpy(a->path, path);

	a->link_mode = link_mode;
	a->mutex = m;
}

void destroy_arg_fetch_t(arg_fetch_t *a) {
	free(a->path);
}

void create_arg_th_exec_t(arg_th_exec_t *a, pthread_mutex_t *m, entry_list_t *el, int or_mode, token_list *tl, int color_mode, int nm) {
	a->mutex = m;
	a->el = el;
	a->or_mode = or_mode;
	a->tl = tl;
	a->color_mode = color_mode;
	a->name_mode = nm;
	a->current_index = 0;
}

