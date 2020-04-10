
#include "lexer.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int IsLetter(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_'))
        return 1;
    return 0;    
}

int IsDigit(int ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0; 
}

bool Is()
{
    return true;
}

std::vector<Token> Scaner(const char *path)
{
    std::vector<Token> token(1);
    int token_n = 0;

    FILE *fp = fopen(path,"r");
    int ch = fgetc(fp);

scaner:
    //token = (Token*)realloc(token,sizeof(Token) * (token_n + 1));
    token.reserve(token_n + 1);

    if (IsLetter(ch))
    {
        token[token_n].word = ch;
        ch = fgetc(fp);
        while (IsLetter(ch) || IsDigit(ch))
        {
            token[token_n].word += ch;
            ch = fgetc(fp);
        }
        token[token_n].code = TK_IDENT;
        token_n++;
        std::cout << token[token_n - 1].word << std::endl;
        goto scaner;
    }
    else if(ch == '\'')
    {
        token[token_n].word = ch;
        ch = fgetc(fp);
        while (IsLetter(ch) || IsDigit(ch))
        {
            token[token_n].word += ch;
            ch = fgetc(fp);
        }
        token[token_n].word += ch;
        token[token_n].code = TK_CCHAR;
        token_n++;
        std::cout << token[token_n - 1].word << std::endl;
        ch = fgetc(fp);
        goto scaner;
    }
    else if(ch == '\"')
    {
        token[token_n].word = ch;
        ch = fgetc(fp);
        while (IsLetter(ch) || IsDigit(ch))
        {
            token[token_n].word += ch;
            ch = fgetc(fp);
        }
        token[token_n].word += ch;
        token[token_n].code = TK_CSTR;
        token_n++;
        std::cout << token[token_n - 1].word << std::endl;
        ch = fgetc(fp);
        goto scaner;
    }
    else if(IsDigit(ch))
    {
        token[token_n].word = ch;
        ch = fgetc(fp);
        while (IsDigit(ch))
        {
            token[token_n].word += ch;
            ch = fgetc(fp);
        }
        token[token_n].code = TK_CINT;
        token_n++;
        std::cout << token[token_n - 1].word << std::endl;
        goto scaner;
    }
    else
    {
        switch (ch)
        {
        case '+':
            token[token_n].word = "+";
            token[token_n].code = TK_PLUS;
            token_n++;
            break;
        case '-':
            token[token_n].word = "-";
            token[token_n].code = TK_MINUS;
            token_n++;
            break;
        case '*':
            token[token_n].word = "*";
            token[token_n].code = TK_STAR;
            token_n++;
            break;
        case '/':
            token[token_n].word = "/";
            token[token_n].code = TK_DIVIDE;
            token_n++;
            break;
        case '=':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token[token_n].word = "==";
                token[token_n].code = TK_EQ;
                token_n++;
            }
            else
            {
                token[token_n].word = "=";
                token[token_n].code = TK_ASSIGN;
                token_n++;
                goto scaner;
            }
            break;
        case '!':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token[token_n].word = "!=";
                token[token_n].code = TK_NEQ;
                token_n++;
            }
            else
                goto scaner;
            break;
        case '<':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token[token_n].word = "<=";
                token[token_n].code = TK_LEQ;
                token_n++;
            }
            else
            {
                token[token_n].word = "<";
                token[token_n].code = TK_LT;
                token_n++;
                goto scaner;
            }
            break;
        case '>':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token[token_n].word = ">=";
                token[token_n].code = TK_GEQ;
                token_n++;
            }
            else
            {
                token[token_n].word = ">";
                token[token_n].code = TK_GT;
                token_n++;
                goto scaner;
            }
            break;
        case '.':
            ch = fgetc(fp);
            if(ch == '.')
            {
                ch = fgetc(fp);
                if(ch == '.')
                {
                    token[token_n].word = "...";
                    token[token_n].code = TK_ELLIPSIS;
                    token_n++;
                }
                else
                {
                    token[token_n].word = "..";
                    goto scaner;
                }
            }
            else
            {
                token[token_n].word = ".";
                token[token_n].code = TK_DOT;
                token_n++;
                goto scaner;
            }
            break;
        case '&':
            token[token_n].word = "&";
            token[token_n].code = TK_AND;
            token_n++;
            break;
        case '(':
            token[token_n].word = "(";
            token[token_n].code = TK_OPENPA;
            token_n++;
            break;
        case ')':
            token[token_n].word = ")";
            token[token_n].code = TK_CLOSEPA;
            token_n++;
            break;
        case '[':
            token[token_n].word = "[";
            token[token_n].code = TK_OPENBR;
            token_n++;
            break;
        case ']':
            token[token_n].word = "]";
            token[token_n].code = TK_CLOSEBR;
            token_n++;
            break;
        case '{':
            token[token_n].word = "{";
            token[token_n].code = TK_BEGIN;
            token_n++;
            break;
        case '}':
            token[token_n].word = "}";
            token[token_n].code = TK_END;
            token_n++;
            break;
        case ';':
            token[token_n].word = ";";
            token[token_n].code = TK_SEMICOLON;
            token_n++;
            break;
        case ',':
            token[token_n].word = ",";
            token[token_n].code = TK_COMMA;
            token_n++;
            break;
        case ' ':
            ch = fgetc(fp);
            goto scaner;
            break;
        case EOF:
            token[token_n].code = TK_EOF;
            //token[token_n].word = '\0';
            goto end;
            break;
        }
        ch = fgetc(fp);

        std::cout << token[token_n - 1].word << std::endl;
        goto scaner;
    }

