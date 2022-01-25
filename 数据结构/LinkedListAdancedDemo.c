/**
 * 本程序将执行线性表的链式实现和操作；
 * 构建初始链表，销毁链表，设置为空链表，判断链表是否为空，取得链表长度，找到某个位置的值，定位某个值的位置并找到某个值出现了几次
 * 向指定位置插入某个值，向某个值后面或前面插入某个值，删除某个位置的值，删除某个值，对链表进行排序，遍历链表，找某个值或某个位置的前驱，
 * 找某个值或某个位置的后继，链表的颠倒.一共大约16个操作.
 * 链式线性存储结构优点：空间无限制，插入删除效率高;缺点：查找元素效率低、存储速度慢;
 */
 #include<stdio.h>
 #include<stdlib.h>
 #include<malloc.h>
 #include<stdbool.h>
 typedef struct Lnode
{
    int data;
    struct Lnode * Next;
}L,*PL;
PL initLinkedList();//内含2个操作
PL destroyLinkedList(PL phead);
void clearLinkedList(PL phead);
bool isEmpty(PL phead);
int getLength(PL phead);
void getElem(PL phead,int i);
int getElemPos(PL phead,int val);
bool insertLinkedList(PL phead);//内含2个操作
bool deleteLinkedList(PL phead);//内含2个操作
void sortLinkedList(PL phead);
void traverse(PL phead);
void getPrior(PL phead);//内含2个操作
void getPost(PL phead);//内含2个操作
void reverseLinkedList(PL phead);
int main()
{
    printf("*************************\n");
    printf("* 1.initLinkedList      *\n");
    printf("* 2.destroyLinkedList   *\n");
    printf("* 3.Empty Or Not        *\n");
    printf("* 4.insertLinkedList    *\n");
    printf("* 5.deleteLinkedList    *\n");
    printf("* 6.clearLinkedList     *\n");
    printf("* 7.traverse            *\n");
    printf("* 8.sortLinkedList      *\n");
    printf("* 9.getElem             *\n");
    printf("* 10.getElemPos         *\n");
    printf("* 11.getPrior           *\n");
    printf("* 12.getPost            *\n");
    printf("* 13.reverseLinkedList  *\n");
    printf("* 14.getLength          *\n");
    printf("*************************\n");
    char str;
    int num;
    int pos;
    int val;
    PL phead=NULL;;
    do
    {
        printf("Input Operand:");
        scanf("%d",&num);
        switch(num)
        {
        case 1:
            phead =initLinkedList(); 
            break;
        case 2:
            phead = destroyLinkedList(phead);
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
            insertLinkedList(phead);
            break;
        case 5:
            deleteLinkedList(phead);
            break;
        case 6:
            clearLinkedList(phead);
            break;
        case 7:
            traverse(phead);
            break;
        case 8:
            sortLinkedList(phead);
            break;
        case 9:
            printf("请输入你想要寻找的位置:");
            scanf("%d",&pos);
            getElem(phead, pos);
            break;
        case 10:
            printf("请输入你想要寻找的值:");
            scanf("%d",&val);
            getElemPos(phead, val);
            break;
        case 11:
            getPrior(phead);
            break;
        case 12:
            getPost(phead);
            break;
        case 13:
            reverseLinkedList(phead);
            break;
        case 14:
            printf("链表长度为:%d\n",getLength(phead));
            break;
        }
        printf("Continue Or Not(Y/N):");
        scanf(" %c",&str);
    }while(str=='Y');
    return 0; 
 }
/**
  * 初始化操作，带有有效节点的初始化，和不带有有效节点的初始化。 
  */ 
PL initLinkedList()
{
     int option;
     printf("1.自定义节点数目的初始化，2.非自定义节点数目的初始化，请输入你的选择:");
     scanf("%d",&option);
     if(1 == option)
     {
         PL phead = (PL)malloc(sizeof(L));
         if(NULL == phead)
         {
             printf("Dynamic Malloc Failed.\n ");
             exit(-1);
         }
         else
         {
            phead->Next = NULL;
            phead->data = 0;
         }
         PL ptail = phead;//定义一个尾指针永远指向尾结点
         int num = 0,val = 0;
         printf("请输入你自定义节点的数目：");
         scanf("%d",&num);
         for(int i = 0;i < num;i++)
         {
             printf("请为第%d个节点赋值:",i+1);
             scanf("%d",&val);
             PL pnew = (PL)malloc(sizeof(L));
             if(NULL == pnew)
             {
                printf("Dynamic Malloc Failed.\n ");
                exit(-1);
             }
             else
             {
                pnew->Next = NULL;
                pnew->data = val;
            }
            ptail->Next = pnew;
            ptail = pnew;
         }
         return phead;//返回头结点
     }
     else if(2 == option)
     {
         PL phead = (PL)malloc(sizeof(L));
         if(NULL == phead)
         {
             printf("Dynamic Malloc Failed.\n ");
             exit(-1);
         }
         else
         {
            phead->Next = NULL;
            phead->data = 0;
         }
         return phead;
     }
     else
     {
         printf("操作数错误\n");
         return NULL;
     }
 }
