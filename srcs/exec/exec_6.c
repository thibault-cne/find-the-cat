/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_6.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/08 12:23:20 by Thibault Cheneviere                      */
/*   Updated: 2022/11/09 09:52:41 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void *ft_th_verify_entry(void *arg) {
	arg_th_exec_t *a;

	a = (arg_th_exec_t *)arg;

	while(1) {
		entry_t *entry;

		if (a->el->status == STATUS_END && a->el->ptr == a->el->size)
			break;

		pthread_mutex_lock(&a->mutex[0]);
		entry = get_entry_list_th(a->el);
		pthread_mutex_unlock(&a->mutex[0]);

		if (entry == NULL)
			continue;
		
		if (ft_verify_entry_1(entry, a->tl, a->or_mode, a->name_mode))
			ft_fprintp(entry, a->color_mode, &a->mutex[1]);
	}

	return NULL;
}
