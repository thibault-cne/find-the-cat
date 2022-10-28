#ifndef FTC_PARSER_H
#define FTC_PARSER_H

#include "token.h"
#include "display.h"
#include "validation.h"

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
    int threadMode;
};
typedef struct _Parser Parser;

void start_parser(Parser *p, TokenList *l, int argc, char **argv);
int set_opt_parser(Parser *p, TokenList *l, Options opt, int argc, char **argv, int pos);

#endif // FTC_PARSER_H
