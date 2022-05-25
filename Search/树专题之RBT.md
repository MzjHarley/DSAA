---
title: 树专题之RBT
date: 2021-05-17 22:00:13
tags:
categories:
- 树专题
---
RBT
<!--more-->
# RBT起源于2-3-4树，本质为2-3-4树
## 2-3-4树
**2-3-4树是一棵四阶的B树，是一种自平衡的数据结构，属于多路查找树；**
### 具有以下三个性质：
**1.所有叶子节点具有相同的深度**
**2.节点只能是2-节点、3-节点、4-节点**
注：2-节点：包含一个元素，有两个子节点
   3-节点：包含两个元素，有三个子节点
   4-节点：包含三个元素，有四个子节点
**3.元素始终保持排序顺序，整体上保持二叉查找树的性质即父节点大于左子节点，小于右子节点，并且节点有多个元素时，每个元素必须大于它左边和左子树的元素；**
### 2-3-4树效率
2-3-4树的查找操作和BST一样，但由于其节点元素不确定，实现并不方便，实现一般用它的等同—红黑树；
**2-3-4树在O（logn）时间内查找、删除和插入，n为树中元素的数目；**
### 手动建立一棵2-3-4树
**创建规则：
1.优先构造4-节点
2.插入时，永远从最低层插入
3.插入时，如需调整，永远都是中间的上去
4.树是从下向上生长的**
依次插入2、3、4、5、6、7、8、9、10、11、12、1、10.5

{%asset_img 1.png%}


## RBT（Red Black Tree）
RBT是一棵节点带有颜色的二叉查找树，自平衡的二叉查找树；
### 它在二叉查找树之外还有五个性质：
**1.节点为红色或是黑色**
**2.根为黑色节点**
**3.所有叶子节点为黑色节点（叶子节点为NIL节点）**
**4.每个红色节点必有两个黑色节点（从叶子节点到根结点的所有路径上不能有两个连续的红色节点）**
**5.从任意节点到其后代叶子节点（NIL节点）的所有简单路径上都包含相同数目的黑色节点（黑色节点平衡）**
### 有了AVL树，为什么还需要RBT？
**AVL树的实现比较复杂，而且插入删除性能差（旋转次数多），在实际应用中不如红黑树；**
红黑树应用非常广泛，如**java中Treemap和Treeset**、**java8中的HashMap的底层实现用的红黑树（当链表长度>8）性能有所提升**、**Linux底层的CFS进程调度算法中Vruntime利用RBT进行存储、I/O多路复用技术的epoll核心结构是红黑树+双向链表**
**RBT是BST和AVL的折中策略；**
注：
Linux内核主要实现两个调度算法，CFS（Complete Fair Schedule，完全公平调度）算法和实时调度算法。
CFS中进程的插入在红黑树右边，缓存红黑树最左边的节点；
CFS中的进程的选择，选择Vruntime中最小的那个进程，它对应的是红黑树最左边的叶子节点；
CFS中进程的的删除，按照红黑树删除，删除后更新调度信息，从RBT中选出一个最小的Vruntime值的节点，将它作为新的最左边的节点缓存起来；
I/O多路复用技术的Epoll支持高并发，采用事件驱动机制，Linux2.6版本才引入；

### 2-3-4树和红黑树的等价关系
2-节点                      变为黑色
3-节点                     上黑下红
4-节点                     中黑上两边红
裂变状态                 中红上两边黑，新增节点为红色，如果为根节点则中间变为黑色

#### 将上面的2-3-4变为红黑树

{%asset_img 2.png%}
## RBT操作
1.销毁
2.遍历（前序、中序、后序）
3.求最大节点
4.求最小节点
5.求树深度
6.查找（递归查找、非递归查找、插入时查找）
7.插入（插入、插入修正）
8.删除（删除、删除修正）
9.旋转（左旋、右旋）
10.打印（打印出具体红黑树）
11.求前驱节点
12.求后继节点
**其中销毁、遍历、求最大节点、求最小节点、求树深度、查找、旋转等操作与BST类似，我们重点说一下插入和删除操作；**
## RBT插入
RBT的插入相对BST较为复杂；
RBT插入的节点颜色都为红色，以此保证性质4和性质5成立；
我们首先对节点进行辨认：
{%asset_img 8.png %}
接下来我们对RBT插入情况一一进行辨析：
### 情况1：RBT为空树
RBT为空树时，**我们直接把插入节点设置成根节点，并将其颜色由红色设置成黑色；**

