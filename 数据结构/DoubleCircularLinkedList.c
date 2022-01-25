/**
 * 双向循环链表的高级操作
 * 双向循环链表，顾名思义：是一个双向链表同时是一个循环链表。
 * 双向循环链表的操作:初始化，清空，销毁，判断是否为空，得到长度，得到某个位置的元素，得到某个元素的位置，位置前驱值前驱，值前驱，
 * 位置后继，值后继，位置插入，值插入，位置删除，值删除，遍历，排序，颠倒输出.大约17个操作。
 */
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
typedef struct Node
{
    struct Node* left;
    int data;
    struct Node* right;
}N,*PN;
PN initDoubleCircularLinkedList(PN phead);
PN destroyDoubleCircularLinkedList(PN phead);
void clearDoubleCircularLinkedList(PN phead);
bool isEmpty(PN phead);
int getLength(PN phead);
void getElem(PN phead);
int getElemPos(PN phead, int val);
void getPrior(PN phead);
void getPost(PN phead);
bool insertDoubleCircularLinkedList(PN phead);
bool deleteDoubleCircularLinkedList(PN phead);
void reverseTraverse(PN phead);
void sortDoubleCircularLinkedList(PN phead);
void traverseDoubleCircularLinkedList(PN phead);
int main()
{
    printf("***************************************\n");
    printf("*  1.initDoubleCircularLinkedList      *\n");
    printf("*  2.destroyDoubleCircularLinkedList   *\n");
    printf("*  3.Empty Or Not                      *\n");
    printf("*  4.insertDoubleCircularLinkedList    *\n");
    printf("*  5.deleteDoubleCircularLinkedList    *\n");
    printf("*  6.clearDoubleCircularLinkedList     *\n");
    printf("*  7.traverseDoubleCircularLinkedList  *\n");
    printf("*  8.sortDoubleCircularLinkedList      *\n");
    printf("*  9.getElem                           *\n");
    printf("* 10.getElemPos                       *\n");
    printf("* 11.getPrior                         *\n");
    printf("* 12.getPost                          *\n");
    printf("* 13.reverseTraverse                  *\n");
    printf("* 14.getLength                        *\n");
    printf("***************************************\n");
    char str;
    int num;
    int pos;
    int val;
    PN phead=NULL;;
    do
    {
        printf("Input Operand:");
        scanf("%d",&num);
        switch(num)
        {
        case 1:
            phead = initDoubleCircularLinkedList(phead); 
            break;
        case 2:
            phead = destroyDoubleCircularLinkedList(phead);
            break;
        case 3:
            if(NULL == phead)
            {
                printf("phead is NULL.\n");
            }
            else
            {
                if(isEmpty(phead))
                {
                    printf("Empty.\n");
                }
                else
                {
                    printf("Not Empty.\n");
                }
            }
            break;
        case 4:
            insertDoubleCircularLinkedList(phead);
            break;
        case 5:
            deleteDoubleCircularLinkedList(phead);
            break;
        case 6:
            clearDoubleCircularLinkedList(phead);
            break;
        case 7:
            traverseDoubleCircularLinkedList(phead);
            break;
        case 8:
            sortDoubleCircularLinkedList(phead);
            break;
        case 9:
            getElem(phead);
            break;
        case 10:
            printf("请输入你想要查询的值:");
            scanf("%d",&val);
            getElemPos(phead,val);
            break;
        case 11:
            getPrior(phead);
            break;
        case 12:
            getPost(phead);
            break;
        case 13:
            reverseTraverse(phead);
            break;
        case 14:
            printf("链表长度为:%d\n",getLength(phead));
            break;
        }
        printf("Continue Or Not(Y/N):");
        scanf(" %c",&str);
    }while(str=='Y' || str=='y');
    return 0;
}
PN initDoubleCircularLinkedList(PN phead)
{
    if(phead)
    {
        phead = destroyDoubleCircularLinkedList(phead);
    }
    int option;
    printf("1.自定义节点初始化，2.非自定义节点初始化.请输入你的选择:");
    scanf("%d",&option);
    if(1 == option)
    {
        phead = (PN)malloc(sizeof(N));
        if(NULL == phead)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        phead->left = phead->right = phead;
        PN ptail = phead;
        int num, val;
        printf("请输入你想要构造的节点数:");
        scanf("%d",&num);
        for(int i = 1;i < num+1;i++)
        {
            printf("请为第%d个节点赋值:",i);
            scanf("%d",&val);
            PN pnew =(PN)malloc(sizeof(N));
            if(NULL == phead)
            {
                printf("Dynamic malloc failed.\n");
                exit(-1);
            }
            pnew->left = NULL;
            pnew->data = val;
            pnew->right = phead; //这里不初始化为NULL，可以在连接节点时省一步

            phead->left = pnew;
            ptail->right = pnew;
            pnew->left = ptail;
            ptail = pnew;
        }
        return phead;
    }
    else if(2 == option)
    {
        phead = (PN)malloc(sizeof(N));
        if(NULL == phead)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        phead->left = phead;
        phead->right = phead;
        return phead;
    }
    else
    {
        printf("option error.\n");
        return NULL;
    }
}
PN destroyDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return NULL;
    }
    clearDoubleCircularLinkedList(phead);
    free(phead);
    return NULL;
}
void clearDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    PN p = phead->right;
    while(p != phead)
    {
        PN q = p->right;
        free(p);
        p = q;
    }
    phead->left = phead->right = phead;
}
bool isEmpty(PN phead)
{
    if(phead->right==phead && phead->left==phead)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int getLength(PN phead)
{
    if(NULL == phead)
    {
        return 0;
    }
    if(isEmpty(phead))
    {
        return 0;
    }
    int length = 0;
    PN p = phead->right;
    while(p != phead)
    {
        length++;
        p = p->right;
    }
    return length;
}
void getElem(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return;
    }
    int pos;
    printf("请输入你想要查找元素的位置:");
    scanf("%d",&pos);
    if(pos<1 || pos>getLength(phead))
    {
        printf("位置错误.\n");
        return;
    }
    int i = 1;
    PN p = phead->right;
    while(i < pos)
    {
        i++;
        p = p->right;
    }
    printf("第%d个位置的元素为%d\n",pos,p->data);
}
int getElemPos(PN phead, int val)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return 0;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return 0;
    }
    int times = 0;
    int i = 1;
    PN p = phead->right;
    printf("查找元素的位置依次为:");
    while(p != phead)
    {
        if(p->data == val)
        {
            times++;
            printf("%d ",i);
        }
        i++;
        p = p->right;
    }
    if(0 == times)
    {
        printf("none");
    }
    else
    {
        printf(",共出现%d次.",times);
    }
    printf("\n");
    return times;
}
void getPrior(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return;
    }
    int option;
    printf("1.位置前驱，2.值前驱;请输入你的选择:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想要寻找前驱的位置:");
        scanf("%d",&pos);
        if(pos<2 || pos>getLength(phead))
        {
            printf("无前驱.\n");
            return;
        }
        int i = 1;
        PN p = phead->right;
        while(i < pos)
        {
            i++;
            p = p->right;
        }
        printf("第%d个位置的前驱为%d.\n",pos,p->left->data);
    }
    else if(2 == option)
    {
        int val;
        printf("请输入你想要寻找前驱的值:");
        scanf("%d",&val);
        printf("前驱依次为:");
        int times = 0;
        PN p = phead->right->right;
        while (p != phead)
        {
            if(p->data == val)
            {
                times++;
                printf("%d ",p->left->data);
            }
            p = p->right;
        }
        if (0 == times)
        {
            printf("none.");
        }
        printf("\n");
    }
    else
    {
        printf("option error");
    }
}
void getPost(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return;
    }
    int option;
    printf("1.位置后继，2.值后继;请输入你的选择:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想要寻找后继的位置:");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(phead)-1)
        {
            printf("无后继.\n");
            return;
        }
        int i = 1;
        PN p = phead->right;
        while(i < pos)
        {
            i++;
            p = p->right;
        }
        printf("第%d个位置的前驱为%d.\n",pos,p->right->data);
    }
    else if(2 == option)
    {
        int val;
        printf("请输入你想要寻找后继的值:");
        scanf("%d",&val);
        printf("后继依次为:");
        int times = 0;
        PN p = phead->right;
        while (p!=phead && p->right!=phead)
        {
            if(p->data == val)
            {
                times++;
                printf("%d ",p->right->data);
            }
            p = p->right;
        }
        if (0 == times)
        {
            printf("none.");
        }
        printf("\n");
    }
    else
    {
        printf("option error");
    }
}
bool insertDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return false;
    }
    printf("插入前:");
    traverseDoubleCircularLinkedList(phead);
    int option;
    printf("1.位置插入，2.值插入;请输入你的选择:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想要插入的位置:");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(phead)+1)
        {
            printf("位置错误.\n");
            return false;
        }
        int val;
        printf("请输入你想要插入的值:");
        scanf("%d",&val);
        int i = 0;
        PN p = phead;
        while(i < pos-1)
        {
            i++;
            p = p->right;
        }
        PN pnew = (PN)malloc(sizeof(N));
        if(NULL == pnew)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        pnew->left = pnew->right = NULL;
        pnew->data = val;
        
        pnew->right = p->right;
        pnew->left = p;
        p->right->left = pnew;
        p->right = pnew;
        printf("插入后:");
        traverseDoubleCircularLinkedList(phead);
        return true;
    }
    else if(2 == option)
    {
        int val;
        printf("请输入该值:");
        scanf("%d",&val);
        if(0 == getElemPos(phead,val))
        {
            printf("不存在该值.\n");
            return false;
        }
        int option2;
        printf("1.插入在该值前面，2.插入在该值后面;请输入你的选择:");
        scanf("%d",&option2);
        int val1;
        printf("请输入你要插入的值:");
        scanf("%d",&val1);
        if(1 == option2)
        {
            int times = 0;
            PN p = phead;
            while(p->right != phead)
            {
                if(p->right->data == val)
                {
                    times++;
                    PN pnew = (PN)malloc(sizeof(N));
                    if(NULL == pnew)
                    {
                        printf("Dynamic malloc failed.\n");
                        exit(-1);
                    }
                    pnew->left = pnew->right = NULL;
                    pnew->data = val1;

                    pnew->right = p->right;
                    pnew->left = p;
                    p->right->left = pnew;
                    p->right = pnew;
                    p = pnew;
                }
                p=p->right;
            }
            if(0 == times)
            {
                printf("不存在该值.\n");
                return false;
            }
            printf("插入后:");
            traverseDoubleCircularLinkedList(phead);
            return true;
        }
        else if(2 == option2)
        {
            int times = 0;
            PN p = phead->right;
            while(p != phead)
            {
                if(p->data == val)
                {
                    times++;
                    PN pnew = (PN)malloc(sizeof(N));
                    if(NULL == pnew)
                    {
                        printf("Dynamic malloc failed.\n");
                        exit(-1);
                    }
                    pnew->left = pnew->right = NULL;
                    pnew->data = val1;

                    pnew->right = p->right;
                    pnew->left = p;
                    p->right->left = pnew;
                    p->right = pnew;
                    p = pnew;
                }
                p = p->right;
            }
            if(0 == times)
            {
                printf("不存在该值.\n");
                return false;
            }
            printf("插入后:");
            traverseDoubleCircularLinkedList(phead);
            return true;
        }
        else
        {
            printf("option error.\n");
            return false;
        }
    }
    else
    {
        printf("option error");
        return false;
    }
}
bool deleteDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return false;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return false;
    }
    printf("删除前:");
    traverseDoubleCircularLinkedList(phead);
    int option;
    printf("1.位置删除，2.值删除;请输入你的选择:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想要删除的位置:");
        scanf("%d",&pos);
        int val;
        if(pos<1 || pos>getLength(phead))
        {
            printf("位置错误.\n");
            return false;
        }
        int i = 0;
        PN p = phead;
        while(i < pos-1)
        {
            i++;
            p = p->right;
        }
        PN q = p->right;
        p->right = q->right;
        q->right->left = p;
        free(q);
        printf("删除后:");
        traverseDoubleCircularLinkedList(phead);
        return true;
    }
    else if(2 == option)
    {
        int val;
        printf("请输入该值:");
        scanf("%d",&val);
        int times = 0;
        PN p = phead;
        while(p->right != phead)
        {
            if(p->right->data == val)
            {
                times++;
                PN q = p->right;
                p->right = q->right;
                q->right->left = p;
                free(q);
            }
            else
            {
                p = p->right;
            }
        }
        if(0 == times)
        {
            printf("不存在该值.\n");
            return false;
        }
        printf("删除后:");
        traverseDoubleCircularLinkedList(phead);
        return true;
    }
    else
    {
        printf("option error.\n");
        return false;
    }
}
void traverseDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return;
    }
    PN p = phead->right;
    while(p != phead)
    {
        printf("%d ",p->data);
        p = p->right;
    }
    printf("\n");
}
void reverseTraverse(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return;
    }
    PN p = phead->left;
    while(p != phead)
    {
        printf("%d ",p->data);
        p = p->left;
    }
    printf("\n");
}
void sortDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return;
    }
    PN pre,p;
    for(int i = 0;i < getLength(phead)-1;i++)
    {
        pre = phead;
        p = pre->right;
        while(p!=phead && p->right!=phead)
        {
            PN q = p->right;
            if(p->data > q->data)
            {
                pre->right = q;
                q->left = pre;
                p->left = q;
                p->right = q->right;
                q->right->left = p;
                q->right = p;
            }
            pre = pre->right;
            p = pre->right;
        }
    }
}