/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// f_grep.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/26/39
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_grep.h"

// Find files that contain a given pattern and put it inside a list
void find_files_by_content_pattern(PathList *l, const char *path, const char *pattern)
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

            find_files_by_content_pattern(l, new_path, pattern);

            // Free allocated memory
            free(new_path);
        }
        else
        {
            new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
            sprintf(new_path, "%s/%s", path, entry->d_name);

            if (!file_contains_pattern(new_path, pattern))
            {
                add_path_list(l, new_path);
            }

            // Free allocated memory
            free(new_path);
        }
    }
}

// Verify files by content pattern
void verify_files_by_content_pattern(PathList *l, const char *pattern)
{
    int i;
    char *path;

    for (i = 0; i < l->ptr; i++)
    {
        path = get_path_list_index(l, i);

        if (path != NULL)
        {
            if (file_contains_pattern(path, pattern))
            {
                remove_path_list_index(l, i);
            }
        }
    }
}
