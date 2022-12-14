/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_3.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 19:07:57 by Thibault Cheneviere                      */
/*   Updated: 2022/12/17 16:39:41 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int ft_verify_entry_2(entry_t *e, token_list *tl, int or_mode, int beg, int name_mode) {
	int i;
	token *t;

	i = beg - 1;

	while(++i < tl->ptr) {
		t = get_token_list_index(tl, i);

		switch(t->TokenType) {
			case MIME:
				if (get_entry_type(e->path) != DT_REG || (!verify_files_by_mime(e->d_name, t->value) && !or_mode))
					return 0;
				if (get_entry_type(e->path) == DT_REG && verify_files_by_mime(e->d_name, t->value) && or_mode) {
					return 1;	
				}
				break;
			case CTC:
				if (get_entry_type(e->path) != DT_REG || (!verify_files_by_content_pattern(e->path, t->value) && !or_mode))
					return 0;
				if (get_entry_type(e->path) == DT_REG && verify_files_by_content_pattern(e->path, t->value) && or_mode) {
					return 1;	
				}
				break;
			case DIRECTORY:
				if (get_entry_type(e->path) != DT_DIR || (!verify_directories_by_name(e->path, t->value) && !or_mode))
					return 0;
				if (get_entry_type(e->path) == DT_DIR && verify_directories_by_name(e->path, t->value) && or_mode) {
					return 1;	
				}
				break;
			default:
				return ft_verify_entry_3(e, tl, or_mode, i, name_mode);
				
		}
	}

	return or_mode ^ 1;
}

int ft_verify_entry_3(entry_t *e, token_list *tl, int or_mode, int beg, int name_mode) {
	int i;
	token *t;

	i = beg - 1;

	while (++i < tl->ptr) {
		t = get_token_list_index(tl, i);

		switch(t->TokenType) {
			case DATE:
				if ((e->d_type == DT_DIR && name_mode) || (e->d_type == DT_REG && !name_mode))
					return 0;
				if (!verify_files_by_date(e->path, t->value) && !or_mode)
					return 0;
				if (verify_files_by_date(e->path, t->value) && or_mode) {
					return 1;
				}
				break;
			case PERM:
				if (!verify_file_perm(e->path, atoi(t->value)) && !or_mode)
					return 0;
				if (verify_file_perm(e->path, atoi(t->value)) && or_mode) {
					return 1;
				}
				break;
			default:
				return ft_verify_entry_4(e, tl, or_mode, i, name_mode);
		}
	}

	return or_mode ^ 1;
}


int ft_verify_entry_4(entry_t *e, token_list *tl, int or_mode, int beg, int name_mode) {
	int i;
	token *t;

	i = beg - 1;

	while (++i < tl->ptr) {
		t = get_token_list_index(tl, i);

		switch(t->TokenType) {
			case COLOR:
				break;
			case OR:
				break;
			case LINK:
				break;
			case THREADS:
				break;
			case TEST:
				break;
			case NONE:
				break;
			default:
				return ft_verify_entry_1(e, tl, or_mode, i, name_mode);
		}
	}

	return or_mode ^ 1;
}
