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
            if (strcmp(entry->d_name, name) == 0)
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

            if (strcmp(file_name, name) != 0)
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

// Get file size in bytes of a dirent
long get_file_size(const char *file_path)
{
    struct stat st;

    if (stat(file_path, &st) == 0)
    {
        return st.st_size;
    }

    return -1;
}
