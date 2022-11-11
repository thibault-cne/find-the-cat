/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// f_dir.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/24/09
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../../includes/ft_file.h"

int verify_directories_by_name(const char *path, const char *name)
{
    char *last_dir;
    int i;

    if (path != NULL)
    {
        last_dir = get_last_dir(path);

        i = regex_match(last_dir, name);

        free(last_dir);

        if (!i)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}
