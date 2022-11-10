/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_2.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 19:05:45 by Thibault Cheneviere                      */
/*   Updated: 2022/11/10 20:59:42 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int ft_verify_entry_1(entry_t *e, token_list *tl, int or_mode, int name_mode) {
	int i;
	token *t;
	
	i = -1;

	while(++i < tl->ptr) {
		t = get_token_list_index(tl, i);

		switch (t->TokenType) {
			case NAME:
				if (get_entry_type(e->path) != DT_REG || (!verify_files_by_name(e->d_name, t->value) && !or_mode))
					return 0;
				if (get_entry_type(e->path) == DT_REG && or_mode && verify_files_by_name(e->d_name, t->value)) {
					return 1;
				}
				break;
			case SIZE:
				if (!verify_files_by_size(e->path, t->value) && !or_mode)
					return 0;
				if (verify_files_by_size(e->path, t->value) && or_mode) {
					return 1;
				}
				break;
			default:
				return ft_verify_entry_2(e, tl, or_mode, i, name_mode);
		}
	}

	return or_mode ^ 1;
}

