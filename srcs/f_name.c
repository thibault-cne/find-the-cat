/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// filename.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/28 12/11/59
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/f_name.h"

// Verify if files in the path list correspond to the given name
int verify_files_by_name(const char *f_name, char *name)
{
    return regex_match(f_name, name);
}
