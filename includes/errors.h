#ifndef FTC_ERRORS_H
#define FTC_ERRORS_H

#include "display.h"
#include "parser.h"

void parser_error(ParserStatus err, int isColored, int pos);
char *get_error_message(ParserStatus err);

#endif // FTC_ERRORS_H
