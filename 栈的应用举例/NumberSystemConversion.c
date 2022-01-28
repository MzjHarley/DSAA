/*
 *1.����ת��������ջ������ת�����ƺ�õ�������ѹջ��֮���ڳ�ջ�� nΪҪת�������֣�NΪ����
 ��ʮ����ת��Ϊ�˽���Ϊ����
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
int main()
{
    PS ps = NULL;
    ps = initStack(ps);
    printf("����������Ҫת����ʮ������:");
    int n;
    scanf("%u",&n);
    while (n)
    {
        push(ps,n%N);
        n /= N;
    }
    printf("ת���������Ϊ:");
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
 * ˼������ת��Ϊ16�����أ�
 * ������pop��ʱ������ж������������ת��Ϊ��ĸ��
 *  while(!isEmpty(ps))
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