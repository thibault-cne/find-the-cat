#ifndef FTC_EXEC_H
#define FTC_EXEC_H

#include <pthread.h>

#include "token.h"
#include "display.h"
#include "validation.h"
#include "parser.h"
#include "thread.h"
#include "entry.h"

// Files include
#include "f_mime.h"
#include "f_name.h"
#include "f_size.h"
#include "f_date.h"
#include "f_grep.h"
#include "f_dir.h"
#include "f_perm.h"

void ft_exec_parser(parser_t *p, token_list *l, const char *path);
void ft_display_path(entry_list_t *el);
void ft_fetch_path(entry_list_t *el, const char *path, int links_mode);
void *ft_verify_entry(void *arg);
void ft_verify_entry_1(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl);
void ft_verify_entry_2(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int beg);
void ft_verify_entry_3(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int beg);
void ft_add_entry(entry_t *e, path_list_t *pl, pthread_mutex_t *mutex);

#endif // FTC_EXEC_H
