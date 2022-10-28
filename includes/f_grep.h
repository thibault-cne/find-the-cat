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

// Content pattern functions
int verify_files_by_content_pattern(const char *path, const char *pattern);

#endif // FTC_F_GREP_H
