#ifndef FTC_EXEC_H
#define FTC_EXEC_H

#include "token.h"
#include "display.h"
#include "validation.h"
#include "parser.h"

// Files include
#include "f_mime.h"
#include "f_name.h"
#include "f_size.h"
#include "f_date.h"
#include "f_grep.h"
#include "f_dir.h"

// Exec parser
void exec_parser(parser *p, token_list *l, const char *path);
void exec_parser_rec(parser *p, token_list *l, path_list *pl, const char *path);
void validate_file(token_list *l, path_list *pl, struct dirent *entry, const char *path);

#endif // FTC_EXEC_H
