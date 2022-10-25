#ifndef FTC_DISPLAY_H
#define FTC_DISPLAY_H

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

#include <stdio.h>

#include "path.h"

void path_display(PathList *l, int isColor);
void path_display_color(PathList *l);

char *color_text(char *text, char *color);

#endif // FTC_DISPLAY_H
