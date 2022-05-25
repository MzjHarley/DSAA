---
title: 树专题之AVL
date: 2021-05-08 22:37:59
tags:
categories:
- 树专题
---
AVL
<!--more-->
### AVL（Balanced Binary Search Tree）
AVL树为自平衡二叉树、高平衡二叉搜索树，名字取自两位发明者的名字；
**AVL具有二叉搜索树的所有特性，并且左右子树的高度差不超过1；**
它通过旋转使树的高度保持在logn，从而使查找删除的复杂度为O（logn）；
### 相关术语
#### 平衡
当节点数固定时，左右子树的高度越接近，这样的二叉树越平衡（深度越低）；
**最理想的平衡为满二叉树和完全二叉树，这样的树高度最小；**
#### 平衡因子（Balanced Factor）
某节点左右子树的高度差（左子树高度-右子树高度）
AVL树的每个节点的平衡因子只能为0，-1，1，如果超过1或者小于-1，则为失衡；
简单来说，AVL每个节点的高度差不超过1；
### AVL是BST的优化
#### 如何改进BST？
在节点插入删除后，想办法让BST恢复平衡（减小树的高度）。
如果不断调整节点的位置，完全可以达到理想平衡（完全二叉树），但付出的代价可能会比较大，比如说调整的次
数会增大，反而增加了时间复杂度；
**我们在这里采取了折中策略，让BST达到适度平衡。**

#### 平衡二叉搜索树
一棵达到适度平衡的二叉搜索树（BST）称为平衡二叉搜索树（Balanced BST）；
其中最为著名的是AVL和RBT(Red Black Tree)；
#### 手动建立一棵AVL树
依次插入13、14、15、12、11、17、16、8、9、1
{%asset_img 1.png%}

### AVL操作
1.销毁
2.删除 
3.插入
4.查找
5.求树最大节点
6.求树最小节点
7.遍历（先序、中序、后序）
8.旋转（左旋（调整失衡节点）、右旋（调整失衡节点），双旋（先调整失衡节点的左节点或右节点，再调整失衡节点，分为LR、RL）
9.判断该树是否平衡
10.求树深度（从根节点开始，为空时-1）
11.求树高度（从叶子节点开始，为空时-1）

