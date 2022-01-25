/**
 * 链式栈，链表来实现的栈结构。
 * 操作：初始化，清空，销毁，入栈，出栈，判断是否为空，遍历，得到长度。
 */
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
typedef struct Elem
{
    int data;
    struct Elem* next;
}E,*PE;
typedef struct LinkedListStack
{
    PE top;
    PE base;
}L,*PL;
PL initStack(PL pl);
void clearStack(PL pl);
PL destroyStack(PL pl);
void push(PL pl);
void pop(PL pl);
bool isEmpty(PL pl);
void printStack(PL pl);
int getLength(PL pl);
int main()
{
    printf("******************\n");
    printf("*1.initStack     *\n");
    printf("*2.PushStack     *\n");
    printf("*3.Popltack      *\n");
    printf("*4.clearStack    *\n");
    printf("*5.Empty Or Not  *\n");
    printf("*6.printStack    *\n");
    printf("*7.destroyStack  *\n");
    printf("*8.getLength     *\n");
    printf("******************\n");
    int num;
    char str;
    PL pl = NULL;
    do
    {
        printf("Input Operand:");
        scanf("%d",&num);
        if(num>0 && num<9)
        {
            switch(num)
            {
                case 1:
                    pl = initStack(pl);
                    break;
                case 2:
                    push(pl);
                    break;
                case 3:
                    pop(pl);
                    break;
                case 4:
                    clearStack(pl);
                    break;
                case 5:
                    if(NULL == pl)
                    {
                        printf("pl is NULL.\n");
                    }
                    else
                    {
                        if(isEmpty(pl))
                        {
                            printf("Empty.\n");
                        }
                        else
                        {
                            printf("Not Empty.\n");
                        }
                    }
                    break;
                case 6:
                    printStack(pl);
                    break;
                case 7:
                    pl = destroyStack(pl);
                    break;
                case 8:
                    if(NULL == pl)
                    {
                        printf("pl is NULL.\n");
                    }
                    else
                    {
                        printf("长度:%d.\n",getLength(pl));
                    }
            }
        }
        else
        {
            printf("Error Operand.\n");
        }
        printf("Continue Or Not(Y/N):");
        scanf(" %c",&str);
    }
    while(str == 'Y'|| str == 'y');
    return 0;
}
PL initStack(PL pl)
{
    if(pl)
    {
        pl = destroyStack(pl);
    }
    pl = (PL)malloc(sizeof(L));
    if(NULL == pl)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        pl->base = (PE)malloc(sizeof(E));
        if(NULL == pl->base)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        pl->base->next = NULL;
        pl->top = pl->base;
    }
    return pl;
}
void clearStack(PL pl)
{
    if(NULL == pl)
    {
        printf("pl is NULL.\n");
        return;
    }
    PE p = pl->top;
    while(p != pl->base)
    {
        PE q = p->next;
        free(p);
        p = q;
    }
}
PL destroyStack(PL pl)
{
    if(NULL == pl)
    {
        printf("pl is NULL.\n");
        return NULL;
    }
    clearStack(pl);
    free(pl->base);
    free(pl);
    return NULL;
}
void push(PL pl)
{
    if(NULL == pl)
    {
        printf("pl is NULL.\n");
        return;
    }
    int val;
    printf("请输入你想压栈的值:");
    scanf("%d",&val);
    PE pnew = (PE)malloc(sizeof(E));
    if(NULL == pnew)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        pnew->data = val;
        pnew->next = pl->top;
        pl->top = pnew;
    }
}
void pop(PL pl)
{
    if(NULL == pl)
    {
        printf("pl is NULL.\n");
        return;
    }
    if(isEmpty(pl))
    {
        printf("stack is empty.\n");
        return;
    }
    printf("出栈的值:%d.\n",pl->top->data);
    PE p = pl->top;
    pl->top = p->next;
    free(p);
}
bool isEmpty(PL pl)
{
    if(pl->top == pl->base)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void printStack(PL pl)
{
    if(NULL == pl)
    {
        printf("pl is NULL.\n");
        return;
    }
    if(isEmpty(pl))
    {
        printf("Stack is empty.\n");
        return;
    }
    PE p = pl->top;
    while(p != pl->base)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
int getLength(PL pl)
{
    int i = 0;
    PE p = pl->top;
    while(p != pl->base)
    {
        i++;
        p = p->next;
    }
    return i;
}