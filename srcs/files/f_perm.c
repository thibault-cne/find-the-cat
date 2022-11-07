/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// f_perm.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/29 08/28/50
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../../includes/f_perm.h"

int get_file_perm(const char *path)
{
    struct stat st;
    int perm;

    if (stat((char *)path, &st) < 0)
    {
        return -1;
    }

    perm = 0;

    if (st.st_mode & S_IRUSR)
    {
        perm += P_READ * PERM_USR;
    }
    if (st.st_mode & S_IWUSR)
    {
        perm += P_WRITE * PERM_USR;
    }
    if (st.st_mode & S_IXUSR)
    {
        perm += P_EXEC * PERM_USR;
    }

    if (st.st_mode & S_IRGRP)
    {
        perm += P_READ * PERM_GRP;
    }
    if (st.st_mode & S_IWGRP)
    {
        perm += P_WRITE * PERM_GRP;
    }
    if (st.st_mode & S_IXGRP)
    {
        perm += P_EXEC * PERM_GRP;
    }

    if (st.st_mode & S_IROTH)
    {
        perm += P_READ * PERM_OTH;
    }
    if (st.st_mode & S_IWOTH)
    {
        perm += P_WRITE * PERM_OTH;
    }
    if (st.st_mode & S_IXOTH)
    {
        perm += P_EXEC * PERM_OTH;
    }

    return perm;
}

int verify_file_perm(const char *path, int perm)
{
    int f_perm;

    f_perm = get_file_perm(path);

    if (f_perm == perm)
    {
        return 1;
    }

    return 0;
}
