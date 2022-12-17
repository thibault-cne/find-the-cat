#ifndef FTC_EXEC_H
#define FTC_EXEC_H

#include <pthread.h>

#include "token.h"
#include "display.h"
#include "validation.h"
#include "parser.h"
#include "entry.h"
#include "t_arg.h"
#include "ft_files.h"

/* exec.c */

void ft_exec_parser(parser_t *p, token_list *l, const char *path);
void ft_fprintp(entry_t *e, int color_mode, pthread_mutex_t *mutex);

/* exec_1.c */

void ft_fetch_path(const char *path, parser_t *p, token_list *tl);
void ft_fetch_path_1(const char *path, parser_t *p, token_list *tl);

/* exec_2.c */

int ft_verify_entry_1(entry_t *e, token_list *tl, int or_mode, int beg, int nm);

/* exec_3.c */

int ft_verify_entry_2(entry_t *e, token_list *tl, int or_mode, int beg, int nm);
int ft_verify_entry_3(entry_t *e, token_list *tl, int or_mode, int beg, int nm);
int ft_verify_entry_4(entry_t *e, token_list *tl, int or_mode, int beg, int name_mode);

/* exec_4.c */

void ft_exec_parser_2(entry_list_t *el, const char *path,  parser_t *p, token_list *tl);
void ft_mutex_init(pthread_mutex_t *m, int nb);
void ft_mutex_destroy(pthread_mutex_t *m, int nb);

/* exec_5.c */

void *ft_thread_fetch_path(void *arg);
void ft_thread_fetch_path_1(entry_list_t *el, const char *path, int links_mode, pthread_mutex_t *mutex);

/* exec_6.c */

void *ft_th_verify_entry(void *arg);

#endif // FTC_EXEC_H
