/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_1.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 19:04:12 by Thibault Cheneviere                      */
/*   Updated: 2022/11/09 09:18:48 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void ft_fetch_path(const char *path, parser_t *p, token_list *tl) {
	char *d_name;
	entry_t e;

	if (p->dir_mode) {
		f_printp(path, p->color_mode);
	} else {
		d_name = get_last_dir(path);

		create_entry(&e,(char *)path, DT_DIR, d_name);
		if (ft_verify_entry_1(&e, tl, p->or_mode, p->name_mode))
			f_printp(e.path, p->color_mode);

		destroy_entry(&e);
		free(d_name);
	}


	ft_fetch_path_1(path, p, tl);
}

void ft_fetch_path_1(const char *path, parser_t *p, token_list *tl) {
	DIR *dir;
	struct dirent *entry;
	entry_t e;
	int len;

	if (!(dir = opendir(path)))
		return;

    while ((entry = readdir(dir)) != NULL) {
		char *new_path;

    	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        	 continue;
		
		len = strlen(path) + strlen(entry->d_name);
		new_path = malloc(len + 2);
		snprintf(new_path, len + 2, "%s/%s", path, entry->d_name);

		if (p->dir_mode) {
			f_printp(new_path, p->color_mode);
		} else {
			create_entry(&e, new_path, entry->d_type, entry->d_name);
			
			if (ft_verify_entry_1(&e, tl, p->or_mode, p->name_mode))
				f_printp(e.path, p->color_mode);
			
			destroy_entry(&e);
		}
		
		if (entry->d_type == DT_DIR || (entry->d_type == DT_LNK && p->link_mode))
			ft_fetch_path_1(new_path, p, tl);

		free(new_path);
	}

	closedir(dir);
}
