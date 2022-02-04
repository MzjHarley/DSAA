/**
  *相比于TheExpressionEvaluates.c，使算数表达式的给出不拘泥于0~9.
  相比于TheExpressionEvaluates.c，改动在145~154行
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
Elemtype getTop(PS ps);

bool In(Elemtype c)//判断c是否是七种运算符之一
{
  if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c=='\n')
    return true;
  else
    return false;
}
/**
 * 比较t1和t2运算符的优先级。本质上看栈顶运算符和读取的运算符之间谁先运算。
 * @param t1 为运算符栈顶的运算符
 * @param t2 为新读取的运算符
 * @return 返回字符类型
 */
Elemtype precede(Elemtype t1, Elemtype t2)
{
    if(t2=='+' || t2=='-')
    {
        if(t1=='+' || t1=='-' || t1=='*' || t1=='/'|| t1==')')
            return '>';//t1>t2,则t1出栈运算，t2压栈
        else
            return '<';//这里如果t1为'('或'\n'则压栈
    }
    if(t2=='*'|| t2=='/')
    {
        if(t1=='+' || t1=='-' || t1=='(' || t1=='\n')
            return '<';//如果是这些字符的话，将t2压栈
        else
            return '>';//如果t1是'*','/'，')'的话，则t1>t2,t1出栈做运算
    }
    if(t2 == '(')
    {
        if(t1 == ')')
        {
            printf("括号不匹配.\n");
            exit(-1);
        }
        else
            return '<';
    }
    if(t2 == ')')
    {
        if(t1 == '(')
            return '=';
        else if(t1 == '\n')//t1如果为'\n',即栈顶为'\n',则栈中可操作字符为空
        {
            printf("缺乏左括号.\n");
            exit(-1);
        }
        else
            return '>';
    }
    if(t2 == '\n')
    {
        if(t1 == '\n')
            return '=';
        else if(t1 == '(')
        {
            printf("缺乏右括号.\n");
            exit(-1);
        }
        else
            return '>';
    }
}
/**
 * 运算函数.
 * @return 返回a与b作theta运算的值对应的字符
 */
Elemtype Operate(Elemtype a,Elemtype theta,Elemtype b)
{
    switch (theta)            
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
    }
    Elemtype t = (Elemtype)('0'-48);
    if(b != t)
        return a/b;
    else
    {
        printf("运算过程中0不能做除数.\n");
        exit(-1);
    }
}
/**
 * 求表达式值函数。
 * @return 字符类型
 */
Elemtype EvaluateExpression()
{
    PS OPTR = NULL, OPND = NULL;//创建两个栈：运算符栈（存放运算符）和数字栈（存放数字）
    OPTR = initStack(OPTR);
    OPND = initStack(OPND);
    Elemtype a, b, c, d;//定义临时变量，存放栈中的数据。
    push(OPTR,'\n');//初始化运算符栈
    c = getchar();//从控制台获取的字符
    d = getTop(OPTR);//获取运算符栈顶的字符
    while (c!='\n' || d!='\n')
    {
        if(In(c))//如果c是七种字符之一
        {
            switch (precede(d,c))
            {
                case '<': //栈顶字符优先级小，则将读取的字符压栈
                        push(OPTR,c);
                        c = getchar();
                        break;
                case '='://优先级相同，将栈顶字符出栈
                        pop(OPTR);
                        c = getchar();
                        break;
                case '>'://栈顶字符优先级大，则栈顶字符出栈作a d b运算并将运算结果压入到数字栈中
                        d = pop(OPTR);
                        b = pop(OPND);
                        a = pop(OPND);
                        push(OPND,Operate(a, d, b));
            }
            d = getTop(OPTR);
        }
        else if(c>='0' && c<='9')//如果是数字字符，则将数字字符对应的数字压入栈中。
        {
            a = 0;
            while(c>='0' && c<='9')//如果是连续数字
            {
                a = a * 10 + (c -48);//
                c = getchar();
            }//147~152使表达式不拘泥于0~9
            push(OPND,a);
        }
        else
        {
            printf("出现非法字符.\n");
            exit(-1);
        }
    }
    d = pop(OPND);
    if(!isEmpty(OPND))
    {
        printf("表达式出错.\n");//such as 3+12,(5+2)(3+6)and so on.
        exit(-1);
    }
    OPND = destroyStack(OPND);
    OPTR = destroyStack(OPTR);
    return d;
}
int main()
{
    printf("请输入算术表达式,负数用(0-正数)表示:\n");
    printf("%d",EvaluateExpression());//测试例子:(0-12)*((5-3)*3+2)/(2+2)
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
Elemtype getTop(PS ps)
{
    return *(ps->ptop-1);
}