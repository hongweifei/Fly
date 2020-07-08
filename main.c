
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/lexer.h"

int main(int argc,char *argv[])
{
	if (argc > 1)
	{
		//printf("%s\n",argv[1]);
		FILE *fp = fopen(argv[1],"r");
		if (fp != NULL)
		{
			Token *token = NULL;
			while ((token = GetNextToken(fp)) != NULL)
			{
				//printf("%s  %d\n", token->str, token->type);
				printf("Type: %d\n",token->type);
				printf("Value: %s\n\n",token->str);
				free(token);
			}
		}
	}
	else if (argc == 1)
		printf("Please specify an input file.\n");
	return 0;
}

