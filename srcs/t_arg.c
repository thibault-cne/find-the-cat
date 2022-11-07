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

