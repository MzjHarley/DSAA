/**
  * 用栈求表达式的值。
  * 1.利用getchar获取表达式，例如3*（7-2），由于是getchar获取的表达式，所以运算符有7种可能：'+','-','*','/','(',')','\n'
  * 2.创建并初始化两个栈：运算符栈（存放运算符）和数字栈（存放数字）
  * 3.将数字字符对应的数字和运算符压入到各自的栈中，并利用运算符间的优先级关系进行运算。
  * 4.返回运算结果
  * 理解这个程序有几个比较重要的点：
  * 1.字符减去48，得到的结果为int类型，如 '1'-48=1.
  * 2.将int类型赋值给char，是将其补码后八位对应的字符赋给char，比如char c = 48,结果为字符0，十进制输出为48。
  * 3.字符之间可以加减乘除，运算结果为整型（其十进制ASCII码加减乘除），例如'3'+'5' 结果为104=51+53
  */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define INIT_STACK_SIZE 10
#define INCREASE 2

typedef char Elemtype;
typedef struct Stack
{
    Elemtype * pbase;
    Elemtype * ptop;
    int stackSize;
}S,*PS;
PS destroyStack(PS ps);
PS initStack(PS ps);
bool isEmpty(PS ps);
void push(PS ps,Elemtype val);
Elemtype pop(PS ps);

bool In(Elemtype c)//判断c是否是七种运算符之一
{
  if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c=='\n')
    return true;
  else
    return false;
}
/**
 * 比较t1和t2运算符的优先级。
 * @param t1 为运算符栈顶的运算符
 * @param t2 为新读取的运算符
 */
Elemtype precede(Elemtype t1, Elemtype t2)
{
  if(t2=='+' || t2=='-')
  {
    
  }
}

Elemtype EvaluateExpression()
{
  PS OPTR,OPND;//创建两个栈：运算符栈（存放运算符）和数字栈（存放数字）
  Elemtype a, b, c, d;
  OPTR = initStack(OPTR);
  OPND = initStack(OPND);

}
int main()
{

    return 0;
}
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
void push(PS ps,Elemtype val)
{
    if((ps->ptop - ps->pbase) == ps->stackSize)
    {
        ps->pbase = (Elemtype*)realloc(ps->pbase, sizeof(Elemtype)*((ps->ptop - ps->pbase)+INCREASE));
        if(NULL == ps->pbase)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps->ptop = ps->stackSize + ps->pbase;
        ps->stackSize += INCREASE;
    }
    *(ps->ptop) = val;
    ps->ptop++;
}
Elemtype pop(PS ps)
{
    ps->ptop--;
    return *(ps->ptop);
}
