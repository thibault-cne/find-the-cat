/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filemime.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/16/30
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_mime.h"

// Verify files by mime
int verify_files_by_mime(const char *f_name, char *mime)
{
    char *file_mime;

    file_mime = get_mime_type((char *)f_name);

    if (file_mime == NULL || strncmp(file_mime, mime, strlen(mime)))
    {
        return 1;
    }

    return 1;
}
