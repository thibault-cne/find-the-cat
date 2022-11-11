/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_date.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:31:44 by Thibault Cheneviere                      */
/*   Updated: 2022/11/11 21:47:15 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_file.h"

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

double get_time(char *time)
{
    int i;
    int offset;
    char *new_time;
    int res;

    res = 0;

    if (time[0] == '-' || time[0] == '+')
    {
        i = 0;
        offset = 1;
    }
    else
    {
        i = -1;
        offset = 0;
    }

    new_time = malloc(sizeof(char) * OPTS_MAX_SIZE);

    while (time[++i] < 57 && time[i] > 48)
    {
        new_time[i - offset] = time[i];
    }
    new_time[i] = '\0';

    res = atoi(new_time) * get_time_multiplier(time[i]);

    // Free memory
    free(new_time);

    return (double)res;
}

int get_time_multiplier(char s)
{
    switch (s)
    {
    case 'm':
        return TIME_MIN;
    case 'h':
        return TIME_H;
    case 'j':
        return TIME_D;
    default:
        return TIME_S;
    }
}

double get_seconds_from_last_modification(const char *file_path)
{
    struct stat st;
    char *cp_path;

    cp_path = (char *)malloc(sizeof(char) * (strlen(file_path) + 1));
    strcpy(cp_path, file_path);

    if (stat(cp_path, &st) == 0)
    {
        time_t t = st.st_mtime;
        time_t now = time(NULL);

        // Free memory
        free(cp_path);

        return difftime(now, t);
    }

    // Free memory
    free(cp_path);

    return -1;
}
