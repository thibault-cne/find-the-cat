/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_1.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 19:04:12 by Thibault Cheneviere                      */
/*   Updated: 2022/11/07 19:04:57 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void ft_fetch_path(entry_list_t *el, const char *path, int links_mode) {
	char *d_name;
	entry_t e;

	d_name = get_last_dir(path);

	create_entry(&e,(char *)path, DT_DIR, d_name);
	add_entry_list_t(el, e);

	destroy_entry(&e);
	free(d_name);

	ft_fetch_path_1(el, path, links_mode);
}

void ft_fetch_path_1(entry_list_t *el, const char *path, int links_mode) {
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

		create_entry(&e, new_path, entry->d_type, entry->d_name);
		add_entry_list_t(el, e);
		
		if (entry->d_type == DT_DIR || (entry->d_type == DT_LNK && links_mode))
			ft_fetch_path_1(el, new_path, links_mode);

		destroy_entry(&e);
		free(new_path);
	}

	closedir(dir);
}
