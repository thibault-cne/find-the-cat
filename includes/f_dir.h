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

void *get_subdirectories(void *args);

// Directory functions
int verify_directories_by_name(const char *path, const char *name);

#endif // FTC_F_DIR_H
