#ifndef FTC_ERRORS_H
#define FTC_ERRORS_H

#include <errno.h>

#include "display.h"
#include "parser.h"

// Display a parser_t error
// @param l the token list
// @param isColored if the color is enable
// @param pos the position of the error
void parser_error(token_list *l, int isColored, int pos);

// Get the error message from a parser_t status
// @param err the parser_t status
char *get_error_message(parser_status err);

#endif // FTC_ERRORS_H
