#ifndef FTC_FILES_H
#define FTC_FILES_H

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// Read ascii files
// @param path the path to the file
// @return the content of the file
char *read_ascii_file(const char *path);

// Check if a file contains a given string
// @param path the path to the file
// @param pattern the string to search
// @return 1 if the file contains the given string, 0 otherwise
int file_contains_pattern(const char *path, const char *pattern);

#endif // FTC_FILES_H
