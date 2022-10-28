#ifndef FTC_TOKEN_H
#define FTC_TOKEN_H

#include <stdlib.h>
#include <string.h>

#include "options.h"

struct _token
{
    int pos;
    Options TokenType;
    char *value;
};
typedef struct _token token;

void create_token(token *t, int pos, Options tokenType, char *value);
void destroy_token(token *t);

struct _TokenList
{
    token *data;
    int ptr;
    int size;
};
typedef struct _TokenList token_list;

void create_token_list(token_list *l, int size);
void add_token_list(token_list *l, token t);
token *get_token_list_index(token_list *l, int i);
token *get_token_list_opt(token_list *l, Options opt);
void destroy_token_list(token_list *l);

#endif // FTC_TOKEN_H
