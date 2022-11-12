/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_name.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:32:08 by Thibault Cheneviere                      */
/*   Updated: 2022/11/13 00:53:10 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_files.h"

int verify_files_by_name(const char *f_name, char *name) {
    int res;

    res = regex_match(f_name, name);

    if (!res)
        return 1;

    return 0;
}

int regex_match(const char *str, const char *pattern) {
    regex_t regex;
    int reti;
    int res;

    reti = regcomp(&regex, pattern, 0);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex %s\n", pattern);
        exit(1);
    }

    res = regexec(&regex, str, 0, NULL, 0);

    // Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);
    return res;
}
