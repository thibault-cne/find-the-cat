/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_grep.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/13 00:37:13 by Thibault Cheneviere                      */
/*   Updated: 2022/11/13 00:37:21 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_file.h"

int verify_files_by_content_pattern(const char *path, const char *pattern) {
    if (path != NULL)
        return file_contains_pattern(path, pattern);

    return 0;
}

char *read_ascii_file(const char *path) {
    FILE *f;
    int size;

    f = fopen(path, "r");

    if (!f)
    {
        printf("Couldn't open the following file : %s\n", path);
        return NULL;
    }

    // Get the file size
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);

    // Read file and put it in a buffer
    char *buf = (char *)malloc(sizeof(char) * size + 1);

    if (!buf)
    {
        printf("Couldn't allocate memory for buffer.\n");
        return NULL;
    }

    fread(buf, 1, size, f);
    buf[size] = '\0';
    fclose(f);

    return buf;
}

int file_contains_pattern(const char *path, const char *pattern)
{
    char *buf;

    buf = read_ascii_file(path);

    if (buf == NULL)
    {
        printf("Couldn't read the file.\n");
        return 0;
    }

    if (!regex_match(buf, pattern))
    {
        free(buf);
        return 1;
    }

    free(buf);
    return 0;
}

