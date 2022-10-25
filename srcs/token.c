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

void create_token(Token *t, int pos, Options tokenType, char *value)
{
    t->pos = pos;
    t->TokenType = tokenType;
    t->value = malloc(sizeof(char) * OPTS_MAX_SIZE);
    strncpy(t->value, value, OPTS_MAX_SIZE);
}

void destroy_token(Token *t)
{
    free(t->value);
}

void create_token_list(TokenList *l, int size)
{
    l->data = (Token *)malloc(sizeof(Token) * size);
    l->ptr = 0;
    l->size = size;
}

void add_token_list(TokenList *l, Token tok)
{
    if (l->ptr >= l->size)
    {
        l->size *= 2;
        l->data = (Token *)realloc(l->data, sizeof(Token) * l->size);
    }

    Token *t;

    t = &l->data[l->ptr++];
    create_token(t, tok.pos, tok.TokenType, tok.value);
}

Token *get_token_list_index(TokenList *l, int i)
{
    if (i >= l->size)
    {
        return NULL;
    }

    return &l->data[i];
}

Token *get_token_list_opt(TokenList *l, Options opt)
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

void destroy_token_list(TokenList *l)
{
    int i;

    i = -1;

    while (++i < l->ptr)
    {
        destroy_token(&l->data[i]);
    }

    free(l->data);
}
