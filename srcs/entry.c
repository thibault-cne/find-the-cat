/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   entry.c                                                                  */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/06 22:53:59 by Thibault Cheneviere                      */
/*   Updated: 2022/12/17 18:01:37 by Thibault Cheneviere                      */
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
	e->next = NULL;
}

void destroy_entry(entry_t *e) {
	free(e->path);
	free(e->d_name);
}

void create_entry_list(entry_list_t *el) {
	el->data = NULL;
	el->status = STATUS_GOING;
}

void add_entry_list_t(entry_list_t *el, entry_t e) {
	entry_t *ne;
	
	ne = (entry_t *)malloc(sizeof(entry_t));
	create_entry(ne, e.path, e.d_type, e.d_name);

	if (el->data == NULL) {
		el->data = ne;
		return;
	}

	entry_t *ce;

	ce = el->data;
	while(ce->next != NULL) {
		ce = ce->next;
	}

	ce->next = ne;
}

entry_t *get_entry_list_th(entry_list_t *el) {
	if (el->data != NULL) {
		entry_t *r = el->data;
		el->data = r->next;
		return r;
	}

	return NULL;
}

void destroy_entry_list(entry_list_t *el) {
	entry_t *temp;
	entry_t *ce;

	ce = el->data;

	if (ce == NULL)
		return;

	while(ce->next != NULL) {
		temp = ce;
		ce = temp->next;
		destroy_entry(temp);
		free(temp);
	}

	destroy_entry(ce);
	free(ce);
}
