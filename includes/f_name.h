#ifndef FTC_F_NAME_H
#define FTC_F_NAME_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Filename functions
void find_files_by_name(path_list *l, const char *path, char *name);
void verify_files_by_name(path_list *l, char *name);

#endif // FTC_F_NAME_H
