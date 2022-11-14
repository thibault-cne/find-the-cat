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
#include "../includes/options.h"
#include "../includes/errors.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        // Run validation on the entry path
        if (!is_dir(argv[1])) {
            printf("Error: please make sure to enter a valid path as first argument.\n");
            exit(1);
        }
        // Remove trailing slash if any
        format_entry_path(argv[1]);

        token_list l;
        parser_t p;

        // Initialize the token list
        create_token_list(&l, 12);

        // Initialize the parser
        start_parser(&p, &l, argc, argv);

        if (p.status != PARSER_SUCCESS) {
            parser_error(&l, p.color_mode, p.error_ptr);

            // Free allocated memory
            destroy_token_list(&l);
            return 1;
        }

        if (p.test_mode) {
            int i;

            i = -1;

            while (++i < l.ptr) {
                token *t = get_token_list_index(&l, i);
                if (t->TokenType != TEST)
                    printf("La valeur du flag %s est %s\n", get_options_flag(t->TokenType), t->value);
            }
        }
        else {
			if (argc == 2)
				p.dir_mode = 1;

            // Run the program
            ft_exec_parser(&p, &l, argv[1]);
        }

        // Free allocated memory
        destroy_token_list(&l);

        return 0;
    }

    return 0;
}
