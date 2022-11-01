#ifndef FTC_F_GREP_H
#define FTC_F_GREP_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Verify if the file content contains the given string
// @param path the path to the file
// @param pattern the string to search
// @return 0 if the file content contains the given string, 1 otherwise
int verify_files_by_content_pattern(const char *path, const char *pattern);

#endif // FTC_F_GREP_H
