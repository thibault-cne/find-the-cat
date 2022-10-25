#ifndef FTC_PATH_H
#define FTC_PATH_H

#define PATH_MAX_SIZE 0xFF

#include <stdlib.h>
#include <string.h>

struct _PathList
{
    int ptr;
    int size;
    char **data;
};
typedef struct _PathList PathList;

void create_path_list(PathList *l, int size);
void add_path_list(PathList *l, char *path);
char *get_path_list_index(PathList *l, int i);
void remove_path_list_index(PathList *l, int i);
void destroy_path_list(PathList *l);

#endif // FTC_PATH_H
