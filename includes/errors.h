#ifndef FTC_ERRORS_H
#define FTC_ERRORS_H

#include <errno.h>

#include "display.h"
#include "parser.h"

void parser_error(token_list *l, int isColored, int pos);
char *get_error_message(parser_status err);

#endif // FTC_ERRORS_H
