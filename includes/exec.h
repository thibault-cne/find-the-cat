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

// Execute the parser
// @param p the parser
// @param l the token list
// @param path the path to search
void exec_parser(parser *p, token_list *l, const char *path);

// Execute the parser recursively inside all subdirectory
// @param args_exec a pointer to the functions arguments
void *exec_parser_rec(void *arg_exec);

// Validate an entry with the parser settings
// @param args a pointer to the functions arguments
void *validate_file(void *args);

#endif // FTC_EXEC_H
