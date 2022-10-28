/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// f_grep.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/26/39
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_grep.h"

// Verify files by content pattern
int verify_files_by_content_pattern(const char *path, const char *pattern)
{
    if (path != NULL)
    {
        return file_contains_pattern(path, pattern);
    }

    return 1;
}
