#ifndef FTC_F_SIZE_H
#define FTC_F_SIZE_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Size functions
void find_files_by_size(PathList *l, const char *path, char *size);
void verify_files_by_size(PathList *l, char *size);

#endif // FTC_F_SIZE_H
