#ifndef FTC_MIME_H
#define FTC_MIME_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum
{
    EXTENSION_POS,
    MIME_TYPE,
    ARRAY_SIZE,
};

// Get the mime type of a file. It return NULL if the file is not found or
// an allocated string containing the mime type.
// @param path the path to the file
// @return the mime type of the file
char *get_mime_type(char *filename);

#endif // FTC_MIME_H
