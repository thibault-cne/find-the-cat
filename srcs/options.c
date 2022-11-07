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

// Size functions
off_t get_size(char *size)
{
    int i;
    int offset;
    char *new_size;
    off_t res;

    res = 0;

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

    while (size[++i] != '\0' && (int)size[i] < 58 && (int)size[i] > 47)
    {
        new_size[i - offset] = size[i];
    }
    new_size[i] = '\0';

    res = atoi(new_size) * get_multiplier(size[i]);

    // Free memory
    free(new_size);

    return res;
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

// Time functions
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
