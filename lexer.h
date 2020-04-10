
#include <stdio.h>
#include <vector>

#include "token.h"

#ifndef LEXER
#define LEXER


int IsLetter(int ch);
int IsDigit(int ch);

std::vector<Token> Scaner(const char *path);

Token Scaner(FILE *fp);

#ifdef __cplusplus
extern "C"{
#endif

    Token *Scaner(std::string path);

#ifdef __cplusplus
}
#endif

Token Scaner(char *str);

#endif

