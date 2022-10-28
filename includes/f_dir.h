#ifndef FTC_F_DIR_H
#define FTC_F_DIR_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"
#include "thread.h"

struct _t_args
{
    path_list *pl;
    char *path;
    thread *t;
};
typedef struct _t_args t_args;

void *get_subdirectories(void *args);

// Directory functions
int verify_directories_by_name(const char *path, const char *name);

void create_t_arg(t_args *a, path_list *pl, thread *t, const char *path);
void destroy_t_arg(t_args *a);

#endif // FTC_F_DIR_H
