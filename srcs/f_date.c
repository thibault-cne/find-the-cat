/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filedate.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/15/23
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_date.h"

// Verify if files in the path list correspond to the given date
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
                return 0;
            }
            break;
        default:
            if (file_time <= real_time)
            {
                return 0;
            }
            break;
        }

        return 1;
    }

    return 1;
}
