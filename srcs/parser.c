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

void start_parser(parser *p, token_list *l, int argc, char **argv)
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
            p->errorPtr = i;
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

int set_opt_parser(parser *p, token_list *l, Options opt, int argc, char **argv, int pos)
{
    token t;
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
    case DIRECTORY:
        if (p->nameMode == 1)
        {
            p->status = PARSER_ERROR;
            p->errorPtr = pos;
            return 0;
        }
        p->nameMode = 0;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            create_token(&t, pos, opt, "dir");
            p->dirMode = 1;
        }
        break;
    case NAME:
        if (p->nameMode == 0)
        {
            p->status = PARSER_ERROR;
            p->errorPtr = pos;
            return 0;
        }
        p->nameMode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->errorPtr = pos;
            return 0;
        }
        break;
    case SIZE:
        if (p->nameMode == 0)
        {
            p->status = PARSER_ERROR;
            p->errorPtr = pos;
            return 0;
        }
        p->nameMode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->errorPtr = pos;
            return 0;
        }
        break;
    case DATE:
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->errorPtr = pos;
            return 0;
        }
        break;
    case MIME:
        if (p->nameMode == 0)
        {
            p->status = PARSER_ERROR;
            p->errorPtr = pos;
            return 0;
        }
        p->nameMode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->errorPtr = pos;
            return 0;
        }
        break;
    case CTC:
        if (p->nameMode == 0)
        {
            p->status = PARSER_ERROR;
            p->errorPtr = pos;
            return 0;
        }
        p->nameMode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->errorPtr = pos;
            return 0;
        }
        break;
    case THREADS:
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            p->threadMode = atoi(argv[pos + 1]);
            // Verify if thread number is greater than one
            if (p->threadMode < 1)
            {
                p->status = PARSER_INVALID_PARAMETER;
                p->errorPtr = pos;
                return 0;
            }
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->errorPtr = pos;
            return 0;
        }
        break;
    default:
        p->status = PARSER_INVALID_OPTION;
        p->errorPtr = pos;
        return 0;
    }

    add_token_list(l, t);

    // Destroy used token
    destroy_token(&t);
    return incr;
}
