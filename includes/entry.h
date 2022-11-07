#ifndef FTC_ENTRY_H
#define FTC_ENTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

struct _entry_t {
	char *path;
	struct dirent *entry;
	enum _status_t {
		STATUS_OK,
		STATUS_NULL,
	}  status;
};
typedef struct _entry_t entry_t;

void create_entry(entry_t *e, char *path, struct dirent *entry);
void destroy_entry(entry_t *e);

struct _entry_list_t {
	struct _entry_t *data;
	int ptr;
	int size; 
};
typedef struct _entry_list_t entry_list_t;

void create_entry_list(entry_list_t *el, int size);
void add_entry_list_t(entry_list_t *el, entry_t e);
entry_t *get_entry_list(entry_list_t *el, int index);
void destroy_entry_list(entry_list_t *el);

#endif // FTC_ENTRY_H
