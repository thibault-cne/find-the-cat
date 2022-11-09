/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_4.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/08 11:59:14 by Thibault Cheneviere                      */
/*   Updated: 2022/11/09 11:12:56 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void ft_exec_parser_2(entry_list_t *el, const char *path,  parser_t *p, token_list *tl) {
	pthread_t *pthread;
	pthread_mutex_t *mutex;
	arg_fetch_t a_f;
	arg_th_exec_t a_th;
	int i;

	pthread = (pthread_t *)malloc(sizeof(pthread_t) * p->thread_mode + 1);
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 2);
	ft_mutex_init(mutex, 2);

	create_arg_fetch_t(&a_f, el, path, p->link_mode, &mutex[0]);
	create_arg_th_exec_t(&a_th, mutex, el, p->or_mode, tl, p->color_mode, p->name_mode);

	i = 1;
	pthread_create(&pthread[i], NULL, (void *)ft_thread_fetch_path, (void *)&a_f);

	while(++i < p->thread_mode) {
		pthread_create(&pthread[i], NULL, (void *)ft_th_verify_entry, (void *)&a_th);
	}

	i = 0;

	while(++i < p->thread_mode) {
		pthread_join(pthread[i], NULL);
	}

	ft_mutex_destroy(mutex, 2);
	free(pthread);
	destroy_arg_fetch_t(&a_f);
}

void ft_mutex_init(pthread_mutex_t *m, int nb) {
	int i;

	i = -1;

	while(++i < nb) {
		pthread_mutex_init(&m[i], NULL);
	}
}

void ft_mutex_destroy(pthread_mutex_t *m, int nb) {
	int i;

	i = -1;

	while(++i < nb) {
		pthread_mutex_destroy(&m[i]);
	}
}
