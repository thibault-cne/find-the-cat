#ifndef FTC_EXEC_H
#define FTC_EXEC_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Debuf functions
void print_subdirectories(const char *path);

// Filename functions
void find_files_by_name(PathList *l, const char *path, char *name);
void verify_files_by_name(PathList *l, char *name);

// Size functions
void find_files_by_size(PathList *l, const char *path, char *size);
void verify_files_by_size(PathList *l, char *size);

// Date functions
void find_files_by_date(PathList *l, const char *path, char *date);
void verify_files_by_date(PathList *l, char *date);

// Mime functions
void find_files_by_mime(PathList *l, const char *path, char *mime);
void verify_files_by_mime(PathList *l, char *mime);

// Content pattern functions
void find_files_by_content_pattern(PathList *l, const char *path, const char *pattern);
void verify_files_by_content_pattern(PathList *l, const char *pattern);

#endif // FTC_EXEC_H
