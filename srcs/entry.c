/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   entry.c                                                                  */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/06 22:53:59 by Thibault Cheneviere                      */
/*   Updated: 2022/11/07 11:53:44 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/entry.h"

void create_entry(entry_t *e, char *path, unsigned char d_type, char *d_name) {
	e->status = STATUS_NULL;
	
	e->path = (char *)malloc(sizeof(char) * strlen(path) + 1);
	strcpy(e->path, path);

	e->d_name = (char *)malloc(sizeof(char) * strlen(d_name) + 1);
	strcpy(e->d_name, d_name);

	e->d_type = d_type;
}

void destroy_entry(entry_t *e) {
	free(e->path);
	free(e->d_name);
}

void create_entry_list(entry_list_t *el, int size) {
	el->size = size;
	el->ptr = 0;
	el->data = (entry_t *)malloc(sizeof(entry_t) * size);
}

void add_entry_list_t(entry_list_t *el, entry_t e) {
	if (el->ptr >= el->size) {
		el->size *= 2;
		el->data = (entry_t *)realloc(el->data, sizeof(entry_t) * el->size);
	}

	entry_t *ne;

	ne = &el->data[el->ptr++];
	create_entry(ne, e.path, e.d_type, e.d_name);
}

entry_t *get_entry_list(entry_list_t *el, int index) {
	if (index >= el->ptr) {
		return NULL;
	}

	return &el->data[index];
}

void destroy_entry_list(entry_list_t *el) {
	int i;

	i = -1;

	while(++i < el->ptr) {
		destroy_entry(&el->data[i]);
	}

	free(el->data);
}