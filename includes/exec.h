#ifndef FTC_EXEC_H
#define FTC_EXEC_H

#include <pthread.h>

#include "token.h"
#include "display.h"
#include "validation.h"
#include "parser.h"
#include "thread.h"

// Files include
#include "f_mime.h"
#include "f_name.h"
#include "f_size.h"
#include "f_date.h"
#include "f_grep.h"
#include "f_dir.h"
#include "f_perm.h"

// Shortcut to create and join a thread
// @param t the thread structure
// @param f the function to execute
// @param a the arguments of the function
#define _create_thread(t, f, a)                             \
    pthread_create(t->threads, NULL, (void *)f, (void *)a); \
    pthread_join(*t->threads, NULL);                        \
    t->active = 0;

// Shortcut to init a thread collection
// @param n the number of threads
// @param tc the thread collection pointer
// @param p_t the thread pointer
// @param m the mutex pointer
#define _create_thread_collection(n, t_c, p_t, m) \
    int i = -1;                                   \
    while (++i < n)                               \
    {                                             \
        thread th;                                \
        create_thread(&th, &p_t[i], m);           \
        add_thread(&t_c, &th);                    \
    }

// Execute the parser
// @param p the parser
// @param l the token list
// @param path the path to search
void exec_parser(parser_t *p, token_list *l, const char *path);

// Execute the parser recursively inside all subdirectory
// @param args_exec a pointer to the functions arguments
void *exec_parser_rec(void *arg_exec);

// Validate an entry with the parser settings
// @param args a pointer to the functions arguments
void *validate_file(void *args);

#endif // FTC_EXEC_H
