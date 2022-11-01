#ifndef FTC_PATH_H
#define FTC_PATH_H

#define PATH_MAX_SIZE 0xFF

#include <stdlib.h>
#include <string.h>

struct _path_list
{
    int ptr;
    int size;
    char **data;
};
typedef struct _path_list path_list;

// Create a new path list
// @param l the path list pointer
// @param size the size of the path list
void create_path_list(path_list *l, int size);

// Add a path to the path list
// @param l the path list pointer
// @param path the path to add
void add_path_list(path_list *l, char *path);

// Get the path at the given index
// @param l the path list pointer
// @param index the index of the path
// @return the path at the given index
char *get_path_list_index(path_list *l, int i);

// Remove the path at the given index
// @param l the path list pointer
// @param index the index of the path
void remove_path_list_index(path_list *l, int i);

// Free the path list
// @param l the path list pointer
void destroy_path_list(path_list *l);

#endif // FTC_PATH_H
