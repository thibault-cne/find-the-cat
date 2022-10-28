/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// exec.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/31/07
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/exec.h"

void exec_parser(Parser *p, TokenList *l, const char *path)
{
    if (!p->orMode)
    {
        if (p->nameMode)
        {
            exec_parser_or_mode_filename(p, l, path);
        }
        else
        {
            exec_parser_or_mode_directory(p, l, path);
        }
    }
}

void exec_parser_or_mode_filename(Parser *p, TokenList *l, const char *path)
{
    PathList pl;
    int i;
    Token *t;

    i = -1;
    create_path_list(&pl, 1);

    t = get_token_list_index(l, ++i);

    switch (t->TokenType)
    {
    case NAME:
        find_files_by_name(&pl, path, t->value);
        break;
    case SIZE:
        find_files_by_size(&pl, path, t->value);
        break;
    case DATE:
        find_files_by_date(&pl, path, t->value);
        break;
    case MIME:
        find_files_by_mime(&pl, path, t->value);
        break;
    case CTC:
        find_files_by_content_pattern(&pl, path, t->value);
        break;
    default:
        return;
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
        case DATE:
            verify_files_by_date(&pl, t->value);
            break;
        case MIME:
            verify_files_by_mime(&pl, t->value);
            break;
        case CTC:
            verify_files_by_content_pattern(&pl, t->value);
            break;
        default:
            break;
        }
    }

    path_display(&pl, p->colorMode);

    destroy_path_list(&pl);
}

void exec_parser_or_mode_directory(Parser *p, TokenList *l, const char *path)
{
    PathList pl;
    int i;
    Token *t;

    i = -1;
    create_path_list(&pl, 1);

    t = get_token_list_index(l, ++i);

    switch (t->TokenType)
    {
    case DIRECTORY:
        if (strcmp(t->value, "dir"))
        {
            find_directories_by_name(&pl, path, t->value);
        }
        else
        {
            get_subdirectories(&pl, path);
        }
        break;
    case DATE:
        find_directories_by_date(&pl, path, t->value);
        break;
    default:
        return;
    }

    while (++i < l->ptr)
    {
        t = get_token_list_index(l, i);
        switch (t->TokenType)
        {
        case DATE:
            verify_files_by_date(&pl, t->value);
            break;
        case DIRECTORY:
            if (strcmp(t->value, "dir"))
            {
                verify_directories_by_name(&pl, t->value);
            }
            break;
        default:
            break;
        }
    }

    path_display(&pl, p->colorMode);

    destroy_path_list(&pl);
}
