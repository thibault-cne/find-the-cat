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

#endif // FTC_T_ARG_H
