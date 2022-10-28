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

void get_subdirectories(path_list *l, const char *path);

// Directory functions
int verify_directories_by_name(const char *path, const char *name);

#endif // FTC_F_DIR_H
