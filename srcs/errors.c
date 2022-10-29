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

void parser_error(parser_status err, int isColored, int pos)
{
    if (isColored)
    {
        // Display the error in red
        fprintf(stderr, "(errno:%s) %s: %s at index : %d\n", strerror(errno), format_text(format_text("Error", STYLE_BOLD), COLOR_RED), get_error_message(err), pos);
        display_help(isColored);
    }
    else
    {
        fprintf(stderr, "(errno:%s) %s: %s at index : %d\n", strerror(errno), "Error", get_error_message(err), pos);
        display_help(isColored);
    }
}

char *get_error_message(parser_status err)
{
    switch (err)
    {
    case PARSER_INVALID_OPTION:
        return "Invalid argument";
    case PARSER_ERROR:
        return "Parser error";
    case PARSER_PARAM_MISSING:
        return "Missing parameter";
    case PARSER_INVALID_PARAMETER:
        return "Invalid parameter";
    default:
        return "Unknown error";
    }
}
