#ifndef FTC_VALIDATION_H
#define FTC_VALIDATION_H

#include <dirent.h>
#include <string.h>

enum _ValidationStatus
{
    VALIDATION_SUCCESS,
    VALIDATION_ERROR,
};
typedef enum _ValidationStatus ValidationStatus;

// Verify if the entry path is valid
// @param entry the path to the entry
// @return 0 if the entry path is valid, 1 otherwise
ValidationStatus validate_entry_path(const char *entry);

// Verify if an entry is an option
// @param entry the string to verify
// @return 1 if the entry is an option, 0 otherwise
int validate_entry_is_not_opt(char *entry);

#endif // FTC_VALIDATION_H