end:
    fclose(fp);
    return token;
}

Token Scaner(FILE *fp)
{
    Token token;

    int ch = fgetc(fp);

scaner:
    if (IsLetter(ch))
    {
        while (IsLetter(ch) || IsDigit(ch))
        {
            token.word += ch;
            ch = fgetc(fp);
        }
        fseek(fp,-1L,SEEK_CUR);
    }
    else if(ch == '\'')
    {
        while (IsLetter(ch) || IsDigit(ch))
        {
            token.word += ch;
            ch = fgetc(fp);
        }
        fseek(fp,-1L,SEEK_CUR);
    }
    else if(ch == '\"')
    {
        while (IsLetter(ch) || IsDigit(ch))
        {
            token.word += ch;
            ch = fgetc(fp);
        }
        fseek(fp,-1L,SEEK_CUR);
    }
    else if(IsDigit(ch))
    {
        while (IsDigit(ch))
        {
            token.word += ch;
            ch = fgetc(fp);
        }
        fseek(fp,-1L,SEEK_CUR);
    }
    else
    {
        switch (ch)
        {
        case '+':
            token.word = "+";
            token.code = TK_PLUS;
            break;
        case '-':
            token.word = "-";
            token.code = TK_MINUS;
            break;
        case '*':
            token.word = "*";
            token.code = TK_STAR;
            break;
        case '/':
            token.word = "/";
            token.code = TK_DIVIDE;
            break;
        case '=':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token.word = "==";
                token.code = TK_EQ;
            }
            else
            {
                token.word = "=";
                token.code = TK_ASSIGN;
                fseek(fp,-1L,SEEK_CUR);
            }
            break;
        case '!':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token.word = "!=";
                token.code = TK_NEQ;
            }
            else
                fseek(fp,-1L,SEEK_CUR);
            break;
        case '<':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token.word = "<=";
                token.code = TK_LEQ;
            }
            else
            {
                token.word = "<";
                token.code = TK_LT;
                fseek(fp,-1L,SEEK_CUR);
            }
            break;
        case '>':
            ch = fgetc(fp);
            if(ch == '=')
            {
                token.word = ">=";
                token.code = TK_GEQ;
            }
            else
            {
                token.word = ">";
                token.code = TK_GT;
                fseek(fp,-1L,SEEK_CUR);
            }
            break;
        case '.':
            ch = fgetc(fp);
            if(ch == '.')
            {
                ch = fgetc(fp);
                if(ch == '.')
                {
                    token.word = "...";
                    token.code = TK_ELLIPSIS;
                }
                else
                {
                    token.word = "..";
                    fseek(fp,-2L,SEEK_CUR);
                }
            }
            else
            {
                token.word = ".";
                token.code = TK_DOT;
                fseek(fp,-1L,SEEK_CUR);
            }
            break;
        case '&':
            token.word = "&";
            token.code = TK_AND;
            break;
        case '(':
            token.word = "(";
            token.code = TK_OPENPA;
            break;
        case ')':
            token.word = ")";
            token.code = TK_CLOSEPA;
            break;
        case '[':
            token.word = "[";
            token.code = TK_OPENBR;
            break;
        case ']':
            token.word = "]";
            token.code = TK_CLOSEBR;
            break;
        case '{':
            token.word = "{";
            token.code = TK_BEGIN;
            break;
        case '}':
            token.word = "}";
            token.code = TK_END;
            break;
        case ';':
            token.word = ";";
            token.code = TK_SEMICOLON;
            break;
        case ',':
            token.word = ",";
            token.code = TK_COMMA;
            break;
        case ' ':
            ch = fgetc(fp);
            goto scaner;
            break;
        case EOF:
            token.code = TK_EOF;
            //token.word = '\0';
            break;
        }
    }
    
    return token;
}

