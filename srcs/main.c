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

#include "../includes/exec.h"
#include "../includes/f_dir.h"
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

        token_list l;
        parser p;

        // Initialize the token list
        create_token_list(&l, 1);

        // Initialize the parser
        p.nameMode = -1;
        p.threadMode = 1;

        start_parser(&p, &l, argc, argv);

        if (p.status != PARSER_SUCCESS)
        {
            parser_error(p.status, p.colorMode, p.errorPtr);
            return 1;
        }

        if (p.testMode)
        {
            path_list pl;
            int i;

            create_path_list(&pl, 1);
            i = -1;

            while (++i < l.ptr)
            {
                token *t = get_token_list_index(&l, i);
                printf("Value of flag %s is %s\n", get_options_flag(t->TokenType), t->value);
            }

            printf("\nDisplay all subdirectories\n");
            get_subdirectories(&pl, argv[1]);
            path_display(&pl, 0);

            // Free the path list
            destroy_path_list(&pl);
        }
        else
        {
            // Run the program
            exec_parser(&p, &l, argv[1]);
        }

        // Free allocated memory
        destroy_token_list(&l);

        return 0;
    }
    else
    {
        char *buf;

        buf = read_ascii_file("./baz/bar/baz/bar/ftc.txt");

        printf("%s\n", buf);
        printf("%d\n", regex_match(buf, "From here"));

        free(buf);
    }

    return 0;
}
