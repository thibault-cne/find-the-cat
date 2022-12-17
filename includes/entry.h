#ifndef FTC_ENTRY_H
#define FTC_ENTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

struct _entry_t {
	char *path;
	unsigned char d_type;
	char *d_name;
	struct _entry_t *next;
};
typedef struct _entry_t entry_t;

void create_entry(entry_t *e, char *path, unsigned char d_type, char *d_name);
void destroy_entry(entry_t *e);

struct _entry_list_t {
	struct _entry_t *data;
	int ptr;
	int size; 
	enum _end_status_t {
		STATUS_END,
		STATUS_GOING,
	} status;
};
typedef struct _entry_list_t entry_list_t;

void create_entry_list(entry_list_t *el);
void add_entry_list_t(entry_list_t *el, entry_t e);
entry_t *get_entry_list(entry_list_t *el, int index);
entry_t *get_entry_list_th(entry_list_t *el);
void destroy_entry_list(entry_list_t *el);

#endif // FTC_ENTRY_H
