#ifndef FTC_PARSER_H
#define FTC_PARSER_H

#include "token.h"
#include "display.h"
#include "validation.h"

enum _parser_status
{
    PARSER_SUCCESS,
    PARSER_ERROR,
    PARSER_INVALID_OPTION,
    PARSER_PARAM_MISSING,
    PARSER_INVALID_PARAMETER,
};
typedef enum _parser_status parser_status;

struct _parser
{
    parser_status status;
    int error_ptr;
    int test_mode;
    int color_mode;
    int or_mode;
    int name_mode;
    int dir_mode;
    int thread_mode;
    int link_mode;
};
typedef struct _parser parser;

// Start parsing the command line
// @param p the parser
// @param l the token list
// @param argc the number of arguments
// @param argv the arguments
void start_parser(parser *p, token_list *l, int argc, char **argv);

// Add a token to the token list
// @param p the parser
// @param l the token list
// @param opt the option type
// @param argc the number of arguments
// @param argv the arguments
// @param pos the current position
// @return the offset of the next token
int set_opt_parser(parser *p, token_list *l, Options opt, int argc, char **argv, int pos);

#endif // FTC_PARSER_H
