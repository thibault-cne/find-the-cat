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
void exec_parser(Parser *p, TokenList *l, const char *path);
void exec_parser_or_mode_filename(Parser *p, TokenList *l, const char *path);
void exec_parser_or_mode_directory(Parser *p, TokenList *l, const char *path);

#endif // FTC_EXEC_H