PL destroyLinkedList(PL phead)//销毁链表，返回NULL;
{
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
        return NULL;
    }
    else
    {
        PL P = phead;
        PL Q = NULL;
        while(P)
        {
            Q = P->Next;//保存待销毁节点的下一个节点地址
            free(P);//销毁待销毁节点
            P = Q;//p向后移动
        }
        return NULL;
    }
}
void clearLinkedList(PL phead)//清空链表，结果使其仅包含头结点
{
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
    }
    else
    {
        phead->Next = destroyLinkedList(phead->Next);//调用函数销毁头结点之后的节点
    }
}
bool isEmpty(PL phead)//判断链表是否为空
{
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
        return true;
    }
    else
    {
        if(NULL == phead->Next)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
int getLength(PL phead)//得到链表的长度，返回长度值
{
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
        return 0;
    }
    else
    {
        int i = 0;
        PL p = phead->Next;
        while(p)
        {
            i++;
            p=p->Next;
        }
        return i;
    }
}
void traverse(PL phead)//遍历链表的值
{
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
    }
    else
    {
        if(isEmpty(phead))
        {
            printf("链表为空\n");
        }
        else
        {
            PL p = phead->Next;
            while(p)
            {
                printf("%d ",p->data);
                p=p->Next;
            }
            printf("\n");
        }
    }
}
void getElem(PL phead, int i) //得到某个位置的元素
{
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
    }
    else if(isEmpty(phead))
    {
        return;
    }
    else if(i<1 || i>getLength(phead))
    {
        printf("The value of i is error.\n");
    }
    else
    {
        int j = 0;
        PL p = phead;
        while(p && j<i)
        {
            j++;
            p=p->Next;
        }
        printf("第%d个位置的值为:%d\n",i,p->data);
    }
}
int getElemPos(PL phead,int val)//得到某个元素的位置，遍历链表返回元素出现的次数
{
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
        return 0;
    }
    else if(isEmpty(phead))
    {
        return 0;
    }
    else
    {
        int times = 0;
        int i = 1;
        PL p = phead->Next;//从首节点开始，因为首节点是第一个有效节点。
        printf("出现位置依次为:"); //采取遍历链表的方式求得值出现的次数。
        while(p)
        {
            if(p->data == val)
            {
                times++;
                printf("%d ",i);
            }   
            i++;
            p=p->Next;
        }
        printf(",共出现%d次.\n",times);
        return times;
    }
}
/**
 * 对节点进行插入的算法，分为两个操作，一个在位置插入，一个在值插入
 * 位置插入操作的核心在于找到前驱。
 * 值插入到前面时有两种算法可按位置找到前驱，也可直接找到前驱
 * 值插入到后面时，直接遍历找到值节点即可。
 * 值插入时可结合getElemPos操作插入到相同的特定次序的值后面
 */ 
