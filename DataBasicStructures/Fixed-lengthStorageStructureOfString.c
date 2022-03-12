/**
 * 串的定长存储结构的表示和实现
 */
#include<stdio.h>
#include<stdbool.h>
#include <string.h>

#define MAX_STR_LEN 40
typedef unsigned char SString[MAX_STR_LEN+1];//定义一个char[MAX_STR_LEN]类型SString.   0号单元存放串的长度

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
 * 将chars字符数组赋给T字符串
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
void ClearString(SString T)//这和destroyString，InitString一致
{
    T[0] = 0;
}
/**
 * 连接字符串s1和s2并将其赋给T
 * @return 返回是否截断，截断则返回false，未截断则返回true
 */ 
bool StrConcat(SString T, SString s1, SString s2)
{
    if(s1[0]+s2[0]<=MAX_STR_LEN) //未截断
    {
        for(int i = 1;i <= s1[0];i++)
        {
            T[i]=s1[i];
        }
        for(int i = 1;i <= s2[0];i++)
        {
            T[i+s[0]] = s2[i];
        }
        T[0]=s1[0]+s2[0];
        return true;
    }
    else//截断
    {
        for(int i = 1;i <= s1[0];i++)
        {
            T[i]=s1[i];
        }
        for(int i = 1;i <= MAX_STR_LEN-s[0];i++)
        {
            T[i+s[0]] = s2[i];
        }
        return false;
    }
}
/**
 * 将s串从pos位置开始长度为len的子串赋给sub，包括pos位置
 * @return 是否求子串成功
 */ 
bool SubString(SString sub, SString s, int pos, int len)
{
    if(pos<0 || pos>s[0] || len<0 || len > s[0]-pos+1)//这里len的范围需要计算，因为从pos开始之后的串的长度是s[0]-pos+1,因此len不能大于这个长度
       return false;
    else
    {
        for(int i = 1;i <= len;i++)
        {
            sub[i] = s[pos+i-1];
        }
        sub[0] = len;
        return true;
    }
}
/**
 * 找到串T在串s中从pos开始的第一个位置
 * @ return 返回位置，若未找到则返回0；否则返回第一个位置 
 **/ 
int Index1(SString s, SString T, int pos)
{
    if(pos<0 || pos>s[0])
    {
        return 0
    }
    else
    {
        int i=pos,j=1;
        while(i<=s[0] && j<=T[0])
        {
            if(s[i] == T[i])
            {
                i++;
                j++;
            }
            else
            {
                j=1;
                i=i-j+2;//以第一次的比较为准算出特殊的位置关系
            }
        }
        if(j>T[0])//当找到T位置时j的数值会大于T[0]
        {
            return i-T[0];
        }
        else
        {
            return 0;
        }
    }
}
/**
 * 和index1函数功能一致，只是算法不同。
 */ 
int index2(SString s, SString T, int pos)
{

}
/**
 * 在index1或index2的基础上找到T在s从pos开始的所有位置
 * @return 返回位置的个数
 */ 
int indexAll(SString s, SString T, int pos)
{
    if(pos<0 || pos>s[0])
      return 0;
    else
    {
        int times = 0;
        int i=pos;
        print("位置为")
        while(i <=S [0])
        {
            int j = Index1(s,T,i);//这里也可以替换为index2函数
            if(0 != j)
            {
                i = j+T[0];
                printf("%d ",j);
                times++;
            }
            else
            {
                break;
            }
        }
        if(0 == times)
        {
            printf(",未出现该子串.\n");
        }
        else
        {
            printf(",该字串共出现%d次.\n",times);
        }
        return times;
    }
}
/**
 * 
 */ 
int StrInsert(SString s, int pos, SString T)
{
    if(pos<0 || pos>s[0]+1)
        return 0;
    else
    {
        if(s[0]+T[0]<=MAX_STR_LEN)//未截断插入
        {
            for(int i = s[0];i>=pos;i--)
            {
                s[i+T[0]]=s[i];
            }
            for(int i = pos;i < pos+T[0];i++)
            {
                s[i] = T[i-pos+1];
            }
            s[0] += T[0];
            return 1;
        }
        else //截断插入,牺牲掉s的部分子串，让新的子串可以插入进去
        {
            int leftSize =MAX_STR_LEN-s[0]; //串s余下的存储空间
            for(int i = s[0];i >= pos;i--)
            {
                s[i+leftSize] = s[i];
            }
            for(int i = pos;i < pos+T[0];i++)
            {
                s[i] = t[i-pos+1];
            }
            s[0] = MAX_STR_LEN;
            return 2;
        }
    }
}
/**
 * 
 */ 
bool StrDelete(SString s, int pos, int len)
{
    if(pos<0 || pos>s[0] || len<0 || len>s[0]-pos+1)
        return false;
    else
    {
        for(int i = pos+len;i <=s[0];i++) //从pos位置开始的len个字符被删除范围应该是[pos,pos+len-1]，则应该将从pos+len位置开始之后的字符（包括pos+len位置上的字符）前移到从pos开始的位置
        {
            s[i-len] = s[i];
        }
        s[0] -= len;//迁移之后减去删除的串的长度len即可
        return true;
    } 
}
/**
 * 
 */ 
bool StrDeleteDependValue(SString s,SString t)
{

}
/**
 * 
 */ 
bool SStringReplace(SString s,SString T,SString v)
{

}
/**
 * @description 打印字符串
 */ 
void StrPrint(SString s)
{
    for(int i=1;i<s[0];i++)
    {
        print("%c",s[i]);
    }
    printf("\n");
}
