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

char *get_mime_type(char *filename);

#endif // FTC_MIME_H
