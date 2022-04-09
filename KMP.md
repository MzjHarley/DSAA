
|Author|Date|
|---|---|
|MZJ|3/8,2022|
---
# KMP
## 求模式串的next数组
以ababcabaa为例
|模式串|a|ab|aba|abab|ababc|ababca|ababcab|ababcaba|ababcabaa|
|---|---|---|---|---|---|---|---|---|---|
|最长公共前后缀|0|0|1|2|0|1|2|3|1|

||a|b|a|b|c|a|b|a|a|
|---|---|---|---|---|---|---|---|---|---|
|下标i|0|1|2|3|4|5|6|7|8|
|最长公共前后缀|0|0|1|2|0|1|2|3|1|
|next[i]|-1|0|0|1|2|0|1|2|3|
```c
/**
 * patten 为模式串，next为next数组   
 * next先存取模式串的位移距离(最长公共前后缀)，之后整体向后移动1位，并将第一位置-1，即可得到位移下标next数组。
 */
void get_next(char*patten,int*next)
{
    int n = strlen(patten);//通过string.h文件中的strlen()方法获取模式串长度
    next[0]=0;//设置next[0]为0，因为第一个字符，没有最长公共前后缀
    int i = 1;//从patten串的第二个字符开始，下标为1
    int j = next[0];//j为next数组的值
    while(i<n)
    {
        if (patten[i]==patten[j])//如果相匹配，那么最长公共前后缀加1，并且赋给next数组
        {
            j++;
            next[i]=j;
            i++;
        }
        else 
        {
            if(j>0)//如果j>0则将其j-1的next值赋给j，这样做会满足所有情况，不要纠结于为什么是这样的
                j=next[j-1];
            else//j=0，将next[i]设为0
            {
                next[i]=0;
                i++;
            }
        } 
    }
    for(int k=n-1;k>0;k--)//将next数组的值整体向后移一位，并把第一位置-1，来设置要位移到的下标而非位移距离
        next[k]=next[k-1];
    next[0]=-1;
}
```
## 对next数组进行修正得到next_val数组
|j|匹配条件|next_val[j]|
|---|---|---|
|j==0|NULL|next_val[j]=next[j]|
|j>0|patten[j]==patten[next[j]]|next_val[j]=next_val[next[j]]|
|j>0|patten[j]!=patten[next[j]]|next_val[j]=next[j]|

**并不是所有情况都需要对next数组进行修正.  
若模式串中出现连续相同大量的的字母时需要修正来减少匹配次数，如aaaaab模式串的next数组就需要修正.**    

下面将ababcabaa的模式串修正。  
||下标i|next[i]|修正过程|next_val[i]|
|---|---|---|---|---|
|a|0|-1|NULL|-1|
|b|1|0|patten[next[1]]!=patten[1],则next_val[1]=next[1]|0|
|a|2|0|patten[next[2]]==patten[2],则next_val[2]=next_val[next[2]]|-1|
|b|3|1|patten[next[3]]==patten[3],则next_val[3]=next_val[next[3]]|0|
|c|4|2|patten[next[4]]!=patten[4],则next_val[4]=next[4]|2|
|a|5|0|patten[next[5]]==patten[5],则next_val[5]=next_val[next[5]]|-1|
|b|6|1|patten[next[6]]==patten[6],则next_val[6]=next_val[next[6]]|0|
|a|7|2|patten[next[7]]==patten[7],则next_val[7]=next_val[next[7]]|-1|
|a|8|3|patten[next[8]]!=patten[8],则next_val[8]=next[8]|3|

简单将aaaaab的模式串next数组修正
||a|a|a|a|a|b|
|---|---|---|---|---|---|---|
|下标i|0|1|2|3|4|5|
|next[i]|-1|0|1|2|3|4|
|next_val[i]|-1|-1|-1|-1|-1|4|

```c
/**
 * patten 为模式串，next为next数组,next_val为next修正后的数组  
 */
void get_nextVal(char*patten,int*next，int* next_val)
{
    int n = strlen(patten);
    next_val[0]=-1;
    int i = 1;//从patten串的第二个字符开始，下标为1
    int j = next[0];//j为next数组的值
    while(i<n)
    {
        if (j==-1 || patten[i]==patten[j])//如果j==-1或者相匹配
        {
            j++;
            if(patten[i]==patten[j])
                next_val[i]=next_val[next[i]];
            else
                next_val[i]=next[i];
            i++;
        }
        else
            j=next_val[j];//
    }
}
```
## KMP源代码
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 20
void get_next(char*match,int*next);
void KMP_Search(char*patten,char*match,int*next);
int main()
{
    char patten[MAX_SIZE];
    char match[MAX_SIZE];
    scanf("%s",patten);
    scanf("%s",match);
    int next[strlen(match)];
    get_next(match,next);
    KMP_Search(patten,match,next);
    return 0;
    //测试用例：primaryString  -ababababcabaab              
    //patten  -ababcabaa
}
void get_next(char*match,int*next)
{
    int n = strlen(match);
    next[0]=0;
    int i = 1;
    int j = 0;
    while(i<n)
    {
        if (match[i]==match[j])
        {
            j++;
            next[i]=j;
            i++;
        }
        else
        {
            if(j>0)
                j=next[j-1];
            else
            {
                next[i]=0;
                i++;
            }
        } 
    }
    for(int k=n-1;k>0;k--)
        next[k]=next[k-1];
    next[0]=-1;
}
void KMP_Search(char*patten,char*match,int*next)
{
    int m = strlen(patten);
    int n = strlen(match);
    int i = 0;
    int j = 0;
    while(i<m)
    {
        if(patten[i]==match[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
            if(-1==j)
            {
                j++;
                i++;
            }
        }
        if(j==n)
        {
            printf("found at %d.\n",i-n);
            j=next[j-1];
            i--;
        }
    }
}
```
