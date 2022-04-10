
|Author|Date|
|---|---|
|MZJ|3/8,2022|
---
# KMP
**Today I will make a summary of String-Match algorithm KMP.  
The array named next stores the moving index.And the array named next_val is a correction to array next.  
Why do we need to correct the array next? You know not all cases require correction of array next.If there is a continuous same number of letters in the pattern string, a correction is required to reduce the number of matches,such as 'aaaaaab'.  
You know patten's initial index will influence the values of array named next and next_val.  
So I divide it into two parts based on whether the patten's initial index is 0 or 1.**
## patten's initial index form 0
![contents](https://github.com/MzjHarley/DataStructuresAndAlgorithms/blob/main/IMG/1.png)  
**We will take 'ababcabaa' as an example.  
LCPX is 'The longest common prefix and suffix'.**

|patten|a|b|a|b|c|a|b|a|a|
|---|---|---|---|---|---|---|---|---|---|
|index|**0**|1|2|3|4|5|6|7|8|
|LCPX[i]|0|0|1|2|0|1|2|3|1|
|next[i]|-1|0|0|1|2|0|1|2|3|
|next_val[i]|-1|0|-1|0|2|-1|0|-1|3|

```C
void get_next(char*patten,int*next)
{
    int i = 0, j = -1;
    next[0]=-1;
    while(i<strlen(patten))
        if(j==-1 || patten[i]==patten[j])
            next[++i]=++j;
        else
            j= next[j];
}

void get_nextVal(char*patten,int*next,int* next_val)
{
    int i =  0, j = -1;
    next_val[0] = -1;
    while(i<strlen(patten))
    {
        if(j==-1|| patten[i]==patten[j])
            next_val[i]=patten[++i]==patten[++j]?next_val[j]:j;
        else
            j=next_val[j];
    }
}

void KMP_Search(char*primaryString,char*patten,int*next)
{
    int times = 0;//record appearence times of patten
    int i = 0, j = 0;
    while(i<strlen(primaryString))
    {
        if(j==-1 ||primaryString[i]==patten[j])
        {
            i++;
            j++;
        }
        else
            j=next[j];
        if(j==strlen(patten))
        {
            times++;
            printf("found at %d.\n",i-j);
            j=next[j-1];
            i--;
        }
    }
    if(0==times)
        printf("Not found.\n");
}
```
## patten's initial index form 1
![contents](https://github.com/MzjHarley/DataStructuresAndAlgorithms/blob/main/IMG/2.png)  
**We still take 'ababcabaa' as an example.  
LCPX is 'The longest common prefix and suffix'.**
|patten|a|b|a|b|c|a|b|a|a|
|---|---|---|---|---|---|---|---|---|---|
|index|**1**|2|3|4|5|6|7|8|9|
|LCPX[i]|0|0|1|2|0|1|2|3|1|
|next[i]|0|1|1|2|3|1|2|3|4|
|next_val[i]|0|1|0|1|3|0|1|0|4|




