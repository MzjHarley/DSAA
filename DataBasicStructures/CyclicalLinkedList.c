/**
 * 循环链表，顾名思义，就是在普通链表的基础上，它的尾结点不在指向为NULL，而是指向头结点。
 * 操作和普通链表相似：初始化，清空，销毁,判断为空，得到长度，得到某个位置的值，得到某个值的位置，值前驱，位置前驱，值后继，位置后继，值插入，值删除，
 * 位置插入，位置删除，遍历，颠倒，排序。大约17个操作。
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
typedef struct Node
{
    int data;
    struct Node* next;
}N,*PN;
PN initCyclicalLinkedList(PN phead);
PN destroyCyclicalLinkedList(PN phead);
void clearCyclicalLinkedList(PN phead);
bool isEmpty(PN phead);
int getLength(PN phead);
void getElem(PN phead);
int getElemPos(PN phead);
void getPrior(PN phead);
void getPost(PN phead);
bool insertCyclicalLinkedList(PN phead);
bool deleteCyclicalLinkedList(PN phead);
void reverseCyclicalLinkedList(PN phead);
void sortCyclicalLinkedList(PN phead);
void traverseCyclicalLinkedList(PN phead);
int main()
{
    printf("*********************************\n");
    printf("* 1.initCyclicalLinkedList      *\n");
    printf("* 2.destroyCyclicalLinkedList   *\n");
    printf("* 3.Empty Or Not                *\n");
    printf("* 4.insertCyclicalLinkedList    *\n");
    printf("* 5.deleteCyclicalLinkedList    *\n");
    printf("* 6.clearCyclicalLinkedList     *\n");
    printf("* 7.traverseCyclicalLinkedList  *\n");
    printf("* 8.sortCyclicalLinkedList      *\n");
    printf("* 9.getElem                     *\n");
    printf("* 10.getElemPos                 *\n");
    printf("* 11.getPrior                   *\n");
    printf("* 12.getPost                    *\n");
    printf("* 13.reverseCyclicalLinkedList  *\n");
    printf("* 14.getLength                  *\n");
    printf("*********************************\n");
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
            phead = initCyclicalLinkedList(phead); 
            break;
        case 2:
            phead = destroyCyclicalLinkedList(phead);
            break;
        case 3:
            if(isEmpty(phead))
            {
                printf("Empty.\n");
            }
            else
            {
                printf("Not Empty.\n");
            }
            break;
        case 4:
            insertCyclicalLinkedList(phead);
            break;
        case 5:
            deleteCyclicalLinkedList(phead);
            break;
        case 6:
            clearCyclicalLinkedList(phead);
            break;
        case 7:
            traverseCyclicalLinkedList(phead);
            break;
        case 8:
            sortCyclicalLinkedList(phead);
            break;
        case 9:
            getElem(phead);
            break;
        case 10:
            getElemPos(phead);
            break;
        case 11:
            getPrior(phead);
            break;
        case 12:
            getPost(phead);
            break;
        case 13:
            reverseCyclicalLinkedList(phead);
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
/**
 * 初始化：分为自定义节点初始化，和非自定义节点初始化。
 * 自定义节点初始化每一个新创造的节点的next都让它指向头结点，然后采取尾插法进行连接。
 * 自定义节点的初始化进行五步操作:1.创建头结点2.创建尾指针，永远指向尾结点3.循环创建节点并对节点进行操作4.连接节点5.返回头结点
 * 非自定义节点的初始化仅仅创建一个头结点并返回头节点。
 */ 
PN initCyclicalLinkedList(PN phead)
{
    if(phead)
    {
        phead = destroyCyclicalLinkedList(phead);
    }
    printf("1.自定义节点初始化，2.非自定义节点初始化;请输入你的选择:");
    int option;
    scanf("%d",&option);
    if(1 == option)
    {
        PN phead = (PN)malloc(sizeof(N));//创建头结点
        if(NULL == phead)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        phead->next = phead;
        PN ptail = phead;//创建尾指针，永远指向尾结点
        int num;
        printf("请输入你想要自定义的节点数:");
        scanf("%d",&num);
        int val;
        for(int i = 1; i < num+1;i++)//循环创建节点并对节点进行操作；连接节点
        {
            PN pnew = (PN)malloc(sizeof(N));
            printf("请为第%d个节点赋值:",i);
            scanf("%d",&val);
            if(NULL == pnew)
            {
                printf("Dynamic malloc failed.\n");
                phead = destroyCyclicalLinkedList(phead);
                exit(-1);
            }
            else
            {
                pnew->data = val;
                pnew->next = phead;
            }
            ptail->next = pnew;
            ptail = pnew;
        }
        return phead;//返回头结点
    }
    else if(2 == option)
    {
        PN phead = (PN)malloc(sizeof(N));
        if(NULL == phead)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        phead->next = phead;
        return phead;
    }
    else
    {
        printf("option error.\n");
        return NULL;
    }
}
/**
 * 销毁循环链表，不能先销毁头结点，如果先销毁头结点会导致最后一个节点失去指向或者在循环链表为空的情况下，为了达到目的导致free两次头结点造成内存崩溃。
 * 应该从首节点开始free，最后再free头结点。
 * 这里的销毁方式和普通链表不同，因为普通链表的尾结点没有指向。
 * 销毁操作实际上是对节点的遍历，但由于其尾结点指向导致其检验条件与普通链表不同。
 */ 