### 情况2：插入节点的父节点为黑色
**直接插入**，插入节点是红色的，插入节点的父节点为黑色，插入后不会影响红黑树的平衡，不用进行自平衡处理；

### 情况3：插入节点的父节点为红色
**情况3说明插入节点的祖父节点一定存在**
#### 情况3.1：插入节点的叔叔节点存在且为红色
**将插入节点的父节点和叔叔节点设置为黑色，祖父节点设置成红色**
{%asset_img 4.png %}
**如果插入节点的祖父节点为根节点，则祖父节点必须设置成黑色**
{%asset_img 5.png %}
#### 情况3.2：插入节点的叔叔节点为黑色或不存在
##### 情况3.2.1：插入节点为其父节点的左子节点
以其父节点为其祖父节点的左子节点为例：
**将插入节点的父节点设置为黑色，祖父节点设置为红色，并对祖父节点进行右旋**
{%asset_img 6.png %}
##### 情况3.2.2：插入节点为其父节点的右子节点
以其父节点为其祖父节点的左子节点为例：
**对插入节点的父节点进行左旋，其父节点变为插入节点，其变为新的插入节点的父节点，将新的
插入节点父节点的设置成黑色，祖父节点设置成红色，并对祖父节点进行右旋**
{%asset_img 7.png %}
## RBT插入总结
{%asset_img 3.png %}

## RBT删除
RBT的删除相对RBT的插入更为复杂；
接下来我们对RBT删除情况一一进行辨析：
### 情况1：删除节点无子节点
#### 情况1.1待删除节点为红色节点
**直接删除**
#### 情况1.2待删除节点为黑色节点
##### 情况1.2.1待删除节点的兄弟节点为黑色节点
{%asset_img 9.png %}
###### 情况1.2.1.1两个子侄为NULL，待删除节点的父节点为红色节点
{%asset_img 10.png %}
**删除待删除节点，将待删除节点的父节点涂黑，兄第节点涂红**
{%asset_img 11.png %}
###### 情况1.2.1.2两个子侄为NULL，待删除节点的父节点为黑色节点
{%asset_img 12.png %}
**删除待删除节点，将待删除节点的兄第节点涂红，对待删除节点的父节点进行调整**
{%asset_img 13.png %}
###### 情况1.2.1.3左子侄为红色
以待删除节点为其父节点的左子节点为例
{%asset_img 14.png %}
**将待删除节点删除，对删除节点的兄第节点进行右旋，将左子侄涂成删除节点的父节点的颜色用于顶替删除节点的父节点，将删除节点的父节点涂黑，并对删除节点父节点进行左旋**
{%asset_img 15.png %}

###### 情况1.2.1.3右子侄为红色
以待删除节点为其父节点的左子节点为例
**将待删除节点删除，将其兄弟节点的颜色涂成其父亲节点的颜色，将其父节点涂黑，并对其父节点进行左旋，将右子侄涂成黑色**

{%asset_img 16.png %}

##### 情况1.2.2待删除节点的兄弟节点为红色节点
**则待删除节点的父节点必为黑色节点，其兄弟节点的两个子节点必存在且为黑色**
以待删除节点为其父节点的左子节点为例
{%asset_img 17.png %}
**将待删除节点删除，对删除节点的父节点进行左旋，其父节点和其兄第节点交换颜色，就转换为情况1.2.1删除节点之后的操作了**
{%asset_img 18.png %}
{%asset_img 19.png %}

### 情况2：删除节点有一个子节点
**由性质4、5可知，待删除节点必为黑色，因为红色节点有两个子节点（为黑色），待删除节点的子节点必为红色节点**
**直接将待删除节点删除，用待删除结点的子节点顶替删除节点，再将其由红色染成黑色**

### 情况3：删除节点有两个子节点
**找到删除节点的前驱节点或后继节点，用前驱节点或后继节点替代待删除节点，从而回到情况1或2**
## RBT删除总结
自己做的流程图，转载请说明出处
个别地方待补充
{%asset_img 20.png %}

