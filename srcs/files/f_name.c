/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_name.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:32:08 by Thibault Cheneviere                      */
/*   Updated: 2022/11/07 10:32:09 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/f_name.h"

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
