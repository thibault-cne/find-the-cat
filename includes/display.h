#ifndef FTC_DISPLAY_H
#define FTC_DISPLAY_H

// Colors
#define COLOR_RESET "\033[0m"
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

#include "path.h"

// Display the map of path
// @param pl the path list
// @param isColor if the color is enable
void path_display(path_list *l, int isColor);

// Display the map of path with color
// @param pl path list
void path_display_color(path_list *l);

// Format a given string with a given format
// @param text the string to format
// @param format the format to apply
// @return The formatted string
char *format_text(char *text, char *format);

// Display the help menu
// @param isColor if the color is enable
void display_help(int isColored);

#endif // FTC_DISPLAY_H
