/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filename.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/11/59
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_name.h"

// Find files by name and put it inside a list
void find_files_by_name(PathList *l, const char *path, char *name)
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

            find_files_by_name(l, new_path, name);

            // Free allocated memory
            free(new_path);
        }
        else
        {
            // reggex_match is for reggex matching
            // use strcmp for exact matching
            if (!regex_match(entry->d_name, name))
            {
                new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
                sprintf(new_path, "%s/%s", path, entry->d_name);

                add_path_list(l, new_path);

                // Free allocated memory
                free(new_path);
            }
        }
    }
}

// Verify if files in the path list correspond to the given name
void verify_files_by_name(PathList *l, char *name)
{
    int i;
    char *path;
    char *file_name;

    for (i = 0; i < l->ptr; i++)
    {
        path = get_path_list_index(l, i);

        if (path != NULL)
        {
            file_name = strrchr(path, '/') + 1;

            // reggex_match is for reggex matching
            // use strcmp for exact matching
            if (regex_match(file_name, name))
            {
                remove_path_list_index(l, i);
            }
        }
    }
}
