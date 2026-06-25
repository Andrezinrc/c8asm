#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

int next_token(FILE *f, char *token_buffer, int max_size);

#endif
