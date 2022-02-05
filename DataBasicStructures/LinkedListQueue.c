/**
 * 队列，一种先进先出的存储结构。
 * 我将实现链式队列的所有高级操作：
 * 初始化,销毁,清空,得到长度,判断是否为空,得到队头元素,入队,出队,遍历，共9个操作
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int Elemtype;
typedef struct Elem
{
    Elemtype data;
    struct Elem *next;
}E, *PE;
typedef struct LinkedListQueue
{
    PE front;
    PE rear;
}Q, *PQ;

PQ initQueue();
PQ destroyQueue(PQ);
void clearQueue(PQ);
int getLength(PQ);
bool isEmpty(PQ);
Elemtype getHead(PQ);
void  EnQueue(PQ,Elemtype);
Elemtype DeQueue(PQ);
void TraverseQueue(PQ);

int main()
{
    printf("******************\n");
    printf("*1.initQueue     *\n");
    printf("*2.EnQueue       *\n");
    printf("*3.DeQueue       *\n");
    printf("*4.clearQueue    *\n");
    printf("*5.Empty Or Not  *\n");
    printf("*6.printQueue    *\n");
    printf("*7.destroyQueue  *\n");
    printf("*8.getLength     *\n");
    printf("*9.getHead       *\n");
    printf("******************\n");
    int num;
    char str;
    Elemtype val;
    PQ q = NULL;
    do
    {
        printf("Input Operand:");
        scanf("%d",&num);
        if(num>0 && num<10)
        {
            switch(num)
            {
                case 1:
                    q = initQueue();
                    break;
                case 2:
                    if(q)
                    {
                        printf("请输入你要入队的元素:");
                        scanf("%d",&val);
                        EnQueue(q, val);
                    }
                    else
                    {
                        printf("Queue is NULL.\n");
                    }
                    break;
                case 3:
                    if(!q)
                    {
                        printf("queue is NULL.\n");
                    }
                    else if(isEmpty(q))
                    {
                        printf("queue is empty.\n");
                    }
                    else
                    {
                        printf("出队的元素为%d.\n",DeQueue(q));
                    }
                    break;
                case 4:
                    clearQueue(q);
                    break;
                case 5:
                    if(!q)
                    {
                        printf("queue is NULL.\n");
                    }
                    else
                    {
                        if(isEmpty(q))
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
                    TraverseQueue(q);
                    break;
                case 7:
                    q = destroyQueue(q);
                    break;
                case 8:
                    if(!q)
                    {
                        printf("queue is NULL.\n");
                    }
                    else
                    {
                        printf("长度:%d.\n",getLength(q));
                    }
                    break;
                case 9:
                    if(!q)
                    {
                        printf("Queue is NULL.\n");
                    }
                    else if(isEmpty(q))
                    {
                        printf("Queue is Empty.\n");
                    }
                    else
                    {
                        printf("队头元素为%d.\n",getHead(q));
                    }
                    break;
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

PQ initQueue()
{
    PQ q = (PQ)malloc(sizeof(Q));
    if(!q)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        q->front = q->rear = (PE)malloc(sizeof(E));
        if(!q->front)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        else
        {
            q->front->next = NULL;
        }
    }
    return q;
}
PQ destroyQueue(PQ q)
{
    if(!q)
    {
        printf("Arguments is NULL.\n");
    }
    else
    {
        PE p = q->front,r;
        while(p)
        {
            r = p->next;
            free(p);
            p = r;
        }
        free(q);
    }
    return NULL;
}
void clearQueue(PQ q)
{
    if(!q)
    {
        printf("queue is NULL.\n");
    }
    else
    {
        destroyQueue(q);
        q = initQueue();
    }
}
int getLength(PQ q)
{
    int i = 0;
    PE p = q->front->next;
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}
bool isEmpty(PQ q)
{
    if(q->front == q->rear)
        return true;
    else
        return false;
}
Elemtype getHead(PQ q)
{
    return q->front->next->data;
}
void EnQueue(PQ q,Elemtype val)
{
    if(!q)
    {
        printf("Arguments is NULL.\n");
    }
    else
    {
        PE p = (PE)malloc(sizeof(E));
        if(!p)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        else
        {
            p->data = val;
            p->next = NULL;
        }
        q->rear->next = p;
        q->rear = p;
    }
}
Elemtype DeQueue(PQ q)
{
    PE p = q->front->next;
    Elemtype t = p->data;
    q->front->next = p->next;
    if(q->rear == p)
    {
        q->rear = q->front;
    }
    free(p);
    return t;
}
void TraverseQueue(PQ q)
{
    if(!q)
    {
        printf("Arguments is NULL.\n");
    }
    else if(isEmpty(q))
    {
        printf("Queue is empty.\n");
    }
    else
    {
        PE p = q->front->next;
        while(p)
        {
            printf("%d ",p->data);
            p = p->next;
        }
        printf("\n");
    }
}
