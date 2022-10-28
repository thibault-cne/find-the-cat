/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filedate.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/15/23
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_date.h"

// Find files by date and put it inside a list
void find_files_by_date(PathList *l, const char *path, char *date)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;
    double real_date;

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

            find_files_by_date(l, new_path, date);

            // Free allocated memory
            free(new_path);
        }
        else
        {
            new_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
            sprintf(new_path, "%s/%s", path, entry->d_name);

            real_date = get_time(date);

            switch (date[0])
            {
            case '+':
                if (get_seconds_from_last_modification(new_path) > real_date)
                {
                    add_path_list(l, new_path);
                }
                break;
            default:
                if (get_seconds_from_last_modification(new_path) <= real_date)
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

// Verify if files in the path list correspond to the given date
void verify_files_by_date(PathList *l, char *date)
{
    int i;
    char *path;
    double file_time;
    double real_time;

    real_time = get_time(date);

    for (i = 0; i < l->ptr; i++)
    {
        path = get_path_list_index(l, i);

        if (path != NULL)
        {
            file_time = get_seconds_from_last_modification(path);

            switch (date[0])
            {
            case '+':
                if (file_time < real_time)
                {
                    remove_path_list_index(l, i);
                }
                break;
            default:
                if (file_time >= real_time)
                {
                    remove_path_list_index(l, i);
                }
                break;
            }
        }
    }
}

// Find directories by date and put it inside a list
void find_directories_by_date(PathList *l, const char *path, char *date)
{
    DIR *dir;
    struct dirent *entry;
    char *new_path;
    double real_date;

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

            real_date = get_time(date);

            switch (date[0])
            {
            case '+':
                if (get_seconds_from_last_modification(new_path) > real_date)
                {
                    add_path_list(l, new_path);
                }
                break;
            default:
                if (get_seconds_from_last_modification(new_path) <= real_date)
                {
                    add_path_list(l, new_path);
                }
                break;
            }

            find_directories_by_date(l, new_path, date);

            // Free allocated memory
            free(new_path);
        }
    }
}
