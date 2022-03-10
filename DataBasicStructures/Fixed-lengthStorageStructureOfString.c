/**
 * 串的定长存储结构的表示和实现
 */
#include<stdio.h>
#include<stdbool.h>
#include <string.h>

#define MAX_STR_LEN 40
typedef unsigned char SString [MAX_STR_LEN+1];//定义一个char[MAX_STR_LEN]类型SString.0号单元存放串的长度

#define destroyString ClearString //这两个函数功能一致
#define InitString ClearString //这两个函数功能一致

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

/**
 * 将chars字符串赋给T字符串
 * @return  赋值成功与否
 */ 
bool StrAssgin(SString T, char* chars)
{
    if(strlen(chars)>MAX_STR_LEN)//如果chars字符串的长度大于定长字符串的长度，返回false；strlen函数位于头文件string.h中，用于返回指定字符数组的长度
    {
        return false;
    }
    else
    {
        for(int i = 1;i < strlen(chars);i++ )
        {
            T[i] = *(chars+i-1);
        }
        T[0] = strlen(chars);
    }
}
/**
 * 将串S复制得T
 */ 
void StrCopy(SString T, SString S)
{
    for(int i = 0;i <= S[0];i++)
       T[i] = S[i];
}
bool StrIsEmpty(SString S)
{
    if(0 == S[0])
      return true;
    else
      return false;
}
/**
 * 用于两个串之间得比较
 * @return 返回0 相等；
 *         返回值>0 S>T；
 *         返回值<0 S<T
 */ 
int StrCompare(SString T, SString S)
{
    for(int i = 1;i<=T[0] && i<=S[0];i++)//先比较公共部分，如果能比较出结果则直接返回，如果不能则长度较大串较大
    {
        if(S[i] != T[i])
          return S[i]-T[i];
    }
    return S[0]-T[0];
}
void ClearString(SString T)
{
    T[0] = 0;
}
/**
 * 
 */ 
bool StrConcat(SString T, SString S1, SString S2)
{

}
bool SubString(SString Sub, SString S, int pos, int len);
bool Index1(SString S, SString T, int pos);
bool StrInsert(SString S, int pos, SString T);
bool StrDelete(SString S, int pos, int len);
void StrPrint(SString S);