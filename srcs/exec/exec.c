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
	path_list_t pl;

	create_path_list(&pl, 1);
	create_entry_list(&el);

	if (p->thread_mode > 1) {
		ft_exec_parser_2(&el, path, p, tl, &pl);
		path_display(&pl, p->color_mode);	
	} else {
		// Fetch all files and subdirs from the path
		ft_fetch_path(path, p, tl);
	}

	destroy_entry_list(&el);
	destroy_path_list(&pl);
}

void ft_display_entry(entry_list_t *el, int color_mode) {
	int i;
	entry_t *e;

	i = -1;

	while(++i < el->size) {
		e = get_entry_list(el, i);

		if (e != NULL)
			printf("%s\n", e->path);
	}
}

void ft_add_entry(entry_t *entry, path_list_t *pl, pthread_mutex_t *mutex) {
	if (mutex == NULL) {
		add_path_list(pl, entry->path);
		return;
	}

	pthread_mutex_lock(mutex);
	add_path_list(pl, entry->path);
	pthread_mutex_unlock(mutex);
}