#ifdef __cplusplus
extern "C"{
#endif

Token *Scaner(std::string path)
{
    FILE *fp = fopen(path.c_str(),"r");

    Token *token = (Token*)calloc(1,sizeof(Token));
    int token_n = 0;

    token[token_n] = Scaner(fp);
    printf("%s\n",token[token_n].word);

    while (token[token_n].code != TK_EOF)
    {
        token_n++;
        token = (Token*)realloc(token,sizeof(Token) * (token_n + 1));
        token[token_n] = Scaner(fp);
        printf("%s\n",token[token_n].word);
    }

    fclose(fp);
    return token;
}

#ifdef __cplusplus
}
#endif



Token Scaner(char *str)
{
    Token token;

    int n = strlen((const char*)str);

    for (int i = 0; i < n; i++)
    {
        int ch = str[i];

        if (IsLetter(ch))
        {
            int j = 0;
            while (IsLetter(str[i + j]) || IsDigit(str[i + j]))
            {
                token.word += str[i + j];
                j++;
            }
            i += j;
        }
        else if(ch == '\'')
        {
            int j = 0;
            while (IsLetter(str[i + j]) || IsDigit(str[i + j]))
            {
                token.word += str[i + j];
                j++;
            }
            i += j;
        }
        else if(ch == '\"')
        {
            int j = 0;
            while (IsLetter(str[i + j]) || IsDigit(str[i + j]))
            {
                token.word += str[i + j];
                j++;
            }
            i += j;
        }
        else if(IsDigit(ch))
        {
            int j = 0;
            while (IsDigit(str[i + j]))
            {
                token.word += str[i + j];
                j++;
            }
            i += j;
        }
        else
        {
            switch (ch)
            {
            case '+':
                token.word = "+";
                token.code = TK_PLUS;
                break;
            case '-':
                token.word = "-";
                token.code = TK_MINUS;
                break;
            case '*':
                token.word = "*";
                token.code = TK_STAR;
                break;
            case '/':
                token.word = "/";
                token.code = TK_DIVIDE;
                break;
            case '=':
                if(str[i + 1] == '=')
                {
                    token.word = "==";
                    token.code = TK_EQ;
                    i++;
                }
                else
                {
                    token.word = "=";
                    token.code = TK_ASSIGN;
                }
                break;
            case '!':
                if(str[i + 1] == '=')
                {
                    token.word = "!=";
                    token.code = TK_NEQ;
                    i++;
                }
                break;
            case '<':
                if(str[i + 1] == '=')
                {
                    token.word = "<=";
                    token.code = TK_LEQ;
                    i++;
                }
                else
                {
                    token.word = "<";
                    token.code = TK_LT;
                }
                break;
            case '>':
                if(str[i + 1] == '=')
                {
                    token.word = ">=";
                    token.code = TK_GEQ;
                    i++;
                }
                else
                {
                    token.word = ">";
                    token.code = TK_GT;
                }
                break;
            case '.':
                if(str[i + 1] == '.')
                {
                    if(str[i + 2] == '.')
                    {
                        token.word = "...";
                        token.code = TK_ELLIPSIS;
                        i += 2;
                    }
                    else
                    {
                        token.word = "..";
                        i++;
                    }
                }
                else
                {
                    token.word = ".";
                    token.code = TK_DOT;
                }
                break;
            case '&':
                token.word = "&";
                token.code = TK_AND;
                break;
            case '(':
                token.word = "(";
                token.code = TK_OPENPA;
                break;
            case ')':
                token.word = ")";
                token.code = TK_CLOSEPA;
                break;
            case '[':
                token.word = "[";
                token.code = TK_OPENBR;
                break;
            case ']':
                token.word = "]";
                token.code = TK_CLOSEBR;
                break;
            case '{':
                token.word = "{";
                token.code = TK_BEGIN;
                break;
            case '}':
                token.word = "}";
                token.code = TK_END;
                break;
            case ';':
                token.word = ";";
                token.code = TK_SEMICOLON;
                break;
            case ',':
                token.word = ",";
                token.code = TK_COMMA;
                break;
            case ' ':
                break;
            case EOF:
                token.code = TK_EOF;
                //token.word = '\0';
                break;
            case '\0':
                return token;
                break;
            }
        }
        break;
    }
    
    return token;
}



