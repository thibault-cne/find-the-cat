#ifndef FTC_VALIDATION_H
#define FTC_VALIDATION_H

#include <dirent.h>

enum _ValidationStatus
{
    VALIDATION_SUCCESS,
    VALIDATION_ERROR,
};
typedef enum _ValidationStatus ValidationStatus;

ValidationStatus validate_entry_path(const char *entry);

#endif // FTC_VALIDATION_H
