/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// options.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/24 15/54/44
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include <stdio.h>

#include "../includes/options.h"

Options get_flag_options(const char *opt)
{
    if (!strcmp(opt, "-test"))
        return TEST;
    if (!strcmp(opt, "-size"))
        return SIZE;
    if (!strcmp(opt, "-name"))
        return NAME;
    if (!strcmp(opt, "-date"))
        return DATE;
    if (!strcmp(opt, "-mime"))
        return MIME;
    if (!strcmp(opt, "-ctc"))
        return CTC;
    if (!strcmp(opt, "-dir"))
        return DIRECTORY;
    if (!strcmp(opt, "-color"))
        return COLOR;
    if (!strcmp(opt, "-perm"))
        return PERM;
    if (!strcmp(opt, "-link"))
        return LINK;
    if (!strcmp(opt, "-threads"))
        return THREADS;
    if (!strcmp(opt, "-ou"))
        return OR;

    return (Options)-1;
}

char *get_options_flag(Options opt)
{
    switch (opt)
    {
    case TEST:
        return "-test";
    case SIZE:
        return "-size";
    case NAME:
        return "-name";
    case DATE:
        return "-date";
    case MIME:
        return "-mime";
    case CTC:
        return "-ctc";
    case DIRECTORY:
        return "-dir";
    case COLOR:
        return "-color";
    case PERM:
        return "-perm";
    case LINK:
        return "-link";
    case THREADS:
        return "-threads";
    case OR:
        return "-ou";
    default:
        return "";
    }
}

