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

void get_subdirectories(PathList *l, const char *path);

// Directory functions
void find_directories_by_name(PathList *l, const char *path, const char *name);
void verify_directories_by_name(PathList *l, const char *name);

#endif // FTC_F_DIR_H
