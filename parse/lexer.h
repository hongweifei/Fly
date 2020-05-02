
#pragma once

#include <stdio.h>
#include "token.h"

#define BOOL	short
#define TRUE	1
#define FALSE	0


BOOL IsIdentifier(const char *str);//是否是标识符
BOOL IsLetter(int ch);//是否是字母
BOOL IsDigit(int ch);//是否是0-9任意数字
BOOL IsSymbol(int ch);//是否是符号

TokenCode IsKeyWord(const char *str);

BOOL NextIsAppointChar(FILE *fp,int ch,BOOL if_is_fp_back);
BOOL NextIsAppointString(FILE* fp, const char *str, BOOL if_is_fp_back);

BOOL NextIsChineseCharacter(FILE *fp);//下一个字是否是汉字

Token *GetNextToken(FILE *fp);
