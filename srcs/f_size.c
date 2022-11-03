/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filesize.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/13/15
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_size.h"

// Verify if files in the path list correspond to the given size
int verify_files_by_size(const char *path, char *size)
{
    int real_size;

    real_size = get_size(size);

    if (path != NULL)
    {
        switch (size[0])
        {
        case '+':
            if (get_file_size(path) > real_size)
            {
                return 1;
            }
            break;
        case '-':
            if (get_file_size(path) < real_size)
            {
                return 1;
            }
            break;
        default:
            if (get_file_size(path) == real_size)
            {
                return 1;
            }
            break;
        }
    }

    return 0;
}
