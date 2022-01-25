/**
 * @author OMNSP
 * @aim 简单链式存储结构的创建和遍历
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct LinkedList{
    int data;
    struct LinkedList* Next;
}L,*PL;
PL ConstructLinkedList();
void TraverseLinkedList(PL Phead);
PL FreeLinkedList(PL Phead);
int main()
{
    PL Phead = ConstructLinkedList();
    TraverseLinkedList(Phead);
    Phead = FreeLinkedList(Phead);
    return 0;
}
PL ConstructLinkedList()
{
    PL Phead =(PL)malloc(sizeof(L));
    if (NULL == Phead)
    {
        printf("Dynamic memory allocation failed.\n");
        exit(-1);
    }
    else
    {
        Phead->Next = NULL;
        Phead->data = 0;
    }
    PL Ptail = Phead;
    int len = 0;
    printf("请输入你想要构造的节点数:");
    scanf("%d",&len);
    int val = 0;
    for(int i = 0; i < len;i++)
    {
        printf("请为第%d个节点赋值：",i+1);
        scanf("%d",&val);
        PL pnew = (PL)malloc(sizeof(L));
        if(NULL == pnew)
        {
            printf("Dynamic memory allocation failed.\n");
            exit(-1);
        }
        else
        {
            pnew->data = val;
            pnew->Next = NULL;
        }
        Ptail->Next = pnew;
        Ptail = pnew;
    }
    return Phead;
}
void TraverseLinkedList(PL Phead)
{
    PL P = Phead->Next;
    printf("输出节点值为");
    while(P)
    {
        printf("%d ",P->data);
        P=P->Next;
    }
    printf("\n");
}
PL FreeLinkedList(PL Phead)
{
    PL P = Phead;
    PL Q = NULL;
    while(P)
    {
        Q = P->Next;
        free(P);
        P=Q;
    }
    return NULL;
}