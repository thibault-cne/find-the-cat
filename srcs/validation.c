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

#define __flags

#include "../includes/validation.h"

int validate_entry_is_not_opt(char *entry)
{
    int i;

    i = -1;

    while (flags[++i])
    {
        if (!strcmp(entry, flags[i]))
            return 1;
    }

    return 0;
}