bool insertLinkedList(PL phead)
{
    printf("操作前:");
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
        return false;
    }
    else
    {
        int option;
        printf("1.根据位置插入，2.根据值插入，请输入你的选择:");
        scanf("%d",&option);
        if(1 == option)
        {
            int pos = 0;
            printf("请输入你要插入的位置:");
            scanf("%d",&pos);
            if(pos<1 || pos>getLength(phead)+1)//按位置执行插入操作可以插入到头结点的后面和尾结点的后面，插入位置不能小于1大于链表长度+1
            {
                return false;
            }
            else
            {
                int j = 0;
                PL p = phead;
                while(p && j<pos-1)
                {
                    j++;
                    p=p->Next;
                }
                int val = 0;
                printf("请为插入节点赋值:");
                scanf("%d",&val);
                PL pnew = (PL)malloc(sizeof(L));
                if(NULL == pnew)
                {
                    printf("Dynamic Malloc Failed.\n ");
                    exit(-1);
                }
                else
                {
                    pnew->Next = p->Next;
                    pnew->data = val;
                    p->Next = pnew;
                }
                printf("操作后:");
                traverse(phead);
                return true;
            }
        }
        else if(2 == option)
        {
            int option2 = 0;
            printf("请输入你要插入到该值1.前面 or 2.后面:");
            scanf("%d",&option2);
            int val1;
            printf("请输入该值:");
            scanf("%d",&val1);
            int val2;
            printf("请输入要插入的值:");
            scanf("%d",&val2);
            if(1 == option2)
            {
                PL p = phead->Next;
                int j = 1;
                while(p)
                {
                    if(p->data == val1)
                    {
                      //421 ~ 427行是按照位置寻找值的前驱。
                      int i = 0;
                      PL q = phead;
                      while(q && i<j-1)
                      {
                          i++;
                          q = q->Next;
                      }
                      PL pnew = (PL)malloc(sizeof(L));
                      if(NULL == pnew)
                      {
                         printf("Dynamic Malloc Failed.\n ");
                         exit(-1);
                      }
                      else
                      {
                        pnew->Next = q->Next;
                        pnew->data = val2;
                        q->Next = pnew;
                      }
                      j++;
                    }
                    j++;
                    p = p->Next;
                }
                printf("操作后:");
                traverse(phead);
                return true;
            }
            else if(2 == option2)
            {
                PL p = phead->Next;
                while(p)
                {
                    if(p->data == val1)
                    {
                       PL pnew = (PL)malloc(sizeof(L));
                       if(NULL == pnew)
                       {
                         printf("Dynamic Malloc Failed.\n ");
                         exit(-1);
                       }
                       else
                       {
                        pnew->Next = p->Next;
                        pnew->data = val2;
                        p->Next = pnew;
                        p = pnew;
                       }
                    }
                    p = p->Next;
                }
                printf("操作后:");
                traverse(phead);
                return true;
            }
            else
            {
                printf("操作数错误\n");
                return false;  
            } 
        }
        else
        {
            printf("操作数错误\n");
            return false;
        }
    } 
}
/**
 * 对节点进行删除的算法，分为两个操作，一个在位置删除，一个在值删除
 * 位置删除操作的核心在于找到前驱。
 * 值删除时，遍历链表找到值的位置，求取其前驱。
 * 值删除时可结合getElemPos操作删除到相同的特定次序的值
 */
bool deleteLinkedList(PL phead)
{
    printf("操作前:");
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
        return false;
    }
    else if(isEmpty(phead))
    {
        return false;
    }
    else
    {
        int option;
        printf("1.根据位置删除，2.根据值删除，请输入你的选择:");
        scanf("%d",&option);
        if(1 == option)
        {
            int pos = 0;
            printf("请输入你要删除的位置:");
            scanf("%d",&pos);
            if(pos<1 || pos>getLength(phead))
            {
                return false;
            }
            else
            {
                int j = 0;
                PL p = phead;
                while(p->Next && j<pos-1)
                {
                    j++;
                    p=p->Next;
                }
                PL q = p->Next;
                p->Next = q->Next;
                free(q);
                printf("操作后:");
                traverse(phead);
                return true;
            }
        }
        else if(2 == option)
        {
            int val1;
            printf("请输入该值:");
            scanf("%d",&val1);
            PL p = phead->Next;
            int j = 1;
            while(p)
            {
                PL r = p->Next;
                if(p->data == val1)
                {
                    int i = 0;
                    PL q = phead;
                    while(q->Next && i<j-1)
                    {
                        i++;
                        q = q->Next;
                    }
                    q->Next = p->Next;
                    free(p);
                }
                else
                {
                    j++; 
                }
                p = r;
            }
            printf("操作后:");
            traverse(phead);
            return true;
        }
        else
        {
            printf("操作数错误\n");
            return false;
        }
    } 
}
/**
 * 求前驱分为两种：根据位置求前驱，根据值求前驱
 */ 
void getPrior(PL phead)
{
    printf("链表:");
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
    }
    else if(isEmpty(phead))
    {
        return;
    }
    else
    {
        int option;
        printf("1.根据位置求前驱，2.根据值求前驱，请输入你的选择:");
        scanf("%d",&option);
        if(1 == option)
        {
            int pos;
            printf("请输入你要求前驱的位置:");
            scanf("%d",&pos);
            if(pos<2 || pos>getLength(phead))
            {
                printf("无前驱\n");
            }
            else
            {
                int i = 0;
                PL p = phead;
                while(p && i<pos-1)
                {
                    i++;
                    p = p->Next;
                }
                printf("位置%d的前驱为%d\n.",pos,p->data);
            }
        }
        else if(2 == option)
        {
            int val;
            printf("请输入你要求前驱的值:");
            scanf("%d",&val);
            int times = 0;
            int j = 2;
            PL q = phead->Next->Next;//首节点无前驱，故从首节点的下一个节点开始
            printf("前驱依次为:");
            while(q)
            {
                if(q->data ==  val)
                {
                    times++;
                    int i = 0;
                    PL p = phead;
                    while(p && i<j-1)
                    {
                        i++;
                        p = p->Next;
                    }
                    printf("%d ",p->data);
                }
                j++;
                q = q->Next;
            }
            if(0 == times)
            {
                printf("none");
            }
            printf("\n");
        }
        else
        {
            printf("操作数错误\n");
        }
    }
}
/**
 * 这是得到后继的算法，分两种操作一种是按照位置求后继，一种是按照值求后继。 
 */
