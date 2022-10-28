#ifndef FTC_PARSER_H
#define FTC_PARSER_H

#include "token.h"
#include "display.h"
#include "validation.h"

// Files include
#include "f_mime.h"
#include "f_name.h"
#include "f_size.h"
#include "f_date.h"
#include "f_grep.h"
#include "f_dir.h"

enum _ParserStatus
{
    PARSER_SUCCESS,
    PARSER_ERROR,
    PARSER_INVALID_OPTION,
    PARSER_PARAM_MISSING,
};
typedef enum _ParserStatus ParserStatus;

struct _Parser
{
    ParserStatus status;
    int errorPtr;
    int testMode;
    int colorMode;
    int orMode;
    int nameMode;
    int sizeMode;
};
typedef struct _Parser Parser;

void start_parser(Parser *p, TokenList *l, int argc, char **argv);
int set_opt_parser(Parser *p, TokenList *l, Options opt, int argc, char **argv, int pos);

// Exec parser
void exec_parser(Parser *p, TokenList *l, const char *path);
void exec_parser_or_mode_filename(Parser *p, TokenList *l, const char *path);
void exec_parser_or_mode_directory(Parser *p, TokenList *l, const char *path);

#endif // FTC_PARSER_H
