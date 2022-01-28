/*
 *行编辑程序
 *思路：将要写入文件的字符压入栈中,之后再写入文件中
 *如果碰到退格符'#'，就出栈删去一个字符；如果是退行符'@',就清空栈删去一行，其余字符压入栈中。
 *等到一行字符全部压入栈之后，就写入到文件中。一行字符一行字符的压栈出栈。
 */
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<stdbool.h>
#define INIT_STACK_SIZE 10
#define INCREASE 2
typedef char Elemtype;
FILE* fp;//定义文件指针，指向一个文件，它是一个全局变量
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
void clearStack(PS ps);
void LineEdit()
{
    PS ps = NULL;
    char ch;
    ps = initStack(ps);//初始化栈
    ch = getchar();//从控制台接收字符；
    //单独一行ctrl+Z结束
    while(ch != EOF)//EOF为ctrl+Z键，全文未结束时，行首字符不能ctrl+Z
    {
        while(ch!=EOF && ch!='\n') //未到行末时
        {
            switch(ch)
            {
                case '#':
                    if(!isEmpty(ps))
                    {
                        pop(ps);
                    }
                    break;
                case '@':
                    clearStack(ps);
                    break;
                default:
                    push(ps,ch);
            }
            ch = getchar();
        }
        //压栈完成后将栈中的字符写入文件并写入换行符
        char * p = ps->pbase;
        while(ps->ptop > p)
        {
            fputc(*p,fp);//将栈中字符送入到文件fp中
            p++;
        }
        fputc('\n',fp);
        clearStack(ps);
        if(ch != EOF)
        {
            ch = getchar();
        }
    }
    ps = destroyStack(ps);
}
int main()
{
    fp = fopen("test.txt","w");//以“写入”方式打开文件。如果文件不存在，那么创建一个新文件；如果文件存在，那么清空文件内容（相当于删除原文件，再创建一个新文件）。
    if(fp)  //fp不为NULL
    {
        LineEdit();//编辑文件
        fclose(fp);//结束后关闭文件
    }
    else
    {
        printf("打开文件失败.\n");
    }
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
void clearStack(PS ps)
{
    ps->ptop = ps->pbase;
}