PN destroyCyclicalLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return NULL;
    }
    PN p = phead->next;
    while(p!=phead)
    {
        PN r = p->next;
        free(p);
        p = r;
    }
    free(phead);
    return NULL;
    //可以麻烦点这样写，或者调用clearCyclicalLinkedList(phead)清空链表后再free头结点，代码量会少很多并且意思一摸一样。
}
/**
 * 清空链表：结果是只有头结点并且头节点的指向是它自己。
 */ 
void clearCyclicalLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList already Empty.\n");
        return;
    }
    PN p = phead->next;
    while(p != phead)
    {
        PN r = p->next;
        free(p);
        p = r;
    }
    phead->next = phead;//这一步尤为重要，因为设置为空表头结点的指向要变成自己。
}
bool isEmpty(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return true;
    }
    if(phead->next == phead)
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
        printf("phead为NULL.\n");
        return 0;
    }
    int i = 0;
    PN p = phead->next;
    while(p != phead)
    {
        i++;
        p = p->next;
    }
    return i;
}
void traverseCyclicalLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return;
    }
    PN p = phead->next;
    while(p != phead)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
void getElem(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return;
    }
    printf("遍历为:");
    traverseCyclicalLinkedList(phead);
    int pos;
    printf("请输入你想要查找的位置:");
    scanf("%d",&pos);
    if(pos<1 || pos>getLength(phead))
    {
        printf("查找位置不存在.\n");
        return;
    }
    int i = 1;
    PN p = phead->next;
    while(i<pos)
    {
        i++;
        p = p->next;
    }
    printf("第%d个位置的元素为:%d.\n",pos,p->data);
}
/**
 * 获取元素出现的位置,遍历所有有效节点。
 */
