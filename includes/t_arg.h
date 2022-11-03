#ifndef FTC_T_ARG_H
#define FTC_T_ARG_H

#include <string.h>

#include "path.h"
#include "thread.h"
#include "token.h"
#include "parser.h"

struct _t_args_get_subdir
{
    path_list_t *pl;
    char *path;
    thread *t;
};
typedef struct _t_args_get_subdir t_args_get_subdir;

// Create a new t_args_get_subdir for the thread
// @param a the t_args_get_subdir pointer
// @param pl the path list
// @param t the thread
// @param path the path to search
void create_t_args_get_subdir(t_args_get_subdir *a, path_list_t *pl, thread *t, const char *path);

// Free the t_args_get_subdir
// @param a the t_args_get_subdir pointer
void destroy_t_args_get_subdir(t_args_get_subdir *a);

struct _t_arg_validation
{
    path_list_t *pl;
    token_list *tl;
    thread *t;
    struct dirent *entry;
    char *path;
    int or_mode;
};
typedef struct _t_arg_validation t_arg_validation;

// Create a new t_arg_validation for the thread
// @param a the t_arg_validation pointer
// @param pl the path list
// @param tl the token list
// @param t the thread
// @param entry the entry to validate
// @param path the path to search
// @param or_mode if the parser is in or mode
void create_t_arg_validation(t_arg_validation *a, path_list_t *pl, token_list *tl, thread *t, struct dirent *entry, const char *path, int or_mode);

// Free the t_arg_validation
void destroy_t_arg_validation(t_arg_validation *a);

struct _t_arg_exec
{
    parser_t *p;
    token_list *l;
    path_list_t *pl;
    thread_collection *t;
    char *path;
};
typedef struct _t_arg_exec t_arg_exec;

// Create a new t_arg_exec for the thread
// @param a the t_arg_exec pointer
// @param p the parser
// @param l the token list
// @param pl the path list
// @param t the thread collection
// @param path the path to search
void create_t_arg_exec(t_arg_exec *a, parser_t *p, token_list *l, path_list_t *pl, thread_collection *t, const char *path);

// Free the t_arg_exec
// @param a the t_arg_exec pointer
void destroy_t_arg_exec(t_arg_exec *a);

#endif // FTC_T_ARG_H
