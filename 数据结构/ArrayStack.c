/**
 * 栈是一种后进先出的存储结构。
 * 这是顺序栈的操作及实现。
 * 初始化，清空，销毁，判断为空，得到长度，入栈，出栈，遍历。
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#define INIT_STACK_SIZE 10
typedef struct Stack
{
    int *data;
    int length;//存放栈的长度
    int stacksize;//存放栈的容量
}S,*PS;
PS initArrayStack(PS ps);
void clearArrayStack(PS ps);
PS destroyArrayStack(PS ps);
bool isEmpty(PS ps);
int getLength(PS ps);
bool push(PS ps);
bool pop(PS ps);
void printArrayStack(PS ps);
int main()
{
    printf("***********************\n");
    printf("*1.initArrayStack     *\n");
    printf("*2.PushStack          *\n");
    printf("*3.PopStack           *\n");
    printf("*4.clearArrayStack    *\n");
    printf("*5.Empty Or Not       *\n");
    printf("*6.printArrayStack    *\n");
    printf("*7.destroyArrayStack  *\n");
    printf("*8.getLength          *\n");
    printf("***********************\n");
    int num;
    char str;
    PS ps=NULL;
    do
    {
        printf("Input Operand:");
        scanf("%d",&num);
        if(num>0 && num<9)
        {
            switch(num)
            {
                case 1:
                    ps = initArrayStack(ps);
                    break;
                case 2:
                    push(ps);
                    break;
                case 3:
                    pop(ps);
                    break;
                case 4:
                    clearArrayStack(ps);
                    break;
                case 5:
                    if(NULL == ps)
                    {
                        printf("ps is NULL.\n");
                    }
                    else
                    {
                        if(isEmpty(ps))
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
                    printArrayStack(ps);
                    break;
                case 7:
                    ps = destroyArrayStack(ps);
                    break;
                case 8:
                    printf("长度:%d.\n",getLength(ps));
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
PS initArrayStack(PS ps)
{
    if(ps)
    {
        ps = destroyArrayStack(ps);
    }
    ps = (PS)malloc(sizeof(S));
    if(NULL == ps)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        ps->data = (int *)malloc(sizeof(int)*INIT_STACK_SIZE);
        if (NULL == ps->data)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps->length = 0;
        ps->stacksize = INIT_STACK_SIZE;
    }
    return ps;
}
void clearArrayStack(PS ps)
{
    if(NULL == ps)
    {
        printf("ps is NULL.\n");
    }
    else if (isEmpty(ps))
    {
        printf("Stack is already empty.\n");
    }
    else
    {
        ps->length = 0;
    }
}
PS destroyArrayStack(PS ps)
{
    if(NULL == ps)
    {
        printf("ps is NULL.\n");
        return NULL;
    }
    free(ps->data);
    free(ps);
    return NULL;
}
bool isEmpty(PS ps)
{
    if(0 == ps->length)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int getLength(PS ps)
{
    return ps->length;
}
bool push(PS ps)
{
    if(NULL == ps)
    {
        printf("ps is NULL.\n");
        return false;
    }
    if(ps->length == ps->stacksize)
    {
        ps->data = (int*)realloc(ps->data,sizeof(int)*(ps->length+INIT_STACK_SIZE));
        if(NULL == ps->data)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps->stacksize = ps->length+INIT_STACK_SIZE;
    }
    printf("push前:");
    printArrayStack(ps);
    int val;
    printf("请输入你要压栈的元素:");
    scanf("%d",&val);
    ps->data[ps->length] = val;
    ps->length++;
    printf("push后:");
    printArrayStack(ps);
    return true;
}
bool pop(PS ps)
{
    if(NULL == ps)
    {
        printf("ps is NULL.\n");
        return false;
    }
    if(isEmpty(ps))
    {
        printf("Stack is Empty.\n");
        return false;
    }
    printf("pop前:");
    printArrayStack(ps);
    printf("出栈元素:%d.\n",ps->data[ps->length-1]);
    ps->length--;
    printf("pop后:");
    printArrayStack(ps);
}
void printArrayStack(PS ps)
{
    if(NULL == ps)
    {
        printf("ps is NULL.\n");
    }
    else if (isEmpty(ps))
    {
        printf("Stack is empty.\n");
    }
    else
    {
        for(int i = ps->length-1;i >= 0;i--)
        {
            printf("%d ",ps->data[i]);
        }
        printf("\n");
    }
}
