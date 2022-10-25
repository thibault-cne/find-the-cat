#ifndef FTC_EXEC_H
#define FTC_EXEC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "options.h"
#include "path.h"

// Debuf functions
void print_subdirectories(const char *path);

// Filename functions
void find_files_by_name(PathList *l, const char *path, char *name);
void verify_files_by_name(PathList *l, char *name);

// Size functions
void find_files_by_size(PathList *l, const char *path, char *size);
void verify_files_by_size(PathList *l, char *size);

// Utility functions
long get_file_size(const char *file_path);

#endif // FTC_EXEC_H
