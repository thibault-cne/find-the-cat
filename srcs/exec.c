/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// exec.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/25 16/11/45
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/exec.h"

// Print the directory path and all the subdirectories paths recursively
void print_subdirectories(const char *path)
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

            print_subdirectories(new_path);
        }
    }
}

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
            if (!reggex_match(entry->d_name, name))
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
            if (reggex_match(file_name, name))
            {
                remove_path_list_index(l, i);
            }
        }
    }
}

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

// Find files by type and put it inside a list
void find_files_by_mime(PathList *l, const char *path, char *mime)
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
            if (!strncmp(file_mime, mime, strlen(mime)))
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
void verify_files_by_mime(PathList *l, char *mime)
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

            if (strncmp(file_mime, mime, strlen(mime)))
            {
                remove_path_list_index(l, i);
            }
        }
    }
}
