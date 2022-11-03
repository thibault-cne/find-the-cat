#ifndef FTC_F_DATE_H
#define FTC_F_DATE_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "options.h"
#include "path.h"
#include "utils.h"

// Verify if the file modification date is valid regarding the given date
// @param path the path to the file
// @param date the date to compare
// @return 1 if the file modification date is valid, 0 otherwise
int verify_files_by_date(const char *path, char *date);

#endif // FTC_F_DATE_H
