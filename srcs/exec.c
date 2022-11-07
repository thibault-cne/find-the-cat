/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// exec.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/31/07
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/exec.h"

void ft_exec_parser(parser_t *p, token_list *tl, const char *path) {
	entry_list_t el;
	path_list_t pl;

	create_path_list(&pl, 1);
	create_entry_list(&el, 1);

	// Fetch all files and subdirs from the path
	ft_fetch_path(&el, path, p->link_mode);

	if (p->dir_mode == 1) {
		ft_display_entry(&el, p->color_mode);
	} else {
		ft_exec_parser_1(&el, p, tl, &pl);
		path_display(&pl, p->color_mode);
	}

	destroy_entry_list(&el);
	destroy_path_list(&pl);
}

void ft_exec_parser_1(entry_list_t *el, parser_t *p, token_list *tl, path_list_t *pl) {
	pthread_t *pthread;
	pthread_mutex_t mutex;
	int i;
	int mult;
	arg_exec_t *a;

	// Split verification of each path between all the threads
	pthread = (pthread_t *)malloc(sizeof(pthread_t) * p->thread_mode);
	pthread_mutex_init(&mutex, NULL);

	// Create all threads and affect it to a certain zone
	i = -1;
	mult = (int)el->ptr/p->thread_mode;

	a = (arg_exec_t *)malloc(sizeof(arg_exec_t) * p->thread_mode);

	while(++i < p->thread_mode) {
		if (i + 1 == p->thread_mode) { create_arg_exec_t(&a[i], i * mult, el->ptr, &mutex, el, p->or_mode, tl, pl, p->name_mode); }
		else { create_arg_exec_t(&a[i], i * mult, (i + 1) * mult, &mutex, el, p->or_mode, tl, pl, p->name_mode); }

		pthread_create(&pthread[i], NULL, (void *)ft_verify_entry, (void *)&a[i]);
	}

	// Join all threads
	i = -1;

	while(++i < p->thread_mode) {
		pthread_join(pthread[i], NULL);
	}

	free(a);
	free(pthread);
	pthread_mutex_destroy(&mutex);
}

void ft_fetch_path(entry_list_t *el, const char *path, int links_mode) {
	char *d_name;
	entry_t e;

	d_name = get_last_dir(path);

	create_entry(&e,(char *)path, DT_DIR, d_name);
	add_entry_list_t(el, e);

	destroy_entry(&e);

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

void ft_display_entry(entry_list_t *el, int color_mode) {
	int i;
	entry_t *e;

	i = -1;

	while(++i < el->ptr) {
		e = get_entry_list(el, i);

		printf("%s\n", e->path);
	}
}

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

void ft_verify_entry_2(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int beg, int name_mode) {
	int i;
	token *t;

	i = beg - 1;

	while(++i < tl->ptr) {
		pthread_mutex_lock(mutex);
		t = get_token_list_index(tl, i);
		pthread_mutex_unlock(mutex);

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
		pthread_mutex_lock(mutex);
		t = get_token_list_index(tl, i);
		pthread_mutex_unlock(mutex);

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

void ft_add_entry(entry_t *entry, path_list_t *pl, pthread_mutex_t *mutex) {
	pthread_mutex_lock(mutex);
	add_path_list(pl, entry->path);
	pthread_mutex_unlock(mutex);
}

