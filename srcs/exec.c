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
    thread_collection t;
    int i;
    thread *th;

    create_path_list(&pl, 1);

    // Init mutex and threads
    threads = (pthread_t *)malloc(sizeof(pthread_t) * p->thread_mode);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    i = -1;
    create_thread_collection(&t, p->thread_mode);
    while (++i < p->thread_mode)
    {
        thread th;
        create_thread(&th, &threads[i], &mutex);
        add_thread(&t, &th);
    }

    if (p->dir_mode == 1)
    {
        t_args_get_subdir args;

        // Get inactive thread
        th = get_thread(&t);

        // Set args inside the args array
        create_t_args_get_subdir(&args, &pl, th, path);

        // Get subdirectories with threads
        pthread_create(th->threads, NULL, (void *)get_subdirectories, (void *)&args);
        pthread_join(*th->threads, NULL);
        th->active = 0;

        // Free args
        destroy_t_args_get_subdir(&args);
    }
    else
    {
        t_arg_exec args;

        // Create args exec
        create_t_arg_exec(&args, p, l, &pl, &t, path);

        if (p->thread_mode > 1)
        {
            th = get_thread(&t);

            // Create thread
            pthread_create(th->threads, NULL, (void *)exec_parser_rec, (void *)&args);
            pthread_join(*th->threads, NULL);
            th->active = 0;
        }
        else
        {
            exec_parser_rec((void *)&args);
        }

        // Free exec args
        destroy_t_arg_exec(&args);
    }

    path_display(&pl, p->color_mode);

    // Destroy mutex and threads
    pthread_mutex_destroy(&mutex);
    free(threads);

    // Destroy path list
    destroy_path_list(&pl);

    // Destroy thread collection
    destroy_thread_collection(&t);
}

void *exec_parser_rec(void *arg_exec)
{
    // Retrieve args
    t_arg_exec *a;
    parser *p;
    token_list *l;
    path_list *pl;
    const char *path;
    thread_collection *t;

    a = (t_arg_exec *)arg_exec;

    p = a->p;
    l = a->l;
    pl = a->pl;
    path = a->path;
    t = a->t;

    // Create thread
    t_arg_exec new_arg_exec;
    thread *th;
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path)))
    {
        closedir(dir);
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        t_arg_validation arg_validation;
        char *new_path;

        new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
        sprintf(new_path, "%s/%s", path, entry->d_name);

        create_t_arg_validation(&arg_validation, pl, l, th, entry, new_path, p->or_mode);

        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // Get inactive thread
            if (!p->name_mode)
            {
                th = get_thread(t);

                // Validate with threads
                pthread_create(th->threads, NULL, (void *)validate_file, (void *)&arg_validation);
                pthread_join(*th->threads, NULL);
                th->active = 0;
            }

            // Create new args
            create_t_arg_exec(&new_arg_exec, p, l, pl, t, new_path);

            exec_parser_rec((void *)&new_arg_exec);

            // Free args
            destroy_t_arg_exec(&new_arg_exec);
        }
        else
        {
            // Check if entry is a symlink
            if (entry->d_type == DT_LNK && p->link_mode)
            {
                // Follow symlink
                char *link_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
                sprintf(link_path, "%s/%s", path, entry->d_name);

                char *real_path = malloc(0x100);
                realpath(link_path, real_path);

                // Check if real path is a directory
                if (is_dir(real_path))
                {
                    // Create new args
                    create_t_arg_exec(&new_arg_exec, p, l, pl, t, real_path);

                    exec_parser_rec((void *)&new_arg_exec);

                    // Free allocated memory
                    free(real_path);
                    free(link_path);

                    // Free args
                    destroy_t_arg_exec(&new_arg_exec);
                }
                else
                {
                    // Free allocated memory
                    free(real_path);
                    free(link_path);
                }
            }

            // Get inactive thread
            th = get_thread(t);

            // Validate with threads
            pthread_create(th->threads, NULL, (void *)validate_file, (void *)&arg_validation);
            pthread_join(*th->threads, NULL);
            th->active = 0;
        }

        // Free allocated memory
        free(new_path);

        // Free args
        destroy_t_arg_validation(&arg_validation);
    }

    closedir(dir);

    return NULL;
}

void *validate_file(void *args)
{
    t_arg_validation *a;
    token_list *l;
    path_list *pl;
    struct dirent *entry;
    char *path;
    token *t;
    int or_mode;

    int i;
    int valid;

    // Get args
    a = (t_arg_validation *)args;
    l = a->tl;
    pl = a->pl;
    entry = a->entry;
    path = a->path;
    or_mode = a->or_mode;

    i = -1;
    valid = 0;

    while (++i < l->ptr)
    {
        t = get_token_list_index(l, i);

        switch (t->TokenType)
        {
        case NAME:
            if ((entry->d_type == DT_DIR || verify_files_by_name(entry->d_name, t->value)) && !or_mode)
            {
                return NULL;
            }
            if ((!(entry->d_type == DT_DIR) && !verify_files_by_name(entry->d_name, t->value)) && or_mode)
            {
                valid = 1;
            }
            break;
        case SIZE:
            if (verify_files_by_size(path, t->value) && !or_mode)
            {
                return NULL;
            }
            if (!verify_files_by_size(path, t->value) && or_mode)
            {
                valid = 1;
            }
            break;
        case MIME:
            if (!verify_files_by_mime(entry->d_name, t->value) && !or_mode)
            {
                return NULL;
            }
            if (verify_files_by_mime(entry->d_name, t->value) && or_mode)
            {
                valid = 1;
            }
            break;
        case CTC:
            if (verify_files_by_content_pattern(path, t->value) && !or_mode)
            {
                return NULL;
            }
            if (!verify_files_by_content_pattern(path, t->value) && or_mode)
            {
                valid = 1;
            }
            break;
        case DIRECTORY:
            if ((entry->d_type != DT_DIR || verify_directories_by_name(path, t->value)) && !or_mode)
            {
                return NULL;
            }
            if (entry->d_type == DT_DIR && !verify_directories_by_name(path, t->value) && or_mode)
            {
                valid = 1;
            }
            break;
        case DATE:
            if (verify_files_by_date(path, t->value) && !or_mode)
            {
                return NULL;
            }
            if (!verify_files_by_date(path, t->value) && or_mode)
            {
                valid = 1;
            }
            break;
        case PERM:
            if (verify_file_perm(path, atoi(t->value)) && !or_mode)
            {
                return NULL;
            }
            if (!verify_file_perm(path, atoi(t->value)) && or_mode)
            {
                valid = 1;
            }
            break;
        default:
            break;
        }
    }

    // Lock mutex
    pthread_mutex_lock(a->t->mutex);

    // Add to path list
    if (valid || !or_mode)
    {
        add_path_list(pl, path);
    }

    // Unlock mutex
    pthread_mutex_unlock(a->t->mutex);
    return NULL;
}
