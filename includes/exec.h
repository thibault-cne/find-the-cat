#ifndef FTC_EXEC_H
#define FTC_EXEC_H

#include <pthread.h>

#include "token.h"
#include "display.h"
#include "validation.h"
#include "parser.h"
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
void ft_exec_parser_1(entry_list_t *el, parser_t *p, token_list *tl, path_list_t *pl);
void ft_fetch_path(entry_list_t *el, const char *path, int links_mode);
void ft_fetch_path_1(entry_list_t *el, const char *path, int links_mode);
void ft_display_entry(entry_list_t *el, int color_mode);
void ft_verify_entry(entry_list_t *el, token_list *tl, int or_mode, path_list_t *pl, int name_mode);
void ft_verify_entry_1(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int nm);
void ft_verify_entry_2(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int beg, int nm);
void ft_verify_entry_3(entry_t *e, token_list *tl, int or_mode, pthread_mutex_t *mutex, path_list_t *pl, int beg, int nm);
void ft_add_entry(entry_t *e, path_list_t *pl, pthread_mutex_t *mutex);

void ft_exec_parser_2(entry_list_t *el, const char *path,  parser_t *p, token_list *tl, path_list_t *pl);
void ft_mutex_init(pthread_mutex_t *m, int nb);
void ft_mutex_destroy(pthread_mutex_t *m, int nb);

void *ft_thread_fetch_path(void *arg);
void ft_thread_fetch_path_1(entry_list_t *el, const char *path, int links_mode, pthread_mutex_t *mutex);

void *ft_th_verify_entry(void *arg);

#endif // FTC_EXEC_H
