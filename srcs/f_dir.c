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

void get_subdirectories(PathList *l, const char *path)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;

    // Print the current path
    printf("%s\n", path);

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

            add_path_list(l, new_path);

            get_subdirectories(l, new_path);

            free(new_path);
        }
    }
}

// Find directories by name and put it inside a list
void find_directories_by_name(PathList *l, const char *path, const char *name)
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

            if (!regex_match(entry->d_name, name))
            {
                add_path_list(l, new_path);
            }

            find_directories_by_name(l, new_path, name);

            // Free allocated memory
            free(new_path);
        }
    }
}

// Verify directories by name
void verify_directories_by_name(PathList *l, const char *name)
{
    int i;
    char *path;

    for (i = 0; i < l->ptr; i++)
    {
        path = get_path_list_index(l, i);

        if (path != NULL)
        {
            if (regex_match(get_last_dir(path), name))
            {
                remove_path_list_index(l, i);
            }
        }
    }
}
