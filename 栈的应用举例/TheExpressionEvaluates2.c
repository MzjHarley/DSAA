/**
  *�����TheExpressionEvaluates.c��ʹ�������ʽ�ĸ�����������0~9.
  �����TheExpressionEvaluates.c���Ķ���145~154��
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

bool In(Elemtype c)//�ж�c�Ƿ������������֮һ
{
  if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c=='\n')
    return true;
  else
    return false;
}
/**
 * �Ƚ�t1��t2����������ȼ��������Ͽ�ջ��������Ͷ�ȡ�������֮��˭�����㡣
 * @param t1 Ϊ�����ջ���������
 * @param t2 Ϊ�¶�ȡ�������
 * @return �����ַ�����
 */
Elemtype precede(Elemtype t1, Elemtype t2)
{
    if(t2=='+' || t2=='-')
    {
        if(t1=='+' || t1=='-' || t1=='*' || t1=='/'|| t1==')')
            return '>';//t1>t2,��t1��ջ���㣬t2ѹջ
        else
            return '<';//�������t1Ϊ'('��'\n'��ѹջ
    }
    if(t2=='*'|| t2=='/')
    {
        if(t1=='+' || t1=='-' || t1=='(' || t1=='\n')
            return '<';//�������Щ�ַ��Ļ�����t2ѹջ
        else
            return '>';//���t1��'*','/'��')'�Ļ�����t1>t2,t1��ջ������
    }
    if(t2 == '(')
    {
        if(t1 == ')')
        {
            printf("���Ų�ƥ��.\n");
            exit(-1);
        }
        else
            return '<';
    }
    if(t2 == ')')
    {
        if(t1 == '(')
            return '=';
        else if(t1 == '\n')//t1���Ϊ'\n',��ջ��Ϊ'\n',��ջ�пɲ����ַ�Ϊ��
        {
            printf("ȱ��������.\n");
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
            printf("ȱ��������.\n");
            exit(-1);
        }
        else
            return '>';
    }
}
/**
 * ���㺯��.
 * @return ����a��b��theta�����ֵ��Ӧ���ַ�
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
        printf("���������0����������.\n");
        exit(-1);
    }
}
/**
 * ����ʽֵ������
 * @return �ַ�����
 */
Elemtype EvaluateExpression()
{
    PS OPTR = NULL, OPND = NULL;//��������ջ�������ջ������������������ջ��������֣�
    OPTR = initStack(OPTR);
    OPND = initStack(OPND);
    Elemtype a, b, c, d;//������ʱ���������ջ�е����ݡ�
    push(OPTR,'\n');//��ʼ�������ջ
    c = getchar();//�ӿ���̨��ȡ���ַ�
    d = getTop(OPTR);//��ȡ�����ջ�����ַ�
    while (c!='\n' || d!='\n')
    {
        if(In(c))//���c�������ַ�֮һ
        {
            switch (precede(d,c))
            {
                case '<': //ջ���ַ����ȼ�С���򽫶�ȡ���ַ�ѹջ
                        push(OPTR,c);
                        c = getchar();
                        break;
                case '='://���ȼ���ͬ����ջ���ַ���ջ
                        pop(OPTR);
                        c = getchar();
                        break;
                case '>'://ջ���ַ����ȼ�����ջ���ַ���ջ��a d b���㲢��������ѹ�뵽����ջ��
                        d = pop(OPTR);
                        b = pop(OPND);
                        a = pop(OPND);
                        push(OPND,Operate(a, d, b));
            }
            d = getTop(OPTR);
        }
        else if(c>='0' && c<='9')//����������ַ����������ַ���Ӧ������ѹ��ջ�С�
        {
            a = 0;
            while(c>='0' && c<='9')//�������������
            {
                a = a * 10 + (c -48);//
                c = getchar();
            }//147~152ʹ���ʽ��������0~9
            push(OPND,a);
        }
        else
        {
            printf("���ַǷ��ַ�.\n");
            exit(-1);
        }
    }
    d = pop(OPND);
    if(!isEmpty(OPND))
    {
        printf("���ʽ����.\n");//such as 3+12,(5+2)(3+6)and so on.
        exit(-1);
    }
    OPND = destroyStack(OPND);
    OPTR = destroyStack(OPTR);
    return d;
}
int main()
{
    printf("�������������ʽ,������(0-����)��ʾ:\n");
    printf("%d",EvaluateExpression());//��������:(0-12)*((5-3)*3+2)/(2+2)
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