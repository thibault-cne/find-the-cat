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
		ft_fetch_path(&el, path, p->link_mode);

		if (p->dir_mode == 1) {
			ft_display_entry(&el, p->color_mode);
		} else {
			ft_exec_parser_1(&el, p, tl, &pl);
			path_display(&pl, p->color_mode);
		}
	}

	destroy_entry_list(&el);
	destroy_path_list(&pl);
}

void ft_exec_parser_1(entry_list_t *el, parser_t *p, token_list *tl, path_list_t *pl) {
	pthread_t *pthread;
	pthread_mutex_t mutex;
	int i;
	int mult;
	arg_exec_t *a;

	// Split verification of each path between all the threads
	pthread = (pthread_t *)malloc(sizeof(pthread_t) * p->thread_mode);
	pthread_mutex_init(&mutex, NULL);

	// Create all threads and affect it to a certain zone
	i = -1;
	mult = (int)el->ptr/p->thread_mode;

	a = (arg_exec_t *)malloc(sizeof(arg_exec_t) * p->thread_mode);

	while(++i < p->thread_mode) {
		if (i + 1 == p->thread_mode) { create_arg_exec_t(&a[i], i * mult, el->ptr, &mutex, el, p->or_mode, tl, pl, p->name_mode); }
		else { create_arg_exec_t(&a[i], i * mult, (i + 1) * mult, &mutex, el, p->or_mode, tl, pl, p->name_mode); }

		pthread_create(&pthread[i], NULL, (void *)ft_verify_entry, (void *)&a[i]);
	}

	// Join all threads
	i = -1;

	while(++i < p->thread_mode) {
		pthread_join(pthread[i], NULL);
	}

	free(a);
	free(pthread);
	pthread_mutex_destroy(&mutex);
}

void ft_display_entry(entry_list_t *el, int color_mode) {
	int i;
	entry_t *e;

	i = -1;

	while(++i < el->ptr) {
		e = get_entry_list(el, i);

		printf("%s\n", e->path);
	}
}

void ft_add_entry(entry_t *entry, path_list_t *pl, pthread_mutex_t *mutex) {
	pthread_mutex_lock(mutex);
	add_path_list(pl, entry->path);
	pthread_mutex_unlock(mutex);
}

