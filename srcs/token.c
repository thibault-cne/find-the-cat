/* ************************************************************************************************************ */
/*                                                                                                              */
/*                                                                                                              */
// token.c
/*                                                                                                              */
// by Thibault Cheneviere : thibault.cheneviere@telecomnancy.eu
/*                                                                                                              */
// Created : 2022/10/24 15/36/28
/*                                                                                                              */
/*                                                                                                              */
/* ************************************************************************************************************ */

#include "../includes/token.h"

void create_token(token *t, int pos, Options tokenType, char *value)
{
    t->pos = pos;
    t->TokenType = tokenType;
    t->value = malloc(sizeof(char) * OPTS_MAX_SIZE);
    strncpy(t->value, value, OPTS_MAX_SIZE);
}

void destroy_token(token *t)
{
    free(t->value);
}

void create_token_list(token_list *l, int size)
{
    l->data = (token *)malloc(sizeof(token) * size);
    l->ptr = 0;
    l->size = size;
}

void add_token_list(token_list *l, token tok)
{
    if (l->ptr >= l->size)
    {
        l->size *= 2;
        l->data = (token *)realloc(l->data, sizeof(token) * l->size);
    }

    token *t;

    t = &l->data[l->ptr++];
    create_token(t, tok.pos, tok.TokenType, tok.value);
}

token *get_token_list_index(token_list *l, int i)
{
    if (i >= l->ptr)
    {
        return NULL;
    }

    return &l->data[i];
}

token *get_token_list_opt(token_list *l, Options opt)
{
    int i;

    i = -1;

    while (++i < l->ptr)
    {
        if (l->data[i].TokenType == opt)
        {
            return &l->data[i];
        }
    }

    return NULL;
}

void destroy_token_list(token_list *l)
{
    int i;

    i = -1;

    while (++i < l->ptr)
    {
        destroy_token(&l->data[i]);
    }

    free(l->data);
}
