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

int validate_entry_is_not_opt(char *entry)
{
    if (!strcmp(entry, "-test"))
    {
        return 1;
    }
    if (!strcmp(entry, "-size"))
    {
        return 1;
    }
    if (!strcmp(entry, "-name"))
    {
        return 1;
    }
    if (!strcmp(entry, "-date"))
    {
        return 1;
    }
    if (!strcmp(entry, "-mime"))
    {
        return 1;
    }
    if (!strcmp(entry, "-ctc"))
    {
        return 1;
    }
    if (!strcmp(entry, "-dir"))
    {
        return 1;
    }
    if (!strcmp(entry, "-color"))
    {
        return 1;
    }
    if (!strcmp(entry, "-perm"))
    {
        return 1;
    }
    if (!strcmp(entry, "-link"))
    {
        return 1;
    }
    if (!strcmp(entry, "-threads"))
    {
        return 1;
    }
    if (!strcmp(entry, "-ou"))
    {
        return 1;
    }
    return 0;
}
