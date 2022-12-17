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

void parser_error(token_list *l, int isColored, int pos, parser_status status) {
    token *t;
    t = get_token_list_index(l, pos);

    if (t == NULL) {
        fprintf(stderr, "Error : %s\n", get_error_message(status));
        return;
    }

    if (isColored) {
        // Display the error in red
        if (t->TokenType == NONE)
            f_printf(stdout, "Le flag |COLOR_RED|STYLE_BOLD|%s|S| n'est pas correct\n", t->value);
        else
            f_printf(stdout, "Le flag |COLOR_RED|STYLE_BOLD|%s|S| n'est pas correct\n", get_options_flag(t->TokenType));
    }
    else {
        if (t->TokenType == NONE)
            fprintf(stdout, "Le flag %s n'est pas correct\n", t->value);
        else
            fprintf(stdout, "Le flag %s n'est pas correct\n", get_options_flag(t->TokenType));
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
