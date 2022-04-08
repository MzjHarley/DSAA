
|Author|Date|
|---|---|
|MZJ|3/8,2022|

# KMP
## 求模式串ababcabaa的next数组
|模式串|最长公共前后缀|
|---|---|
|a|0|
|ab|0|
|aba|1|
|abab|2|
|ababc|0|
|ababca|1|
|ababcab|2|
|ababcaba|3|
|ababcabaa|1|



||a|b|a|b|c|a|b|a|a|
|---|---|---|---|---|---|---|---|---|---|
|下标i|0|1|2|3|4|5|6|7|8|
|移动距离|0|0|1|2|0|1|2|3|1|
|next[i]|-1|0|0|1|2|0|1|2|3|

## 对next数组进行修正得到next_val数组

**并不是所有情况都需要对next数组进行修正，若模式串中出现连续相同大量的的字母时需要修正来减少匹配次数，如aaaaaaaab模式串的next数组就需要修正.**  
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

## KMP源代码
测试用例：patten  -ababababcabaab              match    -ababcabaa
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
