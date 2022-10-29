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

// Exec parser
void exec_parser(parser *p, token_list *l, const char *path);
void *exec_parser_rec(void *arg_exec);
void *validate_file(void *args);

#endif // FTC_EXEC_H
