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

// Filename functions
int verify_files_by_name(const char *f_name, char *name);

#endif // FTC_F_NAME_H
