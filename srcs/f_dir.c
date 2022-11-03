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
    t_args_get_subdir *a;
    t_args_get_subdir new_args;
    char *new_path;

    a = (t_args_get_subdir *)args;

    if (!(dir = opendir(a->path)))
        return (NULL);

    // Lock mutex and add in list
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

            create_t_args_get_subdir(&new_args, a->pl, a->t, new_path);

            get_subdirectories((void *)&new_args);

            // Free allocated memory
            destroy_t_args_get_subdir(&new_args);
            free(new_path);
        }
    }

    closedir(dir);

    return (NULL);
}

void display_subdirectories(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;

    if (!(dir = opendir(path)))
    {
        return;
    }

    printf("%s\n", path);

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
            sprintf(new_path, "%s/%s", path, entry->d_name);

            display_subdirectories(new_path);

            // Free allocated memory
            free(new_path);
        }
        else
        {
            printf("%s/%s\n", path, entry->d_name);
        }
    }

    closedir(dir);

    return;
}

int verify_directories_by_name(const char *path, const char *name)
{
    char *last_dir;
    int i;

    if (path != NULL)
    {
        last_dir = get_last_dir(path);

        i = regex_match(last_dir, name);

        free(last_dir);

        if (!i)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}
