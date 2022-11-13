#ifndef FTC_UTILS_H
#define FTC_UTILS_H

#ifdef _WIN32
	#include "windows.h"
#endif // _WIN32

#include <math.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

int get_entry_type(const char *path);

int ft_superatoi(char *beg, char *end);

#endif // FTC_UTILS_H
