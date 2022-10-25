#ifndef FTC_PARSER_H
#define FTC_PARSER_H

#include "token.h"
#include "exec.h"
#include "display.h"

enum _ParserStatus
{
    PARSER_SUCCESS,
    PARSER_ERROR
};
typedef enum _ParserStatus ParserStatus;

struct _Parser
{
    ParserStatus status;
    int testMode;
    int colorMode;
    int orMode;
    int nameMode;
    int sizeMode;
};
typedef struct _Parser Parser;

void start_parser(Parser *p, TokenList *l, int argc, char **argv);
int set_opt_parser(Parser *p, TokenList *l, Options opt, int argc, char **argv, int pos);
void exec_parser(Parser *p, TokenList *l, const char *path);

#endif // FTC_PARSER_H
