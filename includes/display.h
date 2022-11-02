#ifndef FTC_DISPLAY_H
#define FTC_DISPLAY_H

#define RESET "\033[0m"

// Colors
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// Text styles
#define STYLE_BOLD "\033[1m"
#define STYLE_DIM "\033[2m"
#define STYLE_UNDERLINED "\033[4m"
#define STYLE_BLINK "\033[5m"
#define STYLE_REVERSE "\033[7m"
#define STYLE_HIDDEN "\033[8m"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "path.h"
#include "utils.h"

// Display the map of path
// @param pl the path list
// @param isColor if the color is enable
void path_display(path_list *l, int isColor);

// Display a path in color or not
// @param path the path to display
// @param isColor if the color is enable
void f_printp(const char *path, int isColor);

// Display the help menu
// @param isColor if the color is enable
void display_help(int isColored);

// Implementation of sprintf function
// @param format the format of the string
// @param args the arguments
// @return the formatted string
char *f_sprintf(const char *format, va_list args);

// Implementation of printf function with color and style
// @param format the format of the string
// @param ... the arguments
void f_printf(const char *format, ...);

// Display a string or a color or a style
// @param beg the beginning of the string
// @param end the end of the string
void f_cprintf(char **beg, char **end);

#endif // FTC_DISPLAY_H
