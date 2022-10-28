/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filemime.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/16/30
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_mime.h"

// Find files by type and put it inside a list
void find_files_by_mime(path_list *l, const char *path, char *mime)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;
    char *file_mime;

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

            find_files_by_mime(l, new_path, mime);

            // Free allocated memory
            free(new_path);
        }
        else
        {
            // Get file mime type
            file_mime = get_mime_type(entry->d_name);
            if (file_mime != NULL && !strncmp(file_mime, mime, strlen(mime)))
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

// Verify files by mime
void verify_files_by_mime(path_list *l, char *mime)
{
    int i;
    char *path;
    char *file_mime;

    for (i = 0; i < l->ptr; i++)
    {
        path = get_path_list_index(l, i);

        if (path != NULL)
        {
            file_mime = get_mime_type(path);

            if (file_mime == NULL || strncmp(file_mime, mime, strlen(mime)))
            {
                remove_path_list_index(l, i);
            }
        }
    }
}
