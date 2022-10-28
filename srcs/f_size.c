/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filesize.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/13/15
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_size.h"

// Find files by size and put it inside a list
void find_files_by_size(PathList *l, const char *path, char *size)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;
    int real_size;

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

            find_files_by_size(l, new_path, size);

            // Free allocated memory
            free(new_path);
        }
        else
        {
            new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
            sprintf(new_path, "%s/%s", path, entry->d_name);

            real_size = get_size(size);

            switch (size[0])
            {
            case '+':
                if (get_file_size(new_path) > real_size)
                {
                    add_path_list(l, new_path);
                }
                break;
            case '-':
                if (get_file_size(new_path) < real_size)
                {
                    add_path_list(l, new_path);
                }
                break;
            default:
                if (get_file_size(new_path) == real_size)
                {
                    add_path_list(l, new_path);
                }
                break;
            }

            // Free allocated memory
            free(new_path);
        }
    }
}

// Verify if files in the path list correspond to the given size
void verify_files_by_size(PathList *l, char *size)
{
    int i;
    char *path;
    int real_size;

    real_size = get_size(size);

    for (i = 0; i < l->ptr; i++)
    {
        path = get_path_list_index(l, i);

        if (path != NULL)
        {
            switch (size[0])
            {
            case '+':
                if (get_file_size(path) <= real_size)
                {
                    remove_path_list_index(l, i);
                }
                break;
            case '-':
                if (get_file_size(path) >= real_size)
                {
                    remove_path_list_index(l, i);
                }
                break;
            default:
                if (get_file_size(path) != real_size)
                {
                    remove_path_list_index(l, i);
                }
                break;
            }
        }
    }
}
