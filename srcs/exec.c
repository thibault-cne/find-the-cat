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
    pthread_t *threads;
    pthread_mutex_t mutex;
    thread t;

    create_path_list(&pl, 1);

    // Init mutex and threads
    threads = (pthread_t *)malloc(sizeof(pthread_t) * p->threadMode);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    create_thread(&t, threads, &mutex);

    if (p->dirMode == 1)
    {
        get_subdirectories(&pl, path);
    }
    else
    {
        exec_parser_rec(p, l, &pl, &t, path);
    }

    path_display(&pl, p->colorMode);

    // Destroy mutex and threads
    pthread_mutex_destroy(&mutex);
    free(threads);

    destroy_path_list(&pl);
}

void exec_parser_rec(parser *p, token_list *l, path_list *pl, thread *t, const char *path)
{
    (void)t;
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

            exec_parser_rec(p, l, pl, t, new_path);

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

int validate_file(token_list *l, path_list *pl, struct dirent *entry, const char *path)
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
                return 1;
            }
            break;
        case SIZE:
            if (verify_files_by_size(path, t->value))
            {
                return 1;
            }
            break;
        case MIME:
            if (verify_files_by_mime(entry->d_name, t->value))
            {
                return 1;
            }
            break;
        case CTC:
            if (verify_files_by_content_pattern(path, t->value))
            {
                return 1;
            }
            break;
        case DIRECTORY:
            if (entry->d_type != DT_DIR || verify_directories_by_name(path, t->value))
            {
                return 1;
            }
            break;
        case DATE:
            if (verify_files_by_date(path, t->value))
            {
                return 1;
            }
            break;
        default:
            break;
        }
    }

    add_path_list(pl, (char *)path);
    return 1;
}
