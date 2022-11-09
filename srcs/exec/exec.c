/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// exec.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/31/07
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../../includes/exec.h"

void ft_exec_parser(parser_t *p, token_list *tl, const char *path) {
	entry_list_t el;

	create_entry_list(&el);

	if (p->thread_mode > 1) {
		ft_exec_parser_2(&el, path, p, tl);
	} else {
		// Fetch all files and subdirs from the path
		ft_fetch_path(path, p, tl);
	}

	destroy_entry_list(&el);
}

void ft_fprintp(entry_t *entry, int color_mode, pthread_mutex_t *mutex) {
	if (mutex == NULL) {
		f_printp(entry->path, color_mode);
		return;
	}

	pthread_mutex_lock(mutex);
	f_printp(entry->path, color_mode);
	pthread_mutex_unlock(mutex);
}

