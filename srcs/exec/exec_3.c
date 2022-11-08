/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_3.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 19:07:57 by Thibault Cheneviere                      */
/*   Updated: 2022/11/08 12:32:30 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void ft_verify_entry_2(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int beg, int name_mode) {
	int i;
	token *t;

	i = beg - 1;

	while(++i < tl->ptr) {
		t = get_token_list_index(tl, i);

		switch(t->TokenType) {
			case MIME:
				if (e->d_type != DT_REG || (!verify_files_by_mime(e->d_name, t->value) && !or_mode))
					return;
				if (e->d_type == DT_REG && verify_files_by_mime(e->d_name, t->value) && or_mode) {
					ft_add_entry(e, pl, mutex);
					return;	
				}
				break;
			case CTC:
				if (e->d_type != DT_REG || (!verify_files_by_content_pattern(e->path, t->value) && !or_mode))
					return;
				if (e->d_type == DT_REG && verify_files_by_content_pattern(e->path, t->value) && or_mode) {
					ft_add_entry(e, pl, mutex);
					return;	
				}
				break;
			case DIRECTORY:
				if (e->d_type != DT_DIR || (!verify_directories_by_name(e->path, t->value) && !or_mode))
					return;
				if (e->d_type == DT_DIR && verify_directories_by_name(e->path, t->value) && or_mode) {
					ft_add_entry(e, pl, mutex);
					return;	
				}
				break;
			default:
				ft_verify_entry_3(e, tl, or_mode, mutex, pl, i, name_mode);
				return;
		}
	}

	ft_add_entry(e, pl, mutex);
}

void ft_verify_entry_3(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int beg, int name_mode) {
	int i;
	token *t;

	i = beg - 1;

	while (++i < tl->ptr) {
		t = get_token_list_index(tl, i);

		switch(t->TokenType) {
			case DATE:
				if ((e->d_type == DT_DIR && name_mode) || (e->d_type == DT_REG && !name_mode))
					return;
				if (!verify_files_by_date(e->path, t->value) && !or_mode)
					return;
				if (verify_files_by_date(e->path, t->value) && or_mode) {
					ft_add_entry(e, pl, mutex);
				}
				break;
			case PERM:
				if (!verify_file_perm(e->path, atoi(t->value)) && !or_mode)
					return;
				if (verify_file_perm(e->path, atoi(t->value)) && or_mode) {
					ft_add_entry(e, pl, mutex);
					return;
				}
				break;
			default:
				break;
		}
	}

	ft_add_entry(e, pl, mutex);
}

