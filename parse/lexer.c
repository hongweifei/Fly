

#include "lexer.h"
#include <stdlib.h>
#include <string.h>

BOOL IsIdentifier(const char *str)
{
    if (!IsDigit(str[0]))
    {
        unsigned int i;
        for (i = 1; i < strlen(str); i++)
        {
            if (!IsLetter(str[i]) && !IsDigit(str[i]) && str[i] != '_')
                return FALSE;
        }
        return TRUE;
    }
    else
        return FALSE;
}

BOOL IsLetter(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return TRUE;
    return FALSE;
}

BOOL IsDigit(int ch)
{
    if (ch >= '0' && ch <= '9')
        return TRUE;
    return FALSE;
}

BOOL IsSymbol(int ch)
{
    switch (ch)
    {
    case '+':
        return TRUE;
        break;
    case '-':
        return TRUE;
        break;
    case '*':
        return TRUE;
        break;
    case '/':
        return TRUE;
        break;
    case '=':
        return TRUE;
        break;
    case '!':
        return TRUE;
        break;
    case '<':
        return TRUE;
        break;
    case '>':
        return TRUE;
        break;
    case '.':
        return TRUE;
        break;
    case '&':
        return TRUE;
        break;
    case '(':
        return TRUE;
        break;
    case ')':
        return TRUE;
        break;
    case '[':
        return TRUE;
        break;
    case ']':
        return TRUE;
        break;
    case '{':
        return TRUE;
        break;
    case '}':
        return TRUE;
        break;
    case ';':
        return TRUE;
        break;
    case ',':
        return TRUE;
        break;
    }
    return FALSE;
}


BOOL NextIsAppointChar(FILE* fp, int ch, BOOL if_is_fp_back)
{
    if (ch == fgetc(fp))
    {
        if(if_is_fp_back)
            fseek(fp, -1L, SEEK_CUR);
        return TRUE;
    }
    fseek(fp, -1L, SEEK_CUR);
    return FALSE;
}

BOOL NextIsAppointString(FILE* fp, const char* str, BOOL if_is_fp_back)
{
    int i;
    int length = strlen(str);
    for (i = 0; i < length; i++)
    {
        if (!NextIsAppointChar(fp, str[i], if_is_fp_back))
        {
            fseek(fp, -(i + 1), SEEK_CUR);
            return FALSE;
        }
    }
    if (if_is_fp_back)
        fseek(fp,-length,SEEK_CUR);
    return TRUE;
}


BOOL NextIsChineseCharacter(FILE *fp)
{
    if (fgetc(fp) < 0)
    {
        fseek(fp, -1L, SEEK_CUR);
        return TRUE;
    }
    fseek(fp, -1L, SEEK_CUR);
    return FALSE;
}

Token *GetNextToken(FILE *fp)
{
    Token *token = (Token*)calloc(1,sizeof(Token));

    int ch = fgetc(fp);

start:

    if (IsLetter(ch))
    {
        TokenSetChar(token, ch);
        ch = fgetc(fp);

        while (IsLetter(ch) || IsDigit(ch) || ch == '_')
        {
            TokenAddChar(token, ch);
            ch = fgetc(fp);
        }
        fseek(fp, -1L, SEEK_CUR);

        token->type = TK_IDENT;
        //printf("%s\n",token->str);
    }
    else if (IsDigit(ch))
    {
        TokenSetChar(token, ch);
        ch = fgetc(fp);

        while (IsDigit(ch))
        {
            TokenAddChar(token, ch);
            ch = fgetc(fp);
        }
        fseek(fp, -1L, SEEK_CUR);

        token->type = TK_CINT;;
        //printf("%s\n", token->str);
    }
    else
    {
        switch (ch)
        {
        case '+':
            TokenSetTypeAndText(token, TK_PLUS, "+");
            break;
        case '-':
            if(NextIsAppointChar(fp,ch,FALSE))
                TokenSetTypeAndText(token, TK_POINTSTO, "->");
            else
                TokenSetTypeAndText(token, TK_MINUS, "-");
            break;
        case '*':
            TokenSetTypeAndText(token, TK_STAR, "*");
            break;
        case '/':
            TokenSetTypeAndText(token, TK_DIVIDE, "/");
            break;
        case '=':
            if (NextIsAppointChar(fp,'=',FALSE))
                TokenSetTypeAndText(token, TK_EQ, "==");
            else
                TokenSetTypeAndText(token, TK_ASSIGN, "=");
            break;
        case '!':
            if (NextIsAppointChar(fp, '=', FALSE))
                TokenSetTypeAndText(token, TK_NEQ, "!=");
            break;
        case '<':
            if(NextIsAppointChar(fp,'=',FALSE))
                TokenSetTypeAndText(token, TK_LEQ, "<=");
            else
                TokenSetTypeAndText(token, TK_LT, "<");
            break;
        case '>':
            if (NextIsAppointChar(fp, '=', FALSE))
                TokenSetTypeAndText(token, TK_GEQ, ">=");
            else
                TokenSetTypeAndText(token, TK_GT, ">");
            break;
        case '.':
            if (NextIsAppointString(fp,"..",FALSE))
                TokenSetTypeAndText(token, TK_ELLIPSIS, "...");
            else
                TokenSetTypeAndText(token, TK_DOT, ".");
            break;
        case '&':
            TokenSetTypeAndText(token, TK_AND, "&");
            break;
        case '(':
            TokenSetTypeAndText(token, TK_OPENPA, "(");
            break;
        case ')':
            TokenSetTypeAndText(token, TK_CLOSEPA, ")");
            break;
        case '[':
            TokenSetTypeAndText(token, TK_OPENBR, "[");
            break;
        case ']':
            TokenSetTypeAndText(token, TK_CLOSEBR, "]");
            break;
        case '{':
            TokenSetTypeAndText(token, TK_BEGIN, "{");
            break;
        case '}':
            TokenSetTypeAndText(token, TK_END, "}");
            break;
        case ';':
            TokenSetTypeAndText(token, TK_SEMICOLON, ";");
            break;
        case ',':
            TokenSetTypeAndText(token, TK_COMMA, ",");
            break;
        case ' ':
            ch = fgetc(fp);
            goto start;
            break;
        case '\n':
            ch = fgetc(fp);
            goto start;
        case EOF:
            return NULL;
            break;
        }
    }

    return token;
}

