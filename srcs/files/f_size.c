/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   f_size.c                                                                 */
/*                                                                            */
/*   By: Thibault Cheneviere <thibault.cheneviere@telecomnancy.eu>            */
/*                                                                            */
/*   Created: 2022/11/07 10:31:33 by Thibault Cheneviere                      */
/*   Updated: 2022/11/11 21:46:45 by Thibault Cheneviere                      */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_file.h"

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

off_t get_size(char *size)
{
    char *new_size;
	char *beg;
	char *end;
	char *temp;
    off_t res;

    new_size = malloc(sizeof(char) * strlen(size) + 1);
	strcpy(new_size, size);

	beg = new_size;
	end = new_size;

	beg += strspn(beg, "-+");
	end = beg + strcspn(beg, "ckMG");

	temp = (char *)malloc(sizeof(char) * ((int)(end - beg) + 1));
	strncpy(temp, beg, (int)(end - beg));

	res = atoi(temp);

    // Free memory
	free(temp);
    free(new_size);

    return res * get_multiplier(size[strlen(size) - 1]);
}

int get_multiplier(char s)
{
    switch (s)
    {
    case 'k':
        return SIZE_KIB;
    case 'M':
        return SIZE_MIB;
    case 'G':
        return SIZE_GIB;
    default:
        return SIZE_C;
    }
}

off_t get_file_size(const char *file_path)
{
    struct stat st;

    if (stat(file_path, &st) == 0)
    {
        return st.st_size;
    }

    return -1;
}
