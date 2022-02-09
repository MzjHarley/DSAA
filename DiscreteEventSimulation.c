/**
 * 离散事件模拟银行业务。用到队列，有序链表等结构
 * 注意有序链表非降序排列
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//10~30行是事件链表，即记录事件的链表的表示及基本操作，采取的是有序链表的存储结构
typedef struct OElem
{
    int occurTime;//银行客户到达时间，即发生业务的时间
    int NType;//表示窗口，0~3分别表示特定的窗口
}OElemType;
typedef struct ONode
{
    OElemType data;
    struct ONode* Next;
}ONode,*PONode;
typedef struct OrderLinkedList
{
    PONode head;
    PONode tail;//永远指向有序链表的尾节点，操作有序链表时要特别关注此成员的指向问题
    int len;//有序链表的长度
}O,*PO;
PO InitOrderLinkedList();
bool OrderLinkedListIsEmpty(PO po);
void InsertOrderLinkedList(PO po,OElemType e,int(*compare)(OElemType,OElemType));
PONode DeleteOrderLinkedListFirstNode(PO po);

//32~50行是队列的表示及基本方法
typedef struct QElemtype
{
    int occurTime;//银行客户到达时间，即发生业务的时间
    int Duration;//银行客户办理业务所需要的时间
}QElemtype;
typedef struct QNode
{
    QElemtype data;
    struct QNode* Next;
}QNode,*PQNode;
typedef struct Queue
{
    PQNode front;
    PQNode rear;
}Q,*PQ;
PQ InitQueue();
bool QueueIsEmpty(PQ q);
void EnQueue(PQ q,QElemtype data);
QElemtype DeQueue(PQ q);

void openForDay()
{
    
}


int main()
{
    return 0;
}

PO InitOrderLinkedList()
{
    PO po = (PO)malloc(sizeof(O));
    if(!po)
    {
        printf("Dynamic Malloc failed.\n");
        exit(-1);
    }
    else
    {
        po->head = (PONode)malloc(sizeof(ONode));
        if(!po->head)
        {
            printf("Dynamic Malloc failed.\n");
            exit(-1);
        }
        else
            po->head->Next =  NULL;
        po->tail = po->head;
        po->len = 0;
    }
    return po;
}
bool OrderLinkedListIsEmpty(PO po)
{
    if(po->len)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/**
 * 删除有序链表第一个节点，并且返回该节点。
 */
PONode DeleteOrderLinkedListFirstNode(PO po)
{
    PONode p = po->head->Next;
    if(p)//有序链表不为空
    {
        po->head->Next = p->Next;
        if (!po->head->Next)
        {
            po->tail = po->head;
        }
        po->len--;
        return p;
    }
    else
    {
        return NULL;
    }
}
/**
 * 从头节点遍历有序链表，找到合适位置并且插入到其后面
 * 同时涉及到函数指针的使用
 */
void InsertOrderLinkedList(PO po, OElemType e,int(*compare)(OElemType,OElemType))
{
    PONode p = po->head;
    PONode q = p->Next;
    while (q!=NULL && compare(q->data,e)<0)//通过比较节点值的大小，找寻到合适位置的前驱节点，从而方便插入
    {
        p=q;
        q=q->Next;
    }
    PONode r = (PONode)malloc(sizeof(ONode));
    if(!r)
    {
        printf("Dynamic Malloc failed.\n");
        exit(-1);
    }
    else
    {
        r->data=e;
    }
    r->Next = q;
    p->Next = r;
    po->len++;
    if(!q)//如果插入到有序链表表尾，则要更改尾指针的指向
    {
        po->tail = r;
    }
}
PQ InitQueue()
{
    PQ q = (PQ)malloc(sizeof(Q));
    if(!q)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        q->front = q->rear = (PQNode)malloc(sizeof(QNode));
        if(!q->front)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        else
        {
            q->front->Next = NULL;
        }
    }
    return q;
}
bool QueueIsEmpty(PQ q)
{
    if(q->front == q->rear)
        return true;
    else
        return false;
}
void EnQueue(PQ q,QElemtype val)
{
    if(!q)
    {
        printf("Arguments is NULL.\n");
    }
    else
    {
        PQNode p = (PQNode)malloc(sizeof(QNode));
        if(!p)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        else
        {
            p->data = val;
            p->Next = NULL;
        }
        q->rear->Next = p;
        q->rear = p;
    }
}
QElemtype DeQueue(PQ q)
{
    PQNode p = q->front->Next;
    QElemtype t = p->data;
    q->front->Next = p->Next;
    if(q->rear == p)
    {
        q->rear = q->front;
    }
    free(p);
    return t;
}
