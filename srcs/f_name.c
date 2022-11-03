/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filename.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/11/59
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_name.h"

int verify_files_by_name(const char *f_name, char *name)
{
    int res;

    res = regex_match(f_name, name);

    if (!res)
    {
        return 1;
    }

    return 0;
}
