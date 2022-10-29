#ifndef FTC_T_ARG_H
#define FTC_T_ARG_H

#include <string.h>

#include "path.h"
#include "thread.h"
#include "token.h"
#include "parser.h"

struct _t_args_get_subdir
{
    path_list *pl;
    char *path;
    thread *t;
};
typedef struct _t_args_get_subdir t_args_get_subdir;

void create_t_args_get_subdir(t_args_get_subdir *a, path_list *pl, thread *t, const char *path);
void destroy_t_args_get_subdir(t_args_get_subdir *a);

struct _t_arg_validation
{
    path_list *pl;
    token_list *tl;
    thread *t;
    struct dirent *entry;
    char *path;
    int or_mode;
};
typedef struct _t_arg_validation t_arg_validation;

void create_t_arg_validation(t_arg_validation *a, path_list *pl, token_list *tl, thread *t, struct dirent *entry, const char *path, int or_mode);
void destroy_t_arg_validation(t_arg_validation *a);

struct _t_arg_exec
{
    parser *p;
    token_list *l;
    path_list *pl;
    thread_collection *t;
    char *path;
};
typedef struct _t_arg_exec t_arg_exec;

void create_t_arg_exec(t_arg_exec *a, parser *p, token_list *l, path_list *pl, thread_collection *t, const char *path);
void destroy_t_arg_exec(t_arg_exec *a);

#endif // FTC_T_ARG_H
