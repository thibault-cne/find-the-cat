#ifndef FTC_FILES_H
#define FTC_FILES_H

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// Read ascii files
char *read_ascii_file(const char *path);

int file_contains_pattern(const char *path, const char *pattern);

#endif // FTC_FILES_H
