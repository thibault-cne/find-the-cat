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

#include "../../includes/f_dir.h"

void display_subdirectories(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;
	int len;

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
			
			len = strlen(path) + strlen(entry->d_name);
            new_path = malloc(len + 2);
            snprintf(new_path, len + 2, "%s/%s", path, entry->d_name);

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