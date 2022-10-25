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

void path_display(PathList *pl, int isColor)
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

void path_display_color(PathList *pl)
{
    int i;

    i = -1;

    while (++i < pl->ptr)
    {
        if (pl->data[i] != NULL)
        {
            printf("%s\n", color_text(pl->data[i], COLOR_GREEN));
        }
    }
}

char *color_text(char *text, char *color)
{
    char *res;

    res = malloc(sizeof(char) * (strlen(text) + strlen(color) + strlen(COLOR_RESET) + 1));
    sprintf(res, "%s%s%s", color, text, COLOR_RESET);

    return res;
}