### AVL源码
```c++
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
typedef struct AVLNode
{
    int data;
    int height;
    struct AVLNode*Left;
    struct AVLNode*Right;
} AVLNODE,*PAVL;
int get_depth(PAVL AVLtree);
int get_height(PAVL AVLtree);
int max(int a,int b);
int get_max(PAVL AVLtree);
int get_min(PAVL AVLtree);
PAVL create_AVL(int*arr,int len);
PAVL Destroy_AVL(PAVL AVLtree);
void Pre_traverse(PAVL AVLtree);
void In_traverse(PAVL AVLtree);
void Post_traverse(PAVL AVLtree);
PAVL Search_value(PAVL AVLtree,int value);
PAVL LL_R_Rotate(PAVL AVLtree);
PAVL RR_L_Rotate(PAVL AVLtree);
PAVL LR_L_R_Rotate(PAVL AVLtree);
PAVL RL_R_L_Rotate(PAVL AVLtree);
bool Is_balanced(PAVL AVLtree);
int abs(int a);
PAVL Insert(PAVL AVLtree,int value);
void Delete_1(PAVL& AVLtree);
void Delete_2(PAVL& AVLtree);
PAVL Delete(PAVL& AVLtree,int vlaue);
int main()
{
    int len;
    printf("请输入你想要输入的节点数:");
    scanf("%d",&len);
    int*arr=(int*)malloc(sizeof(int)*len);
    printf("请为每个节点赋值（值不可相同）:");
    for(int i=0; i<len; i++)
        scanf("%d",arr+i);
    PAVL AVLtree=create_AVL(arr,len);
    printf("先序遍历为:");
    Pre_traverse(AVLtree);
    printf("\n");
    printf("中序遍历为:");
    In_traverse(AVLtree);
    printf("\n");
    printf("后序遍历为:");
    Post_traverse(AVLtree);
    printf("\n");
    if(Is_balanced(AVLtree))
        printf("AVL树平衡\n");
    else
        printf("AVL树不平衡\n");
    printf("AVL树的最大节点为%d\n",get_max(AVLtree));
    printf("AVL树的最小节点为%d\n",get_min(AVLtree));
    printf("AVL树的深度为%d\n",get_depth(AVLtree));
    int value;
    char ch;
    do
    {
     printf("请输入你想要查找的值:");
     scanf("%d",&value);
     if(Search_value(AVLtree,value))
          printf("查找成功\n");
     else
          printf("查找失败\n");
     printf("请问你是否还要继续(Y/N):");
     scanf(" %c",&ch);
    }while(ch=='Y'||ch=='y');
    do
    {
     printf("请输入你想要插入的值:");
     scanf("%d",&value);
     if(AVLtree=Insert(AVLtree,value))
     {
         printf("插入成功\n中序遍历为");
         In_traverse(AVLtree);
         printf("\n");
         if(Is_balanced(AVLtree))
            printf("AVL树平衡\n");
         else
            printf("AVL树不平衡\n");
         printf("AVL树的最大节点为%d\n",get_max(AVLtree));
         printf("AVL树的最小节点为%d\n",get_min(AVLtree));
       	 printf("AVL树的深度为%d\n",get_depth(AVLtree));
     }
     else
         printf("插入失败\n");
     printf("请问你是否还要继续(Y/N):");
     scanf(" %c",&ch);
    }while(ch=='Y'||ch=='y');
    do
    {
        printf("请输入你想要删除的值:");
        scanf("%d",&value);
        AVLtree=Delete(AVLtree,value);
        printf("中序遍历为");
        In_traverse(AVLtree);
        printf("\n");
        if(Is_balanced(AVLtree))
            printf("AVL树平衡\n");
        else
            printf("AVL树不平衡\n");
        printf("AVL树的最大节点为%d\n",get_max(AVLtree));
        printf("AVL树的最小节点为%d\n",get_min(AVLtree));
        printf("AVL树的深度为%d\n",get_depth(AVLtree));
        printf("请问你是否还要继续(Y/N):");
        scanf(" %c",&ch);
    }
    while(ch=='Y'||ch=='y');
    AVLtree=Destroy_AVL(AVLtree);
    return 0;
}
PAVL create_AVL(int*arr,int len)
{
    PAVL AVLtree=NULL;
    for(int i=0; i<len; i++)
        AVLtree=Insert(AVLtree,arr[i]);
    return AVLtree;
}
PAVL Search_value(PAVL AVLtree,int value)
{
    if(AVLtree==NULL||AVLtree->data==value)
        return AVLtree;
    else
    {
        if(value<AVLtree->data)
            return Search_value(AVLtree->Left,value);
        else
            return Search_value(AVLtree->Right,value);
    }
}
PAVL LL_R_Rotate(PAVL AVLtree)
{
    if(AVLtree)
    {
        PAVL P=AVLtree->Left;
        AVLtree->Left=P->Right;
        P->Right=AVLtree;
        AVLtree->height=max(get_height(AVLtree->Left),get_height(AVLtree->Right))+1;
        P->height=max(get_height(P->Left),AVLtree->height)+1;
        return P;
    }
    return NULL;
}
PAVL RR_L_Rotate(PAVL AVLtree)
{
    if(AVLtree)
    {
        PAVL P=AVLtree->Right;
        AVLtree->Right=P->Left;
        P->Left=AVLtree;
        AVLtree->height=max(get_height(AVLtree->Left),get_height(AVLtree->Right))+1;
        P->height=max(get_height(P->Right),AVLtree->height)+1;
        return P;
    }
    return NULL;
}
PAVL LR_L_R_Rotate(PAVL AVLtree)
{
    AVLtree->Left=RR_L_Rotate(AVLtree->Left);
    return LL_R_Rotate(AVLtree);
}
PAVL RL_R_L_Rotate(PAVL AVLtree)
{
    AVLtree->Right=LL_R_Rotate(AVLtree->Right);
    return RR_L_Rotate(AVLtree);
}
bool Is_balanced(PAVL AVLtree)
{
    if(AVLtree==NULL)
        return true;
    if(abs(get_height(AVLtree->Left)-get_height(AVLtree->Right))<=1&&Is_balanced(AVLtree->Left)&&Is_balanced(AVLtree->Right))
        return true;
    return false;
}
int abs(int a)
{
    return a<0?-a:a;
}
PAVL Insert(PAVL AVLtree,int value)
{
    if(!Search_value(AVLtree,value))
    {
        if(AVLtree==NULL)
        {
            AVLtree=(PAVL)malloc(sizeof(AVLNODE));
            AVLtree->data=value;
            AVLtree->height=0;
            AVLtree->Left=AVLtree->Right=NULL;
        }
        else
        {
            if(value< AVLtree->data)
            {
                AVLtree->Left=Insert(AVLtree->Left,value);
                if(get_height(AVLtree->Left)-get_height(AVLtree->Right)==2)
                {
                    if(value<AVLtree->Left->data)
                        AVLtree=LL_R_Rotate(AVLtree);
                    else
                        AVLtree=LR_L_R_Rotate(AVLtree);
                }
            }
            else
            {
                AVLtree->Right=Insert(AVLtree->Right,value);
                if(get_height(AVLtree->Right)-get_height(AVLtree->Left)==2)
                {
                    if(value>AVLtree->Right->data)
                        AVLtree=RR_L_Rotate(AVLtree);
                    else
                        AVLtree=RL_R_L_Rotate(AVLtree);
                }
            }
        }
        AVLtree->height=max(get_height(AVLtree->Left),get_height(AVLtree->Right))+1;
        return AVLtree;
    }
    else
        return NULL;
}
void Delete_1(PAVL& AVLtree)
{
    PAVL P,Q;
    if(!AVLtree->Left)
    {
        P=AVLtree;
        AVLtree=AVLtree->Right;
        free(P);
    }
    else if(!AVLtree->Right)
    {
        P=AVLtree;
        AVLtree=AVLtree->Left;
        free(P);
    }
    else
    {
        P=AVLtree->Left;
        while(P->Right)
        {
            P=P->Right;
        }
        P->Right=AVLtree->Right;
        Q=AVLtree;
        AVLtree=AVLtree->Left;
        free(Q);
    }
}
void Delete_2(PAVL& AVLtree)
{
    PAVL P,Q;
    if(!AVLtree->Left)
    {
        P=AVLtree;
        AVLtree=AVLtree->Right;
        free(P);
    }
    else if(!AVLtree->Right)
    {
        P=AVLtree;
        AVLtree=AVLtree->Left;
        free(P);
    }
    else
    {
        Q=AVLtree;
        P=AVLtree->Left;
        while(P->Right)
        {
            Q=P;
            P=P->Right;
        }
        AVLtree->data=P->data;
        if(Q==AVLtree)
            Q->Left=P->Left;
        else
            Q->Right=P->Left;
        free(P);
    }
}
PAVL Delete(PAVL &AVLtree,int value)
{
    if(AVLtree==NULL)
        return NULL;
    else
    {
        if(AVLtree->data==value)
        {
            Delete_1(AVLtree);
            //或Delete_2(AVLtree);
        }
        else if(value<AVLtree->data)
        {
            Delete(AVLtree->Left,value);
        }
        else
            Delete(AVLtree->Right,value);
    }
    if(AVLtree)
    {
        if(get_height(AVLtree->Left)-get_height(AVLtree->Right)==2)
            if(get_height(AVLtree->Left->Left)-get_height(AVLtree->Left->Right)==-1)
                AVLtree=LR_L_R_Rotate(AVLtree);
            else
                AVLtree=LL_R_Rotate(AVLtree);
        if(get_height(AVLtree->Left)-get_height(AVLtree->Right)==-2)
            if(get_height(AVLtree->Right->Left)-get_height(AVLtree->Right->Right)==-1)
                AVLtree=RR_L_Rotate(AVLtree);
            else
                AVLtree=RL_R_L_Rotate(AVLtree);
        AVLtree->height=max(get_height(AVLtree->Left),get_height(AVLtree->Right))+1;
    }
    return AVLtree;
}
```

