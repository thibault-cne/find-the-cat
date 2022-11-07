/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_date.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:31:44 by Thibault Cheneviere                      */
/*   Updated: 2022/11/07 10:31:45 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/f_date.h"

int verify_files_by_date(const char *path, char *date)
{
    double file_time;
    double real_time;

    real_time = get_time(date);

    if (path != NULL)
    {
        file_time = get_seconds_from_last_modification(path);

        switch (date[0])
        {
        case '+':
            if (file_time > real_time)
            {
                return 1;
            }
            break;
        default:
            if (file_time <= real_time)
            {
                return 1;
            }
            break;
        }

        return 0;
    }

    return 0;
}
