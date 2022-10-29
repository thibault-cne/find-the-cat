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

void parser_error(token_list *l, int isColored, int pos)
{
    token *t;
    printf("%d\n", pos - 2);
    t = get_token_list_index(l, pos - 2);

    if (t == NULL)
    {
        printf("Error: Unknown error\n");
        return;
    }

    if (isColored)
    {
        // Display the error in red
        fprintf(stderr, "Le flag %s n'est pas correct\n", format_text(format_text(get_options_flag(t->TokenType), STYLE_BOLD), COLOR_RED));
    }
    else
    {
        fprintf(stderr, "Le flag %s n'est pas correct\n", get_options_flag(t->TokenType));
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