# RBT源码
```c++
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
typedef struct RBTNode
{
    int data;
    int color;//1代表红色，0代表黑色
    struct RBTNode* left;
    struct RBTNode* right;
    struct RBTNode* parent;
} RBT,*PRBT;
void In_traverse(PRBT RBTtree);//中序遍历
void post_traverse(PRBT RBTtree);//后序遍历
void pre_traverse(PRBT RBTtree);//先序遍历

PRBT get_max(PRBT RBTtree);//得到最大节点
PRBT get_min(PRBT RBTtree);//得到最小节点
PRBT get_pre(PRBT RBTtree);//得到前驱节点
PRBT get_post(PRBT RBTtree);//得到后继节点
int  get_depth(PRBT RBTtree);//得到树深度
int  max(int a,int b);//得到两个数之间的最大值

PRBT search_value_1(PRBT RBTtree,int value);//非递归查找
PRBT search_value_2(PRBT RBTtree,int value);//递归查找
bool search_value_3(PRBT RBTtree,PRBT parent,PRBT& P,int value);//查找，如果成功返回该节点，否则返回其查找路径上最后一个结点


bool insert_Node(PRBT& RBTtree,int value);//插入
void insert_fixup(PRBT& RBTtree,PRBT RBTnew);//插入调整使其满足红黑树性质4和5

void left_rotate(PRBT& RBTtree,PRBT RBTNode);//左旋
void right_rotate(PRBT& RBTtree,PRBT RBTNode);//右旋

PRBT creat_RBT(int*arr,int len);//创建一颗红黑树
void print_RBT(PRBT RBTtree,int direction);//打印红黑树
PRBT Destroy_RBT(PRBT RBTtree);//销毁红黑树

bool Delete_Node(PRBT& RBTtree,int value);//删除外部接口
void Delete(PRBT& RBTtree,PRBT RBTNode);//删除内部接口
void delete_fixup(PRBT& RBTtree,PRBT Child,PRBT Parent);//删除调整使其满足红黑树性质4和5

int main()
{
    printf("*************************************************\n");
    printf("*         1.创建红黑树                          *\n");
    printf("*         2.打印红黑树                          *\n");
    printf("*         3.遍历红黑树                          *\n");
    printf("*         4.销毁红黑树                          *\n");
    printf("*         5.查询红黑树                          *\n");
    printf("*         6.打印红黑树最大值                    *\n");
    printf("*         7.打印红黑树最小值                    *\n");
    printf("*         8.查找节点前驱节点                    *\n");
    printf("*         9.查找节点后继节点                    *\n");
    printf("*        10.查找红黑树深度                      *\n");
    printf("*        11.插入红黑树节点                      *\n");
    printf("*        12.删除红黑树节点                      *\n");
    printf("*************************************************\n");
    char ch;
    PRBT RBTtree=NULL;
    PRBT Temp=NULL;
    int* arr;
    int  value,num,i;
    do
    {
        printf("请输入您想要执行的操作：");
        scanf("%d",&num);
        if(num>0&&num<13)
        {
            switch(num)
            {
            case 1:
                printf("请输入你想要创建节点的个数:");
                scanf("%d",&value);
                arr=(int*)malloc(sizeof(int)*value);
                printf("请为节点赋值（不可相同，中间以空格隔开）:");
                for(i=0; i<value; i++)
                    scanf("%d",arr+i);
                RBTtree=creat_RBT(arr,value);
                printf("红黑树创建已完成\n");
                break;
            case 2:
                if(RBTtree)
                {
                    printf("打印红黑树为：\n");
                    print_RBT(RBTtree,0);
                }
                else
                    printf("树为空\n");
                break;
            case 3:
                if(RBTtree)
                {
                    printf("前序遍历为:");
                    pre_traverse(RBTtree);
                    printf("\n");
                    printf("中序遍历为:");
                    In_traverse(RBTtree);
                    printf("\n");
                    printf("后序遍历为:");
                    post_traverse(RBTtree);
                    printf("\n");
                }
                else
                    printf("树为空\n");
                break;
            case 4:
                if(RBTtree)
                {
                    RBTtree=Destroy_RBT(RBTtree);
                    printf("红黑树已销毁\n");
                }
                else
                    printf("树为空\n");
                break;
            case 5:
                printf("请输入你想要查询的值：");
                scanf("%d",&value);
                if((Temp=search_value_1(RBTtree,value)))
                {
                    printf("查找成功\n");
                    if(Temp->parent)
                        printf("%d(%c) is %d's %s Child.\n",Temp->data,Temp->color==1?'R':'B',Temp->parent->data,Temp->data<Temp->parent->data?"Left":"Right");
                    else
                        printf("%d(%c) is root.\n",Temp->data,Temp->color==1?'R':'B');
                }
                else
                    printf("查找失败\n");
                break;
            case 6:
                if(RBTtree)
                    printf("红黑树最大值为%d\n",get_max(RBTtree)->data);
                else
                    printf("树为空\n");
                break;
            case 7:
                if(RBTtree)
                    printf("红黑树最小值为%d\n",get_min(RBTtree)->data);
                else
                    printf("树为空\n");
                break;
            case 8:
                printf("请输入您想要查询的节点：");
                scanf("%d",&value);
                if(RBTtree)
                {
                    if(get_pre(search_value_1(RBTtree,value)))
                        printf("该结点的前驱节点为%d\n",get_pre(search_value_1(RBTtree,value))->data);
                    else
                        printf("该结点没有前驱节点\n");
                }
                else
                    printf("树为空\n");
                break;
            case 9:
                printf("请输入您想要查询的节点：");
                scanf("%d",&value);
                if(RBTtree)
                {
                    if(get_post(search_value_1(RBTtree,value)))
                        printf("该结点的后继节点为%d\n",get_post(search_value_1(RBTtree,value))->data);
                    else
                        printf("该结点没有后继节点\n");
                }
                else
                    printf("树为空\n");
                break;
            case 10:
                printf("红黑树的深度为%d\n",get_depth(RBTtree));
                break;
            case 11:
                printf("请输入你想要插入的值:");
                scanf("%d",&value);
                if(insert_Node(RBTtree,value))
                {
                    printf("插入成功\n");
                    print_RBT(RBTtree,0);
                }
                else
                    printf("插入失败\n");
                break;
            case 12:
                printf("请输入你想要删除的值:");
                scanf("%d",&value);
                if(Delete_Node(RBTtree,value))
                {
                    printf("删除成功\n");
                    print_RBT(RBTtree,0);
                }
                else
                    printf("删除失败\n");
                break;
            }
        }
        else
            printf("亲,请输入操作对应的合法数字\n");
        printf("请问您是否还要执行操作(Y/N):");
        scanf(" %c",&ch);
    }
    while(ch=='Y'||ch=='y');
    return 0;
}

void In_traverse(PRBT RBTtree)
{
    if(RBTtree)
    {
        if(RBTtree->left)
            In_traverse(RBTtree->left);
        printf("%d ",RBTtree->data);
        if(RBTtree->right)
            In_traverse(RBTtree->right);
    }
}

PRBT creat_RBT(int*arr,int len)
{
    PRBT RBTtree=NULL;
    for(int i=0; i<len; i++)
        insert_Node(RBTtree,arr[i]);
    return RBTtree;
}

void post_traverse(PRBT RBTtree)
{
    if(RBTtree)
    {
        if(RBTtree->left)
            post_traverse(RBTtree->left);
        if(RBTtree->right)
            post_traverse(RBTtree->right);
        printf("%d ",RBTtree->data);
    }
}

void pre_traverse(PRBT RBTtree)
{
    if(RBTtree)
    {
        printf("%d ",RBTtree->data);
        if(RBTtree->left)
            pre_traverse(RBTtree->left);
        if(RBTtree->right)
            pre_traverse(RBTtree->right);
    }
}

PRBT Destroy_RBT(PRBT RBTtree)
{
    if(RBTtree)
    {
        if(RBTtree->left)
            Destroy_RBT(RBTtree->left);
        if(RBTtree->right)
            Destroy_RBT(RBTtree->right);
        free(RBTtree);
    }
    return NULL;
}

PRBT search_value_1(PRBT RBTtree,int value)
{
    PRBT P=RBTtree;
    while(P&&(P->data!=value))
    {
        if(P->data<value)
            P=P->right;
        else
            P=P->left;
    }
    return P;
}

PRBT search_value_2(PRBT RBTtree,int value)
{
    if(RBTtree==NULL||RBTtree->data==value)
        return RBTtree;
    else
    {
        if(RBTtree->data<value)
            return search_value_2(RBTtree->right,value);
        else
            return search_value_2(RBTtree->left,value);
    }
}

bool search_value_3(PRBT RBTtree,PRBT parent,PRBT& P,int value)
{
    if(RBTtree==NULL)
    {
        P=parent;
        return false;
    }
    else
    {
        if(RBTtree->data==value)
        {
            P=RBTtree;
            return true;
        }
        else
        {
            if(RBTtree->data<value)
                return search_value_3(RBTtree->right,RBTtree,P,value);
            else
                return search_value_3(RBTtree->left,RBTtree,P,value);
        }
    }
}

PRBT get_max(PRBT RBTtree)
{
    PRBT P=RBTtree;
    if(P)
    {
        while(P->right)
        {
            P=P->right;
        }
        return P;
    }
    return P;
}

PRBT get_min(PRBT RBTtree)
{
    PRBT P=RBTtree;
    if(P)
    {
        while(P->left)
        {
            P=P->left;
        }
        return P;
    }
    return P;
}

PRBT get_pre(PRBT RBTtree)
{
    if(RBTtree->left)
        return get_max(RBTtree->left);
    PRBT P=RBTtree->parent;
    while(P&&(RBTtree==P->left))
    {
        RBTtree=P;
        P=P->parent;
    }
    return P;
}

PRBT get_post(PRBT RBTtree)
{
    if(RBTtree->right)
        return get_min(RBTtree->right);
    PRBT P=RBTtree->parent;
    while(P&&(RBTtree==P->right))
    {
        RBTtree=P;
        P=P->parent;
    }
    return P;
}

int  get_depth(PRBT RBTtree)
{
    if(NULL==RBTtree)
        return -1;
    return max(get_depth(RBTtree->left),get_depth(RBTtree->right))+1;
}

int  max(int a,int b)
{
    return a<b?b:a;
}

void left_rotate(PRBT& RBTtree,PRBT RBTNode)
{
    PRBT P=RBTNode->right;
    RBTNode->right=P->left;
    if(P->left)
        P->left->parent=RBTNode;
    P->parent=RBTNode->parent;
    if(RBTNode->parent)
    {
        if(RBTNode->parent->left==RBTNode)
            RBTNode->parent->left=P;
        else
            RBTNode->parent->right=P;
    }
    else
    {
        RBTtree=P;
    }
    P->left=RBTNode;
    RBTNode->parent=P;
}

void right_rotate(PRBT& RBTtree,PRBT RBTNode)
{
    PRBT P=RBTNode->left;
    RBTNode->left=P->right;
    if(P->right)
        P->right->parent=RBTNode;
    P->parent=RBTNode->parent;
    if(RBTNode->parent)
    {
        if(RBTNode->parent->left==RBTNode)
            RBTNode->parent->left=P;
        else
            RBTNode->parent->right=P;
    }
    else
    {
        RBTtree=P;
    }
    P->right=RBTNode;
    RBTNode->parent=P;
}

/*
参数 direction -1 表示该节点为左子节点
                0 表示该节点为根节点
		        1 表示该节点为右子节点
*/
void print_RBT(PRBT RBTtree,int direction)
{
    if(RBTtree)
    {
        if(direction==0)
            printf("%d(B) is root\n",RBTtree->data);
        else
            printf("%d(%c) is %d's %5s child\n",RBTtree->data,RBTtree->color==1?'R':'B',RBTtree->parent->data,direction==1?"right":"left");
        if(RBTtree->left)
            print_RBT(RBTtree->left,-1);
        if(RBTtree->right)
            print_RBT(RBTtree->right,1);
    }
}
bool insert_Node(PRBT& RBTtree,int value)
{
    PRBT P=NULL;
    if(!search_value_3(RBTtree,NULL,P,value))
    {
        PRBT RBTnew=(PRBT)malloc(sizeof(RBT));
        RBTnew->data=value;
        RBTnew->left=RBTnew->right=NULL;
        RBTnew->color=1;//新增节点为红色
        RBTnew->parent=NULL;
        if(RBTtree==NULL)
            RBTtree=RBTnew;
        else
        {
            if(P->data<value)
            {
                P->right=RBTnew;
                RBTnew->parent=P;
            }
            else
            {
                P->left=RBTnew;
                RBTnew->parent=P;
            }
        }
        insert_fixup(RBTtree,RBTnew);
        return true;
    }
    else
        return false;
}


void insert_fixup(PRBT& RBTtree,PRBT RBTnew)
{
    PRBT Parent,Gparent;
    while((Parent=RBTnew->parent)&&(1==Parent->color))//插入节点的父节点存在为红色，必须要做出调整
    {
        Gparent=Parent->parent;//祖父节点一定存在
        if(Gparent->left==Parent)//其父节点为其祖父节点的左子节点
        {
            PRBT Uncle=Gparent->right;
            if(Uncle&&(1==Uncle->color))//情况1:叔叔存在且为红色
            {
                Uncle->color=0;
                Parent->color=0;
                Gparent->color=1;
                RBTnew=Gparent;
                continue;
            }
            if(Parent->left==RBTnew)//情况2:叔叔节点为黑色或不存在，插入节点为左子节点
            {
                right_rotate(RBTtree,Gparent);
                Gparent->color=1;
                Parent->color=0;
                continue;
            }
            if(Parent->right==RBTnew)//情况3:叔叔节点为黑色或不存在，插入节点为右子节点
            {
                left_rotate(RBTtree,Parent);
                right_rotate(RBTtree,Gparent);
                Gparent->color=1;
                RBTnew->color=0;
            }
            //情况2和3调整后，可能就不满足循环条件
        }
        else
        {
            PRBT Uncle=Gparent->left;
            if(Uncle&&(1==Uncle->color))//情况1:叔叔存在且为红色
            {
                Uncle->color=0;
                Parent->color=0;
                Gparent->color=1;
                RBTnew=Gparent;
                continue;
            }
            if(Parent->left==RBTnew)//情况2:叔叔节点为黑色或不存在，插入节点为左子节点
            {
                right_rotate(RBTtree,Parent);
                left_rotate(RBTtree,Gparent);
                RBTnew->color=0;
                Gparent->color=1;
                continue;
            }
            if(Parent->right==RBTnew)//情况3:叔叔节点为黑色或不存在，插入节点为左子节点
            {
                left_rotate(RBTtree,Gparent);
                Parent->color=0;
                Gparent->color=1;
            }
        }
    }
    RBTtree->color=0;
}

bool Delete_Node(PRBT& RBTtree,int value)
{
    PRBT Temp;
    if((Temp=search_value_1(RBTtree,value)))//寻找到该结点,这里加括号可不是多余，可以消除一个警告
    {
        Delete(RBTtree,Temp);//删除该结点
        return true;
    }
    else
        return false;
}
void Delete(PRBT& RBTtree,PRBT RBTNode)
{
    PRBT Child,Parent;
    int color;
    if((RBTNode->left)&&(RBTNode->right))//待删除节点有两个子节点
    {
        PRBT Post=get_post(RBTNode);//找到该结点的后继节点，用后继节点替代待删除节点
        if(RBTNode->parent)
        {
            if(RBTNode->parent->left==RBTNode)
                RBTNode->parent->left=Post;
            else
                RBTNode->parent->right=Post;
        }
        else
            RBTtree=Post;//如果为空，就说明RBTNode为根节点，则将替代节点设置成根节点
        Child=Post->right;//后继结点一定没有左子节点
        Parent=Post->parent;//现在不着急进行替代，在替代前必须进行必要的判断，此时Parent可能不是RBTNode
        color=Post->color;//保存后继节点的颜色，后续会有颜色替代，保存替代节点的颜色有利于有利于决定是否调整
        if(Parent==RBTNode)//，考虑极端情况，若后继节点的父节点为RBTNode
        {
            Parent=Post;//这一步包含深意，如果看不懂，请继续往后看,保证Parent始终是Child的父亲
        }
        else
        {
            if(Child)//如果孩子不为空
                Child->parent=Parent;
            Parent->left=Child;
            Post->right=RBTNode->right;//Post替代待删除节点
            RBTNode->right->parent=Post;
        }
        //进行替代
        Post->color=RBTNode->color;
        Post->left=RBTNode->left;
        Post->parent=RBTNode->parent;
        RBTNode->left->parent=Post;
        if(0==color)//如果替代节点的颜色为黑色，则进行调整
            delete_fixup(RBTtree,Child,Parent);
        free(RBTNode);
        return;
    }
    //之后则是在删除节点没有两个子节点的基础上讨论，即删除节点有一个子节点，或没有子节点
    if(RBTNode->left)//如果待删除节点的左子节点不为空
        Child=RBTNode->left;
    else
        Child=RBTNode->right;
    Parent=RBTNode->parent;
    color=RBTNode->color;//如果RBTNode为红色则无需要调整，为黑色需要调整
    if(Child)
        Child->parent=Parent;//判断RBTNode是否有孩子
    if(Parent)
    {
        if(Parent->left==RBTNode)
            Parent->left=Child;
        else
            Parent->right=Child;
    }
    else
        RBTtree=Child;
    if(0==color)//待删除节点为黑色，则需要进行调整
        delete_fixup(RBTtree,Child,Parent);
    free(RBTNode);
}
/*
参数：
     RBTtree 为根节点
     Child   为待调整节点
     Parent  为待调整节点的父节点
*/
void delete_fixup(PRBT& RBTtree,PRBT Child,PRBT Parent)
{
    PRBT  Temp;
    while((!Child||(Child->color==0))&&Child!=RBTtree)//子节点为空或者为黑色并且子节点不是根节点，即若待调整节点为红色，或为根节点，无需调整
    {
        if(Parent->left==Child)//待调整节点为左子节点时
        {
            Temp=Parent->right;//据红黑树性质4和5，右节点一定存在0
            if(1==Temp->color)//情况1：兄弟节点为红色，则子侄一定存在并且为黑色
            {
                Temp->color=0;
                Parent->color=1;
                left_rotate(RBTtree,Parent);
                Temp=Parent->right;//用于执行下面步骤以继续循环或终止循环
            }
            if((!Temp->left||(0==Temp->left->color))&&(!Temp->right||(0==Temp->right->color)))
                //情况2：兄弟节点为黑色，据红黑树性质4和5，两个子侄不存在，父亲颜色随意;
                //该情况需要用循环调整
            {
                Temp->color=1;
                Child=Parent;
                Parent=Child->parent;
            }
            else//兄弟节点为黑色，但子侄不都为空并且不都为黑色
            {
                if(!Temp->right||(0==Temp->right->color))//右子侄不存在或者为黑色，即左子侄存在并且为红色
                {
                    Temp->left->color=Parent->color;//将父节点的颜色赋给Temp->left,T以便顶替父节点
                    Parent->color=0;
                    right_rotate(RBTtree,Temp);
                    left_rotate(RBTtree,Parent);
                }
                else//右子侄存在并且为红色
                {
                    Temp->color=Parent->color;
                    Parent->color=0;
                    Temp->right->color=0;
                    left_rotate(RBTtree,Parent);
                }
                Child=RBTtree;//不论何时Child总能指向RBTtree
                break;
            }
        }
        else
        {
            Temp=Parent->left;//据红黑树性质4和5，左节点一定存在
            if(1==Temp->color)//情况1：兄弟节点为红色，则子侄一定存在并且为黑色
            {
                Temp->color=0;
                Parent->color=1;
                right_rotate(RBTtree,Parent);
                Temp=Parent->left;
            }
            if((!Temp->left||(0==Temp->left->color))&&(!Temp->right||(0==Temp->right->color)))
                //情况2：兄弟节点为黑色，据红黑树性质4和5，两个子侄不存在，父亲颜色随意
            {
                Temp->color=1;
                Child=Parent;
                Parent=Child->parent;
            }
            else//兄弟节点为黑色，但子侄不都为空并且为黑色
            {
                if(!Temp->right||(0==Temp->right->color))//右子侄不存在或者为黑色，即左子侄存在并且为红色
                {
                    Temp->color=Parent->color;//将父节点的颜色赋给Temp,以便顶替父节点
                    Parent->color=0;
                    Temp->left->color=0;
                    right_rotate(RBTtree,Parent);
                }
                else//右子侄存在并且为红色
                {
                    Temp->right->color=Parent->color;
                    Parent->color=0;
                    left_rotate(RBTtree,Temp);
                    right_rotate(RBTtree,Parent);
                }
                Child=RBTtree;
                break;
            }
        }
    }
    if(Child)
        Child->color=0;
}
```