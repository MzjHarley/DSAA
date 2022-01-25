/**
 * 这个程序将进行静态链表的创建和高级操作。
 * 静态链表是用顺序存储结构实现的链式存储，由两条链表共用，一条是备用链表（存放空闲节点），一条是链表。
 * 静态链表有两个头结点，一个是备用链表的头结点下标为0，一条是链表头结点下标为listsize-1
 * 静态链表高级操作：初始化，清空，销毁，分配，释放，查找元素位置，查找某个位置元素，值删除，位置删除，位置插入，值前驱，位置前驱，
 * 值后继，位置后继，打印判断为空，链表长度。共16个操作，其实我还可以把排序和颠倒操作写上，但是没必要。我简单提一下，排序使用冒泡排序进行操作。
 * 颠倒操作可以用链表的颠倒操作，原理完全一样，只是遍历的方式不一样罢了。
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#define INIT_LIST_SIZE 20
typedef struct StaticList
{
    int data;
    int next;//存放下一个元素的下标
}S,*PS;
PS initStaticList(PS ps);
void clearStaticList(PS ps);
PS destroyStaticList(PS ps);
void Free(PS ps, int index);
void getElem(PS ps);
int getElemPos(PS ps, int val);
void getPrior(PS ps);
void getPost(PS ps);
bool isEmpty(PS ps);
bool insertStaticList(PS ps);
bool deleteStaticList(PS ps);
void printStaticList(PS ps);
int Malloc(PS ps);
int getLength(PS ps);
int main()
{
    printf("*************************\n");
    printf("* 1.initStaticList      *\n");
    printf("* 2.destroyStaticList   *\n");
    printf("* 3.Empty Or Not        *\n");
    printf("* 4.insertStaticList    *\n");
    printf("* 5.deleteStaticList    *\n");
    printf("* 6.clearStaticList     *\n");
    printf("* 7.printStaticList     *\n");
    printf("* 8.getElem             *\n");
    printf("* 9.getElemPos          *\n");
    printf("* 10.getPrior           *\n");
    printf("* 11.getPost            *\n");
    printf("* 12.getLength          *\n");
    printf("*************************\n");
    char str;
    int num;
    int val;
    PS ps = NULL;
    do
    {
        printf("Input Operand:");
        scanf("%d",&num);
        switch(num)
        {
        case 1:
            ps = initStaticList(ps); 
            break;
        case 2:
            ps = destroyStaticList(ps);
            break;
        case 3:
            if(isEmpty(ps))
            {
                printf("Empty.\n");
            }
            else
            {
                printf("Not Empty.\n");
            }
            break;
        case 4:
            insertStaticList(ps);
            break;
        case 5:
            deleteStaticList(ps);
            break;
        case 6:
            clearStaticList(ps);
            break;
        case 7:
            printStaticList(ps);
            break;
        case 8:
            getElem(ps);
            break;
        case 9:
            printf("请输入你想要寻找的值:");
            scanf("%d",&val);
            getElemPos(ps, val);
            break;
        case 10:
            getPrior(ps);
            break;
        case 11:
            getPost(ps);
            break;
        case 12:
            printf("长度为:%d\n",getLength(ps));
            break;
        }
        printf("Continue Or Not(Y/N):");
        scanf(" %c",&str);
    }while(str=='Y' || str=='y');
    return 0;
}
/**
 * 初始化静态链表：
 * 非自定义初始化状态是：有两个头节点下标分别为0和INIT_LIST_SIZE-1，分别是备用链表和链表的头结点，链表为空，备用链表为满。
 * 自定义初始化的状态：有两个头节点下标分别为0和INIT_LIST_SIZE-1，分别是备用链表和链表的头结点，含有自定义个有效节点即链表不为空。
 * 注意num值不能小于0，大于INIT_LIST_SIZE-2，因为静态链表有两个头结点不存放有效数据所以有INIT_LIST_SIZE-2个有效节点。
 */
