/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_mime.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:31:59 by Thibault Cheneviere                      */
/*   Updated: 2022/11/13 00:52:39 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_files.h"

// Verify files by mime
int verify_files_by_mime(const char *f_name, char *mime) {
    char *file_mime;

    file_mime = get_mime_type((char *)f_name);

    if (file_mime == NULL)
        return 0;

    if ((!strcmp(file_mime, mime) || !strncmp(file_mime, mime, strlen(mime))))
    {
        free(file_mime);
        return 1;
    }

    free(file_mime);
    return 0;
}
