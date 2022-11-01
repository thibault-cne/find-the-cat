#ifndef FTC_F_SIZE_H
#define FTC_F_SIZE_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Verify if the file size is valid regarding the given size
// @param path the path to the file
// @param size the size to compare
// @return 0 if the file size is valid, 1 otherwise
int verify_files_by_size(const char *path, char *size);

#endif // FTC_F_SIZE_H
