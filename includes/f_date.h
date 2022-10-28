#ifndef FTC_F_DATE_H
#define FTC_F_DATE_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Date functions
void find_files_by_date(PathList *l, const char *path, char *date);
void verify_files_by_date(PathList *l, char *date);
void find_directories_by_date(PathList *l, const char *path, char *date);

#endif // FTC_F_DATE_H
