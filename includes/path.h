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

void create_path_list(path_list *l, int size);
void add_path_list(path_list *l, char *path);
char *get_path_list_index(path_list *l, int i);
void remove_path_list_index(path_list *l, int i);
void destroy_path_list(path_list *l);

#endif // FTC_PATH_H
