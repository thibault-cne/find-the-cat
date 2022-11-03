#ifndef FTC_F_NAME_H
#define FTC_F_NAME_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Verify if the name of a file is valid
// @param f_name the name of the file
// @param name the name to compare or a pattern(regex)
// @return 1 if the name is valid, 0 otherwise
int verify_files_by_name(const char *f_name, char *name);

#endif // FTC_F_NAME_H
