/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_date.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:31:44 by Thibault Cheneviere                      */
/*   Updated: 2022/11/13 22:08:48 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_files.h"

int verify_files_by_date(const char *path, char *date) {
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
                return 1;
            break;
        default:
            if (file_time <= real_time)
                return 1;
            break;
        }

        return 0;
    }

    return 0;
}

double get_time(char *time)
{
    char *beg;
	char *end;
    int res;

    res = 0;

	beg = time;
	beg += strspn(beg, "-");
	end = beg + strcspn(beg, "mhj");

    res = ft_superatoi(beg, end) * get_time_multiplier(time[strlen(time) - 1]);

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

double get_seconds_from_last_modification(const char *path)
{
    struct stat st;

    if (stat(path, &st) == 0)
    {
        time_t t = st.st_mtime;
        time_t now = time(NULL);

        return difftime(now, t);
    }

    return -1;
}
