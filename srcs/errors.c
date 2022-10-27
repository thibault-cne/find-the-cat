/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// errors.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/27 08/22/27
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/errors.h"

void parser_error(ParserStatus err, int isColored, int pos)
{
    if (isColored)
    {
        printf("%s: %s at index : %d\n", format_text(format_text("Error", STYLE_BOLD), COLOR_RED), get_error_message(err), pos);
        display_help(isColored);
    }
    else
    {
        printf("%s: %s at index : %d\n", "Error", get_error_message(err), pos);
        display_help(isColored);
    }
}

char *get_error_message(ParserStatus err)
{
    switch (err)
    {
    case PARSER_INVALID_OPTION:
        return "Invalid argument";
    case PARSER_ERROR:
        return "Parser error";
    case PARSER_PARAM_MISSING:
        return "Missing parameter";
    default:
        return "Unknown error";
    }
}
