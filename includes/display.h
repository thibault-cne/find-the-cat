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
#include <string.h>

#include "utils.h"

#ifdef __styles
// Styles used by the display functions
const char *styles[] = {
    "COLOR_RED", "COLOR_GREEN", "COLOR_YELLOW", "COLOR_BLUE", "COLOR_MAGENTA",
    "COLOR_CYAN", "COLOR_WHITE", "S", "STYLE_BOLD", "STYLE_DIM",
    "STYLE_UNDERLINED", "STYLE_BLINK", "STYLE_REVERSE", "STYLE_HIDDEN",
    NULL};

// Styles used in the terminal
const char *converted_styles[] = {
    COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_MAGENTA,
    COLOR_CYAN, COLOR_WHITE, RESET, STYLE_BOLD, STYLE_DIM,
    STYLE_UNDERLINED, STYLE_BLINK, STYLE_REVERSE, STYLE_HIDDEN,
    NULL};
#endif // __styles

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
void f_printf(FILE *f, const char *format, ...);

// Display a string or a color or a style
// @param beg the beginning of the string
// @param end the end of the string
void f_cprintf(FILE *f, char **beg, char **end);

#endif // FTC_DISPLAY_H
