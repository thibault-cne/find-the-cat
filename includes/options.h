#ifndef FTC_OPTIONS_H
#define FTC_OPTIONS_H

#define OPTS_MAX_SIZE 0xFF // Max size of an options

// Size constant
#define SIZE_C 0x1
#define SIZE_KIB 0x400
#define SIZE_MIB 0x100000
#define SIZE_GIB 0x40000000

// Time constant
#define TIME_S 0x1
#define TIME_MIN 0x3C
#define TIME_H 0xE10
#define TIME_D 0x15180

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

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
    NONE,
};
typedef enum _Options Options;

// Get the option from one command line argument
// @param arg the command line argument
// @return the option
Options get_flag_options(const char *opt);

// Get the argument from an option
// @param opt the option
// @return the argument
char *get_options_flag(Options opt);



#endif // FTC_OPTIONS_H
