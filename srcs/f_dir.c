/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// f_dir.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/24/09
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_dir.h"

void *get_subdirectories(void *args)
{
    DIR *dir;
    struct dirent *entry;
    t_args *a;
    t_args new_args;
    char *new_path;

    a = (t_args *)args;

    if (!(dir = opendir(a->path)))
        return (NULL);

    // Lock mutex
    pthread_mutex_lock(a->t->mutex);
    add_path_list(a->pl, (char *)a->path);
    pthread_mutex_unlock(a->t->mutex);

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            new_path = malloc(strlen(a->path) + strlen(entry->d_name) + 2);
            sprintf(new_path, "%s/%s", a->path, entry->d_name);

            create_t_arg(&new_args, a->pl, a->t, new_path);

            get_subdirectories((void *)&new_args);

            destroy_t_arg(&new_args);
            free(new_path);
        }
    }
    return (NULL);
}

// Verify directories by name
int verify_directories_by_name(const char *path, const char *name)
{

    if (path != NULL)
    {
        return regex_match(get_last_dir(path), name);
    }

    return 1;
}

void create_t_arg(t_args *a, path_list *pl, thread *t, const char *path)
{
    a->pl = pl;
    a->t = t;
    a->path = malloc(sizeof(char) * strlen(path) + 1);
    strcpy(a->path, path);
}

void destroy_t_arg(t_args *a)
{
    free(a->path);
}
