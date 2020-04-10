
#include <stdio.h>
#include <iostream>
#include "token.h"
#include "lexer.h"

int main(int argc,char *argv[])
{
    //std::vector<Token> token(1);
    Token token;
    int token_n = 1;

    if(argc > 1)
    {
        //token = Scaner((const char*)argv[1]);
        FILE *fp = fopen(argv[1],"r");
        token = Scaner(fp);
        while (token.code != TK_EOF)
        {
            token = Scaner(fp);
            token_n++;
            std::cout << token.word << std::endl;
        }
        
    }

    /*
    int i;
    for (i = 0; i < token.size(); i++)
    {
        std::cout << token[i].word << std::endl;
    }
    */

    return 0;
}
