#ifndef FTC_T_ARG_H
#define FTC_T_ARG_H

#include <string.h>
#include <pthread.h>

#include "path.h"
#include "token.h"
#include "parser.h"
#include "entry.h"

struct _arg_exec_t {
	int beg;
	int end;
	pthread_mutex_t *mutex;
	entry_list_t *el;
	int or_mode;
	token_list *tl;
	path_list_t *pl;
	int name_mode;
};
typedef struct _arg_exec_t arg_exec_t;

void create_arg_exec_t(arg_exec_t *a, int beg, int end, pthread_mutex_t *mutex, entry_list_t *el, int or_mode, token_list *tl, path_list_t *pl, int name_mode);

struct _arg_fetch_t {
	entry_list_t *el;
	char *path;
	int link_mode;
	pthread_mutex_t *mutex;
};
typedef struct _arg_fetch_t arg_fetch_t;

void create_arg_fetch_t(arg_fetch_t *a, entry_list_t *el, const char *path, int link_mode, pthread_mutex_t *m);
void destroy_arg_fetch_t(arg_fetch_t *a);

struct _arg_thread_exec_t {
	pthread_mutex_t *mutex;
	entry_list_t *el;
	int or_mode;
	token_list *tl;
	int color_mode;
	int name_mode;
	int current_index;
};
typedef struct _arg_thread_exec_t arg_th_exec_t;

void create_arg_th_exec_t(arg_th_exec_t *a, pthread_mutex_t *m, entry_list_t *el, int or_mode, token_list *tl, int color_mode, int name_mode);

#endif // FTC_T_ARG_H
