/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// parser.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/24 15/20/44
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/parser.h"

void start_parser(Parser *p, TokenList *l, int argc, char **argv)
{
    int i;
    int incr;

    i = 1;
    incr = 0;

    p->colorMode = 0;
    p->orMode = 0;
    p->testMode = 0;
    p->status = PARSER_SUCCESS;

    while (++i < argc)
    {
        if (!argv[i])
        {
            p->status = PARSER_ERROR;
            return;
        }

        if (argv[i][0] == '-')
        {
            // Add the flag and its value inside the token list
            // Remembre to check for test flag which has no value
            Options opt = get_flag_options(argv[i]);

            incr = set_opt_parser(p, l, opt, argc, argv, i);

            i += incr;
        }
    }

    return;
}

int set_opt_parser(Parser *p, TokenList *l, Options opt, int argc, char **argv, int pos)
{
    Token t;
    int incr;

    incr = 0;

    switch (opt)
    {
    case TEST:
        p->testMode = 1;
        create_token(&t, pos, opt, "test");
        break;
    case COLOR:
        p->colorMode = 1;
        create_token(&t, pos, opt, "color");
        break;
    case OR:
        p->orMode = 1;
        create_token(&t, pos, opt, "or");
        break;
    case NAME:
        if (pos + 1 < argc)
        {
            p->nameMode = 1;
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_ERROR;
            return 0;
        }
        break;
    case SIZE:
        if (pos + 1 < argc)
        {
            p->sizeMode = 1;
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_ERROR;
            return 0;
        }
        break;
    default:
        p->status = PARSER_ERROR;
        return 0;
    }

    add_token_list(l, t);

    // Destroy used token
    destroy_token(&t);
    return incr;
}

void exec_parser(Parser *p, TokenList *l, const char *path)
{
    if (!p->orMode)
    {
        PathList pl;
        int i;
        Token *t;

        i = -1;
        create_path_list(&pl, 1);

        t = get_token_list_index(l, ++i);

        switch (t->TokenType)
        {
            {
            case NAME:
                find_files_by_name(&pl, path, t->value);
                break;
            case SIZE:
                find_files_by_size(&pl, path, t->value);
                break;
            default:
                return;
            }
        }

        while (++i < l->ptr)
        {
            t = get_token_list_index(l, i);

            switch (t->TokenType)
            {
            case NAME:
                verify_files_by_name(&pl, t->value);
                break;
            case SIZE:
                verify_files_by_size(&pl, t->value);
                break;
            default:
                break;
            }
        }

        path_display(&pl, p->colorMode);

        destroy_path_list(&pl);
    }
}