void getPost(PL phead)
{
    printf("链表:");
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
    }
    else if(isEmpty(phead))
    {
        return;
    }
    else
    {
        int option;
        printf("1.根据位置求后继，2.根据值求后继，请输入你的选择:");
        scanf("%d",&option);
        if(1 == option)
        {
            int pos;
            printf("请输入你要求后继的位置:");
            scanf("%d",&pos);
            if(pos<1 || pos>getLength(phead)-1)//按位置求后继时位置应该不大于1，同时小于链表的长度，因为尾结点没有后继。
            {
                printf("无后继\n");
            }
            else
            {
                int i = 0;
                PL p = phead;
                while(p && i<pos) //p经过循环后得到的是该位置的节点，
                {
                    i++;
                    p = p->Next;
                }
                if(p->Next)
                {
                    printf("位置%d的后继为%d\n.",pos,p->Next->data);
                }
                else
                {
                    printf("位置%d无后继\n.",pos);
                }
            }
        }
        else if(2 == option)
        {
            int val;
            printf("请输入你要求后继的值:");
            scanf("%d",&val);
            int times = 0;
            PL q = phead->Next;
            printf("后继依次为:");
            while(q)
            {
                if(q->data ==  val)
                {
                    if(q->Next)
                    {
                        printf("%d ",q->Next->data);
                        times++;
                    }
                }
                q = q->Next;
            }
            if(0 == times)
            {
                printf("none");
            }
            printf("\n");
        }
        else
        {
            printf("操作数错误\n");
        }
    }
}
/**
 * 这是链表的冒泡排序算法，依次确立一个最大值
 * 经过Length-1次循环，每次循环从头开始并确定一个最大值
 */
void sortLinkedList(PL phead)
{
    printf("操作前:");
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
    }
    else if(isEmpty(phead))
    {
        return;
    }
    else
    {
        PL pre,p,q;
        for(int i=0;i<getLength(phead)-1;i++)
        {
            pre=phead;
            p=pre->Next;
            while(p && p->Next)
            {
                q=p->Next;
                if(p->data > q->data)
                {
                    pre->Next=q;
                    p->Next=q->Next;
                    q->Next=p;
                }
                pre=pre->Next;
                p=pre->Next;
            }
        }
        printf("操作后:");
        traverse(phead);
    }
}
/**
 * 这是颠倒链表的算法，将头结点和首节点断开，依次从NULL，首节点开始对节点成对进行操作。
 * q为p的前一个节点，r为p的后一个节点
 */
void reverseLinkedList(PL phead)
{
    printf("操作前:");
    traverse(phead);
    if(NULL == phead)
    {
        printf("头结点为NULL\n");
    }
    else if(isEmpty(phead))
    {
        return;
    }
    else
    {
        PL p=phead->Next,q = NULL,r;
        while(p)
        {
            r = p->Next;//这里保存操作节点下一个节点的地址
            p->Next = q; //颠倒操作
            q = p; //q向后移动
            p = r;//p向后移动
        }
        //上面循环结束后，p为NULL，q为尾结点
        phead->Next = q;
        printf("操作后:");
        traverse(phead);
    }
}
/*
在求值前驱和后继时的另一种算法：
求值前驱：
PL  p =phead->Next,q;
printf("前驱依次为:");
int j = 0;
while(p && p->Next)
{
    q = p->Next;
    if(q->data == value)
    {
        printf("%d ",p->data);
        j++;
    }
    p=p->Next;
}
if(j == 0)
{
    printf("none");
}
printf("\n");
求值后继:
PL  p =phead->Next,q;
printf("后继依次为:");
int j = 0;
while(p && p->Next)
{
    q = p->Next;
    if(p->data == value)
    {
        printf("%d ",q->data);
        j++;
    }
    p=p->Next;
}
if(j == 0)
{
    printf("none");
}
*/
