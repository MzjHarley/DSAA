
```
|Author|Date|
|MZJ|3/8,2022|
```



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
    //测试用例：patten  -ababababcabaab              match    -ababcabaa
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
