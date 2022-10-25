#ifndef FTC_OPTIONS_H
#define FTC_OPTIONS_H

#define OPTS_MAX_SIZE 0xFF // Max size of an options

// Size constant
#define SIZE_C 0x1
#define SIZE_KIB 0X400
#define SIZE_MIB 0X100000
#define SIZE_GIB 0X40000000

#include <string.h>
#include <stdlib.h>

enum _Options
{
    NAME,
    SIZE,
    DATE,
    MIME,
    CTC,
    DIRECTORY,
    COLOR,
    PERM,
    LINK,
    THREADS,
    OR,
    TEST,
};
typedef enum _Options Options;

Options get_flag_options(const char *opt);
char *get_options_flag(Options opt);
int get_size(char *size);

#endif // FTC_OPTIONS_H
