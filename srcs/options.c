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

#include "../includes/options.h"

Options get_flag_options(const char *opt)
{
    if (!strcmp(opt, "-test"))
    {
        return TEST;
    }
    if (!strcmp(opt, "-size"))
    {
        return SIZE;
    }
    if (!strcmp(opt, "-name"))
    {
        return NAME;
    }
    if (!strcmp(opt, "-date"))
    {
        return DATE;
    }
    if (!strcmp(opt, "-mime"))
    {
        return MIME;
    }
    if (!strcmp(opt, "-ctc"))
    {
        return CTC;
    }
    if (!strcmp(opt, "-dir"))
    {
        return DIRECTORY;
    }
    if (!strcmp(opt, "-color"))
    {
        return COLOR;
    }
    if (!strcmp(opt, "-perm"))
    {
        return PERM;
    }
    if (!strcmp(opt, "-link"))
    {
        return LINK;
    }
    if (!strcmp(opt, "-threads"))
    {
        return THREADS;
    }
    if (!strcmp(opt, "-ou"))
    {
        return OR;
    }

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

int get_size(char *size)
{
    int i;
    int offset;
    char *new_size;

    if (size[0] == '-' || size[0] == '+')
    {
        i = 0;
        offset = 1;
    }
    else
    {
        i = -1;
        offset = 0;
    }

    new_size = malloc(sizeof(char) * OPTS_MAX_SIZE);

    while (size[++i] != '\0')
    {
        new_size[i - offset] = size[i];
    }
    new_size[i] = '\0';

    return atoi(new_size);
}
