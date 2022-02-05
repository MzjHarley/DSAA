/**
 * 循环队列，用数组实现的队列结构，当队列满时，再入队则将新元素入队到第一个元素上，而不再分配新的内存空间。
 * 操作有:初始化,销毁,清空,得到长度,判断是否为空,得到队头元素,入队,出队,遍历
 * 1.静态队列一般为什么必须为循环队列？ 传统数组实现队列会造成空间浪费；
 * 2.循环队列需要几个参数来确定？两个int参数front和rear；front永远指向队列的第一个元素，rear永远指向最后一个有效元素的下一个位置.
 * 3.front和rear这两个参数在不同场合的不同含义:
 * 队列初始化：front和rear值都为0；
 * 队列为空：front和rear值相等但不一定为0；
 * 队列非空：front指向第一个元素，rear指向最后一个有效元素的下一个位置；
 * 4.循环队列入队伪算法：将值存入rear所代表的位置；rear =（rear+1）%数组长度；
 * 5.循环队列出队伪算法：front =（front+1）%数组长度；
 * 6.如何判断循环队列是否为满？
 * 要么多设置一个参数，该参数名为长度，但频繁更新较麻烦；
 * 要么存n个元素，找n+1个空间，空间浪费率为1/n+1，n越大，浪费率越低；这种方式front与rear相邻时为满；此时（rear+1）%数组长度==front；
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INIT_QSIZE 5
typedef int Elemtype;
typedef struct CircularQueue
{
    Elemtype* pbase;
    int front;//永远指向队头
    int rear;//永远指向队尾元素的下一个位置
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
    PQ q;
    q = (PQ)malloc(sizeof(Q));
    if(!q)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        q->pbase = (Elemtype*)malloc(sizeof(Elemtype)*INIT_QSIZE);
        if (!q->pbase)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        q->front = q->rear = 0;
    }
    return q;
}
PQ destroyQueue(PQ q)
{
    if(!q)
    {
        printf("queue is NULL.\n");
    }
    else
    {
        free(q->pbase);
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
    else if(isEmpty(q))
    {
        printf("queue is already empty.\n");
    }
    else
    {
        q->rear = q->front = 0;
    }
}
int getLength(PQ q)
{
    return (q->rear - q->front + INIT_QSIZE)%INIT_QSIZE;
}
bool isEmpty(PQ q)
{
    if(q->front == q->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}
Elemtype getHead(PQ q)
{
    return q->pbase[q->front];
}
void EnQueue(PQ q,Elemtype val)
{
    if(!q)
    {
        printf("queue is NULL.\n");
    }
    else if (((q->rear+1)%INIT_QSIZE) == q->front)
    {
        printf("queue is full.\n");
    }
    else
    {
        q->pbase[q->rear] = val;
        q->rear = (q->rear+1)%INIT_QSIZE;
    }
}
Elemtype DeQueue(PQ q)
{
    Elemtype t = q->pbase[q->front];
    q->front = (q->front+1)%INIT_QSIZE;
    return t;
}
void TraverseQueue(PQ q)
{
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
        int p = q->front;
        while (p != q->rear)
        {
            printf("%d ",q->pbase[p]);
            p = (p+1)%INIT_QSIZE;
        }
        printf("\n");
    }
}
