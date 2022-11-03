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

#define __styles

#include "../includes/display.h"

void path_display(path_list_t *pl, int isColor)
{
    int i;

    i = -1;

    while (++i < pl->ptr)
    {
        if (pl->data[i] == NULL)
        {
            continue;
        }

        f_printp(pl->data[i], isColor);
    }
}

void f_printp(const char *path, int isColor)
{
    if (!isColor)
    {
        printf("%s\n", path);
        return;
    }

    const char *delimiters = "/";

    char *beg;
    char *end;

    beg = (char *)path;
    end = (char *)path;

    while (*end != '\0')
    {
        beg += strspn(beg, delimiters);
        end = beg + strcspn(beg, delimiters);

        if (*end == '\0')
        {
            f_printf("COLOR_BLUE|%.*s%c|S", (int)(end - beg), beg, *end);
            break;
        }
        f_printf("S|%.*s%c", (int)(end - beg), beg, *end);

        beg = end + 1;
    }

    putchar('\n');
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

char *f_sprintf(const char *format, va_list args)
{
    va_list args2;
    size_t len;

    va_copy(args2, args);

    len = vsnprintf(NULL, 0, format, args);
    char *str = (char *)malloc((len + 1) * sizeof(char));

    vsnprintf(str, len + 1, format, args2);

    va_end(args);

    str[len] = '\0';
    return str;
}

// Format is a string like COLOR|STYLE|text|COLOR|STYLE|text|...
// Example: "COLOR_GREEN|STYLE_BOLD|Hello World|" will return "Hello World" in green and bold
void f_printf(const char *format, ...)
{
    va_list args;
    char *str;
    char *beg;
    char *end;
    char *whitespace;
    char *delimiters;

    va_start(args, format);
    str = f_sprintf(format, args);
    va_end(args);

    beg = str;
    end = str;

    whitespace = " \t";
    delimiters = "|";

    while (*end != '\0')
    {
        beg += strspn(beg, whitespace);
        end = beg + strcspn(beg, delimiters);
        f_cprintf(&beg, &end);

        beg = end + 1;
    }

    free(str);
}

void f_cprintf(char **beg, char **end)
{
    char *format;
    int i;

    format = malloc(sizeof(char) * (*end - *beg + 1));
    strncpy(format, *beg, *end - *beg);
    format[(int)(*end - *beg)] = '\0';

    i = -1;

    while (styles[++i])
    {
        if (strcmp(format, styles[i]) == 0)
        {
            printf("%s", converted_styles[i]);
            free(format);
            return;
        }
    }

    printf("%s", format);
    free(format);
}
