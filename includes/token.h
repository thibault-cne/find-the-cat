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

// Create a new token
// @param t the token pointer
// @param pos the position of the token
// @param token_type the type of the token
// @param value the value of the token
void create_token(token *t, int pos, Options token_type, char *value);

// Free the token
// @param t the token pointer
void destroy_token(token *t);

struct _token_list
{
    token *data;
    int ptr;
    int size;
};
typedef struct _token_list token_list;

// Create a new token list
// @param l the token list pointer
// @param size the size of the token list
void create_token_list(token_list *l, int size);

// Add a token to the token list
// @param l the token list pointer
// @param t the token to add
void add_token_list(token_list *l, token t);

// Get the token at the given index
// @param l the token list pointer
// @param index the index of the token
// @return the token at the given index
token *get_token_list_index(token_list *l, int i);

// Get the token of the given type
// @param l the token list pointer
// @param opt the type of the token
// @return the token of the given type
token *get_token_list_opt(token_list *l, Options opt);

// Free the token list
// @param l the token list pointer
void destroy_token_list(token_list *l);

#endif // FTC_TOKEN_H