PS initStaticList(PS ps)
{
    printf("初始化前:");
    printStaticList(ps);
    int option;
    printf("1.自定义链表的初始化，2.非自定义初始化；请输入你的选择：");
    scanf("%d",&option);
    if(1 == option)
    {
        ps = (PS)malloc(sizeof(S)*INIT_LIST_SIZE);
        if(NULL == ps)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        int num, val;
        printf("请输入自定义链表初始化数目：");
        scanf("%d",&num);
        if(num<0 || num>INIT_LIST_SIZE-2)
        {
            printf("数目错误.\n");
            return NULL;
        }
        //链表带有自定义节点初始化
        ps[INIT_LIST_SIZE-1].next = INIT_LIST_SIZE-2;
        for(int i = 2; i < num+1;i++)
        {
            printf("请为第%d节点赋值:",i-1);
            scanf("%d",&val);
            ps[INIT_LIST_SIZE-i].next = INIT_LIST_SIZE-i-1;
            ps[INIT_LIST_SIZE-i].data = val;
        }
        printf("请为第%d节点赋值:",num);
        scanf("%d",&val);
        ps[INIT_LIST_SIZE-1-num].next = 0;
        ps[INIT_LIST_SIZE-1-num].data = val;
        //相应的备用链表初始化
        for(int i = 0;i < INIT_LIST_SIZE-2-num;i++)
        {
            ps[i].next = i+1;
        }
        ps[INIT_LIST_SIZE-2-num].next= 0;
        printf("初始化后:");
        printStaticList(ps);
        return ps;
    }
    else if(2 == option)
    {
        ps = (PS)malloc(sizeof(S)*INIT_LIST_SIZE);
        if(NULL == ps)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps[INIT_LIST_SIZE-1].next = 0;//使链表为空
        //下面使备用链表为满
        for(int i = 0;i < INIT_LIST_SIZE-2;i++)
        {
            ps[i].next = i+1;
        }
        ps[INIT_LIST_SIZE-2].next = 0;
        printf("初始化后:");
        printStaticList(ps);
        return ps;
    }
    else
    {
        printf("option error.\n");
        return NULL;
    }
    
}
/**
 * 清空链表：使其链表为空；
 */
void clearStaticList(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return;
    }
    if(isEmpty(ps))
    {
        printf("静态链表已为空.\n");
        return;
    }
    printf("清空前:");
    printStaticList(ps);
    int i = ps[INIT_LIST_SIZE-1].next;//从第一个有效节点开始
    while(ps[i].next)
    {
        i = ps[i].next;
    }
    ps[i].next = ps[0].next;
    ps[0].next = ps[INIT_LIST_SIZE-1].next;
    ps[INIT_LIST_SIZE-1].next = 0;
    printf("清空后:");
    printStaticList(ps);
}
PS destroyStaticList(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return NULL;
    }
    free(ps);
    return NULL;
}
/**
 * 释放下标为index的节点，其结果是使其成为备用链表的第一个节点。
 * 这个函数用于其他函数中以达到删除的目的。
 * 不需要对index进行范围检验，因为我们不会单独使用它
 */
