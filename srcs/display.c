/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// display.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/25 19/35/10
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/display.h"

void path_display(path_list *pl, int isColor)
{
    if (isColor)
    {
        path_display_color(pl);
    }
    else
    {
        int i;

        i = -1;

        while (++i < pl->ptr)
        {
            if (pl->data[i] != NULL)
            {
                printf("%s\n", pl->data[i]);
            }
        }
    }
}

void path_display_color(path_list *pl)
{
    int i;

    i = -1;

    while (++i < pl->ptr)
    {
        if (pl->data[i] != NULL)
        {
            f_printf("COLOR_GREEN|%s\n|S", pl->data[i]);
        }
    }
}

void display_help(int isColored)
{
    if (isColored)
    {
        f_printf("COLOR_GREEN|STYLE_BOLD|%s|S: ./FindTheCat [PATH] [-OPTION [PARAMETER]]\n", "Usage");
    }
    else
    {
        printf("%s: ./FindTheCat [PATH] [-OPTION [PARAMETER]]\n", "Usage");
    }
}

// Format is a string like COLOR|STYLE|text|COLOR|STYLE|text|...
// Example: "COLOR_GREEN|STYLE_BOLD|Hello World|" will return "Hello World" in green and bold
void f_printf(const char *format, ...)
{
    size_t len;
    char *str;
    va_list args;
    va_list args2;
    char *beg;
    char *end;
    char *whitespace;
    char *delimiters;

    va_start(args, format);

    // Copy the args to args2
    va_copy(args2, args);

    // Get the length of the string
    len = vsnprintf(NULL, 0, format, args);

    // Allocate the string
    str = malloc(len + 1);

    // Write the string
    vsprintf(str, format, args2);

    va_end(args);

    str[len] = '\0';

    beg = str;
    end = str;

    whitespace = " \t";
    delimiters = "|";

    while (1)
    {
        beg += strspn(beg, whitespace);
        end = beg + strcspn(beg, delimiters);

        f_fprintf(&beg, &end);

        beg = end + 1;

        if (*end == '\0')
        {
            break;
        }
    }

    free(str);
}

void f_fprintf(char **beg, char **end)
{
    char *format;

    format = malloc(sizeof(char) * (*end - *beg + 1));
    strncpy(format, *beg, *end - *beg);
    format[(int)(*end - *beg)] = '\0';

    if (!strcmp(format, "COLOR_GREEN"))
    {
        printf("%s", COLOR_GREEN);
        free(format);
        return;
    }
    if (!strcmp(format, "COLOR_RED"))
    {
        printf("%s", COLOR_RED);
        free(format);
        return;
    }
    if (!strcmp(format, "COLOR_YELLOW"))
    {
        printf("%s", COLOR_YELLOW);
        free(format);
        return;
    }
    if (!strcmp(format, "COLOR_BLUE"))
    {
        printf("%s", COLOR_BLUE);
        free(format);
        return;
    }
    if (!strcmp(format, "COLOR_MAGENTA"))
    {
        printf("%s", COLOR_MAGENTA);
        free(format);
        return;
    }
    if (!strcmp(format, "COLOR_CYAN"))
    {
        printf("%s", COLOR_CYAN);
        free(format);
        return;
    }
    if (!strcmp(format, "S"))
    {
        printf("%s", RESET);
        free(format);
        return;
    }
    if (!strcmp(format, "STYLE_BOLD"))
    {
        printf("%s", STYLE_BOLD);
        free(format);
        return;
    }
    if (!strcmp(format, "STYLE_UNDERLINE"))
    {
        printf("%s", STYLE_UNDERLINED);
        free(format);
        return;
    }
    if (!strcmp(format, "STYLE_BLINK"))
    {
        printf("%s", STYLE_BLINK);
        free(format);
        return;
    }
    if (!strcmp(format, "STYLE_REVERSE"))
    {
        printf("%s", STYLE_REVERSE);
        free(format);
        return;
    }
    if (!strcmp(format, "STYLE_HIDDEN"))
    {
        printf("%s", STYLE_HIDDEN);
        free(format);
        return;
    }

    printf("%s", format);
    free(format);
}
