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

void exec_parser(parser *p, token_list *l, const char *path)
{
    path_list pl;
    create_path_list(&pl, 1);

    exec_parser_rec(p, l, &pl, path);

    path_display(&pl, p->colorMode);
}

void exec_parser_rec(parser *p, token_list *l, path_list *pl, const char *path)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;

    if (!(dir = opendir(path)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
            sprintf(new_path, "%s/%s", path, entry->d_name);

            validate_file(l, pl, entry, new_path);

            exec_parser_rec(p, l, pl, new_path);

            // Free allocated memory
            free(new_path);
        }
        else
        {
            new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
            sprintf(new_path, "%s/%s", path, entry->d_name);

            validate_file(l, pl, entry, new_path);

            // Free allocated memory
            free(new_path);
        }
    }

    closedir(dir);
}

void validate_file(token_list *l, path_list *pl, struct dirent *entry, const char *path)
{
    int i;
    token *t;

    i = -1;

    while (++i < l->ptr)
    {
        t = get_token_list_index(l, i);

        switch (t->TokenType)
        {
        case NAME:
            if (entry->d_type == DT_DIR || verify_files_by_name(entry->d_name, t->value))
            {
                return;
            }
            break;
        case SIZE:
            if (verify_files_by_size(path, t->value))
            {
                return;
            }
            break;
        case MIME:
            if (verify_files_by_mime(entry->d_name, t->value))
            {
                return;
            }
            break;
        case CTC:
            if (verify_files_by_content_pattern(path, t->value))
            {
                return;
            }
            break;
        case DIRECTORY:
            if (entry->d_type != DT_DIR || verify_directories_by_name(path, t->value))
            {
                return;
            }
            break;
        case DATE:
            if (verify_files_by_date(path, t->value))
            {
                return;
            }
            break;
        default:
            break;
        }
    }

    add_path_list(pl, (char *)path);
}
