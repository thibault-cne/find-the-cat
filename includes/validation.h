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

ValidationStatus validate_entry_path(const char *entry);
int validate_entry_is_not_opt(char *entry);

#endif // FTC_VALIDATION_H
