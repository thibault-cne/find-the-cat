/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// main.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/24 15/20/20
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../includes/parser.h"
#include "../includes/exec.h"
#include "../includes/options.h"
#include "../includes/validation.h"
#include "../includes/errors.h"

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        // Run validation on the entry path
        if (validate_entry_path(argv[1]) != VALIDATION_SUCCESS)
        {
            printf("Error: please make sure to enter a valid path as first argument.\n");
            return 1;
        }

        TokenList l;
        Parser p;

        create_token_list(&l, 1);

        start_parser(&p, &l, argc, argv);

        if (p.status != PARSER_SUCCESS)
        {
            parser_error(p.status, p.colorMode, p.errorPtr);
            return 1;
        }

        if (p.testMode)
        {
            int i;

            i = -1;

            while (++i < l.ptr)
            {
                Token *t = get_token_list_index(&l, i);
                printf("Value of flag %s is %s\n", get_options_flag(t->TokenType), t->value);
            }

            printf("\nDisplay all subdirectories\n");
            print_subdirectories(argv[1]);
        }
        else
        {
            exec_parser(&p, &l, argv[1]);
        }

        // Free allocated memory
        destroy_token_list(&l);

        return 0;
    }
    else
    {
        printf("%d\n", reggex_match("moi", "[mt]oi"));
        printf("%d\n", reggex_match("toi", "[mt]oi"));
    }

    return 0;
}
