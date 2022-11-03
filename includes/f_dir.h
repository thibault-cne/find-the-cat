#ifndef FTC_F_DIR_H
#define FTC_F_DIR_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"
#include "thread.h"
#include "t_arg.h"

// Get all subdirectories of a given directory
// @param args a pointer to the functions arguments
void *get_subdirectories(void *args);

// Display all subdirectories of a given directory
// @param path the path to the directory
void display_subdirectories(const char *path);

// Verify if the name of a directory is valid
// @param path the path to the file
// @param name the name of the file
// @return 1 if the name is valid, 0 otherwise
int verify_directories_by_name(const char *path, const char *name);

#endif // FTC_F_DIR_H
