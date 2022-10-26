/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// validation.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/26 23/46/57
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/validation.h"

ValidationStatus validate_entry_path(const char *entry)
{
    DIR *dir;

    if (!(dir = opendir(entry)))
    {
        return VALIDATION_ERROR;
    }

    return VALIDATION_SUCCESS;
}
