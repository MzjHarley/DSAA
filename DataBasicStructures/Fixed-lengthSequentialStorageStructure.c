/**
 * 串的定长存储结构的表示和实现
 */
#include<stdio.h>
#include<stdbool.h>

#define MAX_STR_LEN 40
typedef unsigned char SString [MAX_STR_LEN];//定义一个char数组类型SString.

#define destroyString ClearString
#define InitString ClearString

bool StrAssgin(SString T, char* chars);
void StrCopy(SString T, SString S);
bool StrIsEmpty(SString S);
int StrCompare(SString T, SString S);
void ClearString(SString T);
bool StrConcat(SString T, SString S1, SString S2);
bool Str(SString Sub, SString S, int pos, int len);
bool Index1(SString S, SString T, int pos);
bool StrInsert(SString S, int pos, SString T);
bool StrDelete(SString S, int pos, int len);
void StrPrint(SString S);

int main()
{
    return 0;
}

bool StrAssgin(SString T, char* chars);
void StrCopy(SString T, SString S);
bool StrIsEmpty(SString S);
int StrCompare(SString T, SString S);
void ClearString(SString T);
bool StrConcat(SString T, SString S1, SString S2);
bool Str(SString Sub, SString S, int pos, int len);
bool Index1(SString S, SString T, int pos);
bool StrInsert(SString S, int pos, SString T);
bool StrDelete(SString S, int pos, int len);
void StrPrint(SString S);
