/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_2.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 19:05:45 by Thibault Cheneviere                      */
/*   Updated: 2022/11/08 14:38:18 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void ft_verify_entry(entry_list_t *el, token_list *tl, int or_mode, path_list_t *pl, int name_mode) {
	int i;
	entry_t *entry;

	i = - 1;

	while (++i < el->size) {
		entry = get_entry_list(el, i);

		if (entry != NULL)
			ft_verify_entry_1(entry, tl, or_mode, NULL, pl, name_mode);
	}
}

void ft_verify_entry_1(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int name_mode) {
	int i;
	token *t;
	
	i = -1;

	while(++i < tl->ptr) {
		t = get_token_list_index(tl, i);

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

