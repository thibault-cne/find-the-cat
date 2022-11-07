/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_size.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:31:33 by Thibault Cheneviere                      */
/*   Updated: 2022/11/07 19:16:38 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/f_size.h"

// Verify if files in the path list correspond to the given size
int verify_files_by_size(const char *path, char *size)
{
    off_t real_size;

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

