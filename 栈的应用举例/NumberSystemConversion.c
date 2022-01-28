/*
 *数制转换：利用栈将数字转换进制后得到的数字压栈，之后在出栈。 n为要转换的数字，N为进制
 *以十进制转换为八进制为例。
 */
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h>
#define INIT_STACK_SIZE 10
#define INCREASE 2
#define N 8
typedef int Elemtype;
typedef struct Stack
{
    Elemtype * pbase;
    Elemtype * ptop;
    int stackSize;
}S,*PS;
PS destroyStack(PS ps);
PS initStack(PS ps);
bool isEmpty(PS ps);
void push(PS ps,int val);
Elemtype pop(PS ps);
int main()
{
    PS ps = NULL;
    ps = initStack(ps);
    printf("请输入你想要转换的十进制数:");
    int n;
    scanf("%u",&n);
    while (n)
    {
        push(ps,n%N);
        n /= N;
    }
    printf("转换后的数字为:");
    while(!isEmpty(ps))
    {
        Elemtype e = pop(ps);
        printf("%d",e);
    }
    printf("\n");
    ps = destroyStack(ps);
    return 0;
}
/**
 * 思考若是转换为16机制呢？
 * 这是在pop的时候加上判断条件让其可以转变为字母。
 while(!isEmpty(ps))
 {
    Elemtype e = pop(ps);
    if(e<10)
    {
        printf("%d",e);
    }
    else
    {
        printf("%c",e+55);
    }
 }
 */
PS destroyStack(PS ps)
{
    free(ps->pbase);
    free(ps);
    return NULL;
}
PS initStack(PS ps)
{
    if(ps)
    {
        ps = destroyStack(ps);
    }
    ps = (PS)malloc(sizeof(S));
    if(NULL == ps)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        ps->pbase = (Elemtype*)malloc(sizeof(Elemtype)*INIT_STACK_SIZE);
        if(NULL == ps->pbase)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps->ptop = ps->pbase;
        ps->stackSize = INIT_STACK_SIZE;
    }
    return ps;
}
bool isEmpty(PS ps)
{
    if(ps->pbase == ps->ptop)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void push(PS ps,int val)
{
    if((ps->ptop - ps->pbase) == ps->stackSize)
    {
        ps->pbase = (Elemtype*)realloc(ps->pbase, sizeof(Elemtype)*((ps->ptop - ps->pbase)+INCREASE));
        if(NULL == ps->pbase)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps->ptop = (ps->ptop - ps->pbase) + ps->pbase;
    }
    *(ps->ptop) = val;
    ps->ptop++;
}
Elemtype pop(PS ps)
{
    ps->ptop--;
    return *(ps->ptop);
}
