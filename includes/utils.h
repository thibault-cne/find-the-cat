#ifndef FTC_UTILS_H
#define FTC_UTILS_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <libgen.h>

// Include mime utils
#include "mime.h"

// Include files utils
#include "files.h"

// Get the size of a file
// @param path the path to the file
// @return the size of the file
long get_file_size(const char *file_path);

// Get the last modification time of a file in seconds
// @param path the path to the file
// @return the last modification time of the file in seconds
double get_seconds_from_last_modification(const char *file_path);

// Check the match between a string and a pattern
// @param str the string to match
// @param pattern the pattern to match
// @return 0 if the string matches the pattern, 1 otherwise
int regex_match(const char *str, const char *pattern);

// Get the last directory of a path
// @param path the path to the file
// @return the last directory of the path
char *get_last_dir(const char *path);

// Check if a path is a directory
// @param path the path to the file
// @return 1 if the path is a directory, 0 otherwise
int is_dir(const char *path);

// Format the path and remove the last slash if it exists
// @param path the path to the file
// @return the formatted path
char *format_entry_path(char *path);

#endif // FTC_UTILS_H