void Free(PS ps, int index)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return;
    }
    ps[index].next = ps[0].next;
    ps[0].next = index;
}
void getElem(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return;
    }
    if(isEmpty(ps))
    {
        printf("静态链表为空.\n");
        return;
    }
    printStaticList(ps);
    int pos;
    printf("请输入你要查找的位置:");
    scanf("%d",&pos);
    if(pos<1 || pos>getLength(ps))
    {
        printf("位置错误.\n");
        return;
    }
    int j;
    for(int i = 0;i < pos;i++)
    {
        j = ps[INIT_LIST_SIZE-1-i].next;
    }
    printf("第%d个位置的元素为:%d.\n",pos,ps[j].data);
}
int getElemPos(PS ps, int val)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return 0;
    }
    if(isEmpty(ps))
    {
        printf("静态链表为空.\n");
        return 0;
    }
    printStaticList(ps);
    int times = 0;
    int i = ps[INIT_LIST_SIZE-1].next;
    printf("你想要寻找的值的下标依次为:");
    while(i)
    {
        if(ps[i].data == val)
        {
            printf("%d ",i);
            times++;
        }
        i = ps[i].next;
    }
    if(0 == times)
    {
        printf("none.\n");
    }
    else
    {
        printf("，共出现%d次.\n",times);
    }
    return times;
}
void getPrior(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return;
    }
    if(isEmpty(ps))
    {
        printf("静态链表为空.\n");
        return;
    }
    printStaticList(ps);
    int option;
    printf("1.位置前驱，2.值前驱；请输入你的选择：");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你要查找前驱的位置：");
        scanf("%d",&pos);
        if(pos<2 || pos>getLength(ps))
        {
            printf("无前驱.\n");
            return;
        }
        int i = 1;
        int j = ps[INIT_LIST_SIZE-1].next;
        while(i < pos-1)
        {
            j = ps[j].next;
            i++;
        }
        printf("位置%d的前驱为:%d.\n",pos,ps[j].data);
    }
    else if(2 == option)
    {
        int val,times = 0;
        printf("请输入你想要查找前驱的值:");
        scanf("%d",&val);
        printf("前驱依次为:");
        int i = ps[INIT_LIST_SIZE-1].next;
        while(i && ps[i].next)
        {
            if(ps[ps[i].next].data == val)
            {
                printf("%d ",ps[i].data);
                times++;
            }
            i = ps[i].next;
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
void getPost(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return;
    }
    if(isEmpty(ps))
    {
        printf("静态链表为空.\n");
        return;
    }
    printStaticList(ps);
    int option;
    printf("1.位置后继，2.值后继；请输入你的选择：");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你要查找后继的位置：");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(ps)-1)
        {
            printf("无后继.\n");
            return;
        }
        int i = 1;
        int j = ps[INIT_LIST_SIZE-1].next;
        while(i < pos)
        {
            j = ps[j].next;
            i++;
        }
        printf("位置%d的后继为:%d.\n",pos,ps[ps[j].next].data);
    }
    else if(2 == option)
    {
        int val,times = 0;
        printf("请输入你想要查找后继的值:");
        scanf("%d",&val);
        printf("后继依次为:");
        int i = ps[INIT_LIST_SIZE-1].next;
        while(i && ps[i].next)
        {
            if(ps[i].data == val)
            {
                printf("%d ",ps[ps[i].next].data);
                times++;
            }
            i = ps[i].next;
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
bool isEmpty(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return true;
    }
    if(0 == ps[INIT_LIST_SIZE-1].next)
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
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return 0;
    }
    int i = ps[INIT_LIST_SIZE-1].next;
    int times = 0;
    while(i)
    {
        times++;
        i = ps[i].next;
    }
    return times;
}
/**
 * 分配一个节点，并返回其下标，其结果是从备用链表拿走第一个节点
 * 这个函数用于其他函数中以达到插入的目的，我们不会单独使用它
 */ 
int Malloc(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return 0;
    }
    int i = ps[0].next;
    if(i)//判断一下可以少执行一步，理论上更快了
    {
        ps [0].next = ps[i].next;
    }
    return i;
}
void printStaticList(PS ps)
{
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return;
    }
    if(isEmpty(ps))
    {
        printf("静态链表为空.\n");
        return;
    }
    printf("链表为{下标:元素}:");
    int i = ps[INIT_LIST_SIZE-1].next;
    while(i)
    {
        printf("{%d:%d} ",i,ps[i].data);
        i = ps[i].next;
    }
    printf("备用链表{下标}:");
    if(ps[0].next == 0)
    {
        printf("none.\n");
        return;
    }
    int j = ps[0].next;
    while(j)
    {
        printf("{%d} ",j);
        j = ps[j].next;
    }
    printf("\n");
}
bool insertStaticList(PS ps)
{
    printf("插入前:");
    printStaticList(ps);
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return false;
    }
    if(getLength(ps) == INIT_LIST_SIZE-2)
    {
        printf("静态链表已满.\n");
        return false;
    }
    int pos;
    printf("请输入你想插入的位置:");
    scanf("%d",&pos);
    if(pos<1 || pos>getLength(ps)+1)
    {
        printf("位置错误.\n");
        return false;
    }
    int i = INIT_LIST_SIZE-1;
    int j = 0;
    while(j < pos-1)
    {
        j++;
        i = ps[i].next;
    }
    int k = Malloc(ps);
    int val;
    printf("请为插入节点赋值:");
    scanf("%d",&val);
    ps[k].data = val;
    ps[k].next = ps[i].next;
    ps[i].next = k;
    printf("插入后:");
    printStaticList(ps);
    return true;
}
bool deleteStaticList(PS ps)
{
    printf("删除前:");
    printStaticList(ps);
    if(NULL == ps)
    {
        printf("ps为NULL.\n");
        return false;
    }
    if(isEmpty(ps))
    {
        printf("静态链表为空.\n");
        return false;
    }
    int option;
    printf("1.位置删除，2.值删除；请输入你的选择：");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("请输入你想删除的位置:");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(ps))
        {
            printf("位置错误.\n");
            return false;
        }
        int i = INIT_LIST_SIZE-1;
        int j = 0;
        while(j < pos-1)
        {
            j++;
            i = ps[i].next;
        }
        
        int k = ps[ps[i].next].next;
        Free(ps,ps[i].next);
        ps[i].next = k;
        printf("删除后:");
        printStaticList(ps);
        return true;
    }
    else if(2 == option)
    {
        int val;
        printf("请输入你想要删除的值:");
        scanf("%d",&val);
        int i = INIT_LIST_SIZE-1;
        int j = 0;
        while(i && ps[i].next)
        {
            int k = ps[i].next;
            if(ps[k].data == val)
            {
                int r = ps[k].next;
                Free(ps,k);
                ps[i].next = r;
            }
            i = ps[i].next;
        }
        printf("删除后:");
        printStaticList(ps);
        return true;
    }
    else
    {
        printf("option error.\n");
        return false;
    }
}