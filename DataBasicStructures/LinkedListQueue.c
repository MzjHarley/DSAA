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
        q->front->next = destroyQueue(q->front->next);
        q->rear = q->front;
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
        return false;
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
        return true;
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
