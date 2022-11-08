/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   exec_5.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/08 12:15:58 by Thibault Cheneviere                      */
/*   Updated: 2022/11/08 13:11:18 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void *ft_thread_fetch_path(void *arg) {
	arg_fetch_t *a;
	char *d_name;
	entry_t e;

	a = (arg_fetch_t *)arg;

	d_name = get_last_dir(a->path);

	create_entry(&e,(char *)a->path, DT_DIR, d_name);
	pthread_mutex_lock(a->mutex);
	add_entry_list_t(a->el, e);
	pthread_mutex_unlock(a->mutex);

	destroy_entry(&e);
	free(d_name);

	ft_thread_fetch_path_1(a->el, a->path, a->link_mode, a->mutex);

	a->el->status = STATUS_END;

	return NULL;
}

void ft_thread_fetch_path_1(entry_list_t *el, const char *path, int links_mode, pthread_mutex_t *mutex) {
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
		pthread_mutex_lock(mutex);
		add_entry_list_t(el, e);
		pthread_mutex_unlock(mutex);
		
		if (entry->d_type == DT_DIR || (entry->d_type == DT_LNK && links_mode))
			ft_thread_fetch_path_1(el, new_path, links_mode, mutex);

		destroy_entry(&e);
		free(new_path);
	}

	closedir(dir);
}

