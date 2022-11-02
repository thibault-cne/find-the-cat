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

// Verify if the file mime type is valid regarding the given mime type.
// We verify mime type by extension
// @param path the path to the file
// @param mime the mime type to compare
// @return 1 if the file mime type is valid, 0 otherwise
int verify_files_by_mime(const char *path, char *mime);

#endif // FTC_F_MIME_H
