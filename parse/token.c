

#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TokenSetTypeAndText(Token* token, TokenCode type, const char* text)
{
	TokenSetType(token, type);
	TokenSetText(token, text);
}

void TokenSetTypeAndChar(Token* token, TokenCode type, int ch)
{
	TokenSetType(token, type);
	TokenSetChar(token, ch);
}

void TokenSetType(Token* token, TokenCode type)
{
	token->type = type;
}

void TokenSetText(Token *token,const char *text)
{
	unsigned int length = strlen(text);
	token->str = (char*)malloc(sizeof(char) * length);

	strcpy(token->str,text);
}

void TokenSetChar(Token* token, int ch)
{
	token->str = (char*)calloc(1,sizeof(char));
	sprintf(token->str,"%c",ch);
}

void TokenAddChar(Token* token, int ch)
{
	unsigned int length = strlen(token->str);
	token->str = (char*)realloc(token->str,sizeof(char) * (length + 1));

	char str[2] = {'\0'};
	sprintf(str, "%c", ch);
	strcat(token->str,str);
}