int getElemPos(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return 0;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return 0;
    }
    printf("遍历为:");
    traverseCyclicalLinkedList(phead);
    int val;
    printf("请输入你想要寻找的值:");
    scanf("%d",&val);
    int times = 0;//记录值出现的次数
    int  i = 1;
    PN p = phead->next;
    printf("元素出现的位置依次是:");
    while(p != phead)
    {
        if(p->data == val)
        {
            printf("%d ",i);
            times++;
        }
        i++;
        p = p->next;
    }
    if(0 == times)
    {
        printf("none.\n");
    }
    else
    {
        printf("，共出现了%d次.\n",times);
    }
    return times;
}
void getPrior(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return;
    }
    printf("遍历为:");
    traverseCyclicalLinkedList(phead);
    printf("1.位置前驱，2.值前驱;请输入你的选择:");
    int option;
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想要查找前驱的位置:");
        scanf("%d",&pos);
        if(pos<2 || pos>getLength(phead))
        {
            printf("无前驱.\n");
            return;
        }
        int i = 1;
        PN p = phead->next;
        while(i<pos-1)
        {
            i++;
            p = p->next;
        }
        printf("第%d个位置的前驱是%d.\n",pos,p->data);
    }
    else if(2 == option)
    {
        int val;
        printf("请输入你想要查找前驱的值:");
        scanf("%d",&val);
        int times = 0;
        PN p = phead->next;
        printf("前驱依次为:");
        while(p!=phead && p->next!=phead)
        {
            if(p->next->data == val)
            {
                times++;
                printf("%d ",p->data);
            }
            p = p->next;
        }
        if(0 == times)
        {
            printf("none.");
        }
        printf("\n");
    }
    else
    {
        printf("option error.\n");
    }
}
void getPost(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return;
    }
    printf("遍历为:");
    traverseCyclicalLinkedList(phead);
    printf("1.位置后继，2.值后继;请输入你的选择:");
    int option;
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想要查找后继的位置:");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(phead)-1)
        {
            printf("无后继.\n");
            return;
        }
        int i = 1;
        PN p = phead->next;
        while(i<pos)
        {
            i++;
            p = p->next;
        }
        printf("第%d个位置的后继是%d.\n",pos,p->next->data);
    }
    else if(2 == option)
    {
        int val;
        printf("请输入你想要查找后继的值:");
        scanf("%d",&val);
        int times = 0;
        PN p = phead->next;
        printf("后继依次为:");
        while(p!=phead && p->next!=phead)
        {
            if(p->data == val)
            {
                times++;
                printf("%d ",p->next->data);
            }
            p = p->next;
        }
        if(0 == times)
        {
            printf("none.");
        }
        printf("\n");
    }
    else
    {
        printf("option error.\n");
    }
}
bool insertCyclicalLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return false;
    }
    printf("插入前:");
    traverseCyclicalLinkedList(phead);
    printf("1.位置插入，2.值插入;请输入你的选择:");
    int option;
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想找插入的位置:");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(phead)+1)
        {
            printf("位置错误.\n");
            return false;
        }
        int i = 0;
        PN p = phead;
        while(i < pos-1)
        {
            i++;
            p = p->next;
        }
       int val;
       printf("请为插入节点赋值:");
       scanf("%d",&val);
       PN pnew = (PN)malloc(sizeof(N));
       if(NULL == pnew)
       {
           printf("Dynamic malloc failed.\n");
           return false;
       }
       pnew->data = val;
       pnew->next = NULL;
       pnew->next = p->next;
       p->next = pnew;
       printf("插入后:");
       traverseCyclicalLinkedList(phead);
       return true;
    }
    else if(2 == option)
    {
        int val;
        printf("请输入该值:");
        scanf("%d",&val);
        int option1;
        printf("1.插入在该值前面，2.插入到该值后面;请输入你的选择:");
        scanf("%d",&option1);
        int val1;
        printf("请输入你要插入的值:");
        scanf("%d",&val1);
        int times = 0;
        if(1 == option1)
        {
            PN p = phead;
            while(p->next != phead)
            {
                if(p->next->data == val)
                {
                    times++;
                    PN pnew = (PN)malloc(sizeof(N));
                    if(NULL == pnew)
                    {
                        printf("Dynamic malloc failed.\n");
                        return false;
                    }
                    pnew->data = val1;
                    pnew->next = NULL;
                    pnew->next = p->next;
                    p->next = pnew;
                    p = pnew;
                }
                p = p->next;
            }
            if(0 == times)
            {
                printf("不存在该值.\n");
                return false;
            }
            printf("插入后:");
            traverseCyclicalLinkedList(phead);
            return true;
        }
        else if(2 == option1)
        {
            PN p = phead->next;
            while(p!=phead)
            {
                if(p->data == val)
                {
                    times++;
                    PN pnew = (PN)malloc(sizeof(N));
                    if(NULL == pnew)
                    {
                        printf("Dynamic malloc failed.\n");
                        return false;
                    }
                    pnew->data = val1;
                    pnew->next = NULL;
                    pnew->next = p->next;
                    p->next = pnew;
                    p = pnew;
                }
                p = p->next;
            }
            if(0 == times)
            {
                printf("不存在该值.\n");
                return false;
            }
            printf("插入后:");
            traverseCyclicalLinkedList(phead);
            return true;
        }
        else
        {
            printf("option1 error.\n");
            return false;
        }
    }
    else
    {
        printf("option error.\n");
        return false;
    }
}
bool deleteCyclicalLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return false;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return false;
    }
    printf("删除前:");
    traverseCyclicalLinkedList(phead);
    printf("1.位置删除，2.值删除;请输入你的选择:");
    int option;
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想找删除的位置:");
        scanf("%d",&pos);
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
            p = p->next;
        }
        PN r = p->next;
        p->next = r->next;
        free(r);
        printf("删除后:");
        traverseCyclicalLinkedList(phead);
        return true;
    }
    else if(2 == option)
    {
        int val;
        printf("请输入该值:");
        scanf("%d",&val);
        int option1;
        int times = 0;
        PN p = phead;
        while(p->next != phead)
        {
            if(p->next->data == val)
            {
                times++;
                PN r = p->next;
                p->next = r->next;
                free(r);
            }
            else
            {
                p = p->next;
            }
        }
        if(0 == times)
        {
            printf("不存在该值.\n");
            return false;
        }
        printf("删除后:");
        traverseCyclicalLinkedList(phead);
        return true;
    }
    else
    {
        printf("option error.\n");
        return false;
    }
}
void reverseCyclicalLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return;
    }
    printf("颠倒前:");
    traverseCyclicalLinkedList(phead);
    PN p = phead->next;
    PN q = phead;
    while(p != phead)
    {
        PN r = p->next;
        p->next = q;
        q= p;
        p =r;
    }
    phead->next = q;
    printf("颠倒后:");
    traverseCyclicalLinkedList(phead);
}
void sortCyclicalLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead为NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("CyclicalLinkedList is Empty.\n");
        return;
    }
    printf("排序前:");
    traverseCyclicalLinkedList(phead);
    PN pre,p;
    for(int i = 0;i < getLength(phead)-1;i++)
    {
        pre = phead;
        p = pre->next;
        while(p!=phead && p->next!=phead)
        {
            PN q = p->next;
            if(p->data > q->data)
            {
                p->next = q->next;
                q->next = p;
                pre->next = q;
            }
            pre = pre->next;
            p = pre->next;
        }
    }
    printf("排序前:");
    traverseCyclicalLinkedList(phead);
}