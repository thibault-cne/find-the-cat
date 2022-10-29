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

    p->color_mode = 0;
    p->or_mode = 0;
    p->test_mode = 0;
    p->status = PARSER_SUCCESS;

    while (++i < argc)
    {
        if (!argv[i])
        {
            p->status = PARSER_ERROR;
            p->error_ptr = i;
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
        p->test_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            create_token(&t, pos, opt, "test");
        }
        break;
    case COLOR:
        p->color_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            create_token(&t, pos, opt, "color");
        }
        break;
    case OR:
        p->or_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            create_token(&t, pos, opt, "or");
        }
        break;
    case LINK:
        p->link_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            create_token(&t, pos, opt, "link");
        }
        break;
    case DIRECTORY:
        if (p->name_mode == 1)
        {
            p->status = PARSER_ERROR;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        p->name_mode = 0;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            create_token(&t, pos, opt, "dir");
            p->dir_mode = 1;
        }
        break;
    case NAME:
        if (p->name_mode == 0)
        {
            p->status = PARSER_ERROR;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        p->name_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        break;
    case SIZE:
        if (p->name_mode == 0)
        {
            p->status = PARSER_ERROR;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        p->name_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
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
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        break;
    case MIME:
        if (p->name_mode == 0)
        {
            p->status = PARSER_ERROR;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        p->name_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        break;
    case CTC:
        if (p->name_mode == 0)
        {
            p->status = PARSER_ERROR;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        p->name_mode = 1;
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        break;
    case THREADS:
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            p->thread_mode = atoi(argv[pos + 1]);
            // Verify if thread number is greater than one
            if (p->thread_mode < 1)
            {
                p->status = PARSER_INVALID_PARAMETER;
                p->error_ptr = pos;

                create_token(&t, pos, opt, "");
                return 0;
            }
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        break;
    case PERM:
        if (pos + 1 < argc && !validate_entry_is_not_opt(argv[pos + 1]))
        {
            create_token(&t, pos, opt, argv[pos + 1]);
            incr = 1;
        }
        else
        {
            p->status = PARSER_PARAM_MISSING;
            p->error_ptr = pos;

            create_token(&t, pos, opt, "");
            add_token_list(l, t);

            // Destroy used token
            destroy_token(&t);
            return 0;
        }
        break;
    default:
        p->status = PARSER_INVALID_OPTION;
        p->error_ptr = pos;

        create_token(&t, pos, NONE, argv[pos]);
        add_token_list(l, t);

        // Destroy used token
        destroy_token(&t);
        return 0;
    }

    add_token_list(l, t);

    // Destroy used token
    destroy_token(&t);
    return incr;
}
