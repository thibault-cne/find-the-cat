#ifndef FTC_F_MIME_H
#define FTC_F_MIME_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Mime functions
int verify_files_by_mime(const char *path, char *mime);

#endif // FTC_F_MIME_H
