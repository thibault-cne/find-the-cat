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
