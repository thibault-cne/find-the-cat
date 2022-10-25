#ifndef FTC_TOKEN_H
#define FTC_TOKEN_H

#include <stdlib.h>
#include <string.h>

#include "options.h"

struct _Token
{
    int pos;
    Options TokenType;
    char *value;
};
typedef struct _Token Token;

void create_token(Token *t, int pos, Options tokenType, char *value);
void destroy_token(Token *t);

struct _TokenList
{
    Token *data;
    int ptr;
    int size;
};
typedef struct _TokenList TokenList;

void create_token_list(TokenList *l, int size);
void add_token_list(TokenList *l, Token t);
Token *get_token_list_index(TokenList *l, int i);
Token *get_token_list_opt(TokenList *l, Options opt);
void destroy_token_list(TokenList *l);

#endif // FTC_TOKEN_H
