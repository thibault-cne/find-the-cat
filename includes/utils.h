#ifndef FTC_UTILS_H
#define FTC_UTILS_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

// Include mime utils
#include "mime.h"

// Include files utils
#include "files.h"

// Utility functions
long get_file_size(const char *file_path);
double get_seconds_from_last_modification(const char *file_path);
int regex_match(const char *str, const char *pattern);

#endif // FTC_UTILS_H
