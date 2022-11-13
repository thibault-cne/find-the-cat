#ifndef FTC_VALIDATION_H
#define FTC_VALIDATION_H

#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#ifdef __flags
const char *flags[] = {
    "-name", "-size", "-mime", "-ctc", "-perm", "-dir",
    "-date", "-link", "-color", "-threads", "-test", "-ou", NULL};
#endif // __flags

enum _ValidationStatus
{
    VALIDATION_SUCCESS,
    VALIDATION_ERROR,
};
typedef enum _ValidationStatus ValidationStatus;

// Verify if an entry is an option
// @param entry the string to verify
// @return 1 if the entry is an option, 0 otherwise
int validate_entry_is_not_opt(char *entry);

#endif // FTC_VALIDATION_H
