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

void get_subdirectories(path_list *l, const char *path)
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

// Verify directories by name
int verify_directories_by_name(const char *path, const char *name)
{

    if (path != NULL)
    {
        return regex_match(get_last_dir(path), name);
    }

    return 1;
}
