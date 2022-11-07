/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_2.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 19:05:45 by Thibault Cheneviere                      */
/*   Updated: 2022/11/07 19:07:47 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void *ft_verify_entry(void *arg) {
	arg_exec_t *arg_t;
	int beg;
	int end;
	pthread_mutex_t *mutex;
	entry_list_t *el;
	token_list *tl;
	int or_mode;
	path_list_t *pl;
	int i;
	entry_t *entry;

	arg_t = (arg_exec_t *)arg;
	beg = arg_t->beg;
	end = arg_t->end;
	mutex = arg_t->mutex;
	el = arg_t->el;
	tl = arg_t->tl;
	or_mode = arg_t->or_mode;
	pl = arg_t->pl;

	i = beg - 1;

	if (end > el->ptr) {
		printf("Error in index : out of bound\n");
		return NULL;
	}

	while (++i < end) {
		pthread_mutex_lock(mutex);
		entry = get_entry_list(el, i);
		pthread_mutex_unlock(mutex);

		ft_verify_entry_1(entry, tl, or_mode, mutex, pl, arg_t->name_mode);
	}

	return NULL;
}

void ft_verify_entry_1(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int name_mode) {
	int i;
	token *t;
	
	i = -1;

	while(++i < tl->ptr) {
		pthread_mutex_lock(mutex);
		t = get_token_list_index(tl, i);
		pthread_mutex_unlock(mutex);

		switch (t->TokenType) {
			case NAME:
				if (e->d_type != DT_REG || (!verify_files_by_name(e->d_name, t->value) && !or_mode))
					return;
				if (e->d_type == DT_REG && or_mode && verify_files_by_name(e->d_name, t->value)) {
					ft_add_entry(e, pl, mutex);
					return;
				}
				break;
			case SIZE:
				if (!verify_files_by_size(e->path, t->value) && !or_mode)
					return;
				if (verify_files_by_size(e->path, t->value) && or_mode) {
					ft_add_entry(e, pl, mutex);
					return;
				}
				break;
			default:
				ft_verify_entry_2(e, tl, or_mode, mutex, pl, i, name_mode);
				return;
		}
	}

	ft_add_entry(e, pl, mutex);
}

