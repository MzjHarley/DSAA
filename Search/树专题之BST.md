---
title: 树专题之BST
date: 2021-05-07 07:16:51
tags:
categories:
- 树专题
---
BST
<!--more-->
### BST(Binary Search Tree)
二叉搜索树，该树左节点比父节点小，右节点比父节点大，高度决定查找效率；
BST基本操作：
1.查找
2.销毁
3.删除
4.求树深度
5.求最大节点
6.插入
7.求最小节点
8.遍历
### BST源码
```c
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct Node
{
	int data;
	struct Node*Lchild;
	struct Node*Rchild;
}NODE,*PNODE;
PNODE create_BST(int*arr,int len);
bool insert_Node(PNODE &Ptree,int key);
bool search_value_1(PNODE Ptree,int key,PNODE Parent,PNODE &P);
PNODE search_value_2(PNODE Ptree,int key);
bool Delete_Node(PNODE &Ptree,int key);
void Delete_P(PNODE &P);
void Delete_S(PNODE &P);
void Destroy_BST(PNODE Ptree);
void Pre_traverse(PNODE Ptree);
void In_traverse(PNODE Ptree);
void Post_traverse(PNODE Ptree);
int get_max(PNODE Ptree);
int get_min(PNODE Ptree);
int get_depth(PNODE Ptree);
int main()
{
	int len;
	printf("请输入BST结点的个数:");
	scanf("%d",&len);
	int*arr=(int*)malloc(sizeof(int)*len);
	printf("请为节点赋值（赋值不可相同且中间以空格隔开）:");
	for(int i=0;i<len;i++)
		scanf("%d",arr+i);
	PNODE Ptree=create_BST(arr,len);
	printf("先序输出为:");
	Pre_traverse(Ptree);
	printf("\n");
	printf("中序输出为:");
	In_traverse(Ptree);
	printf("\n");
	printf("后序输出为:");
	Post_traverse(Ptree);
	printf("\n");
	printf("BST深度为:%d\n",get_depth(Ptree));
	printf("BST节点最大值为:%d\n",get_max(Ptree));
	printf("BST节点最小值为:%d\n",get_min(Ptree));
	int value;
	char ch;
	do
	{
		printf("请输入你想要查找的值:");
		scanf("%d",&value);
		if(search_value_2(Ptree,value))
		    printf("查找成功\n");
		else
		    printf("查找失败\n");
		printf("请问你是否继续查找(Y/N):");
		scanf(" %c",&ch);
	}while(ch=='Y'||ch=='y');
	do
	{
		printf("请输入你想要插入的值:");
		scanf("%d",&value);
		if(insert_Node(Ptree,value))
		{
			printf("插入成功\n中序遍历为");
			In_traverse(Ptree);
			printf("\n");
		}
		else
			printf("插入失败\n");
		printf("请问你是否继续插入(Y/N):");
		scanf(" %c",&ch);
	}while(ch=='Y'||ch=='y');
	do
	{
		printf("请输入你想要删除的值:");
		scanf("%d",&value);
		if(Delete_Node(Ptree,value))
		{
			printf("删除成功\n中序遍历为");
			In_traverse(Ptree);
			printf("\n");
		}
		else
			printf("删除失败\n");
		printf("请问你是否继续删除(Y/N):");
		scanf(" %c",&ch);
	}while(ch=='Y'||ch=='y');
	Destroy_BST(Ptree);
	Ptree=NULL;
	return 0;
}
//这里我可以先序创建二叉树
PNODE create_BST(int*arr,int len)
{
	PNODE Ptree=NULL;
	for(int i=0;i<len;i++)
	    insert_Node(Ptree,arr[i]);
	return Ptree;
}
bool insert_Node(PNODE &Ptree,int key)
{
	PNODE P;
	if(!search_value_1(Ptree,key,NULL,P))
	{
		PNODE PNew=(PNODE)malloc(sizeof(NODE));
		PNew->data=key;
		PNew->Lchild=PNew->Rchild=NULL;
		if(Ptree==NULL)
		{
			Ptree=PNew;
		}
		else
		{
			if(P->data<key)
				P->Rchild=PNew;
			else
				P->Lchild=PNew;
		}
		return true;
	}
	else
		return false;
}
bool search_value_1(PNODE Ptree,int key,PNODE Parent,PNODE &P)
{
	if(Ptree==NULL)
	{
		P=Parent;
		return false;
	}
	else
	{
		if(Ptree->data==key)
		{
			P=Ptree;	    
			return true;	
		}
		else if(Ptree->data<key)
			return search_value_1(Ptree->Rchild,key,Ptree,P);
		else
			return search_value_1(Ptree->Lchild,key,Ptree,P);
	}
}
PNODE search_value_2(PNODE Ptree,int key)
{
	if(Ptree==NULL||Ptree->data==key)
		return Ptree;
	else
	{
		if(Ptree->data<key)
			return search_value_2(Ptree->Rchild,key);
		else
			return search_value_2(Ptree->Lchild,key);
	}
}
bool Delete_Node(PNODE &Ptree,int key)
{
	if(Ptree==NULL)
		return false;
	else
	{
		if(Ptree->data==key)
		{
			Delete_P(Ptree);
			//Delete_S(Ptree);
			return true;
		}
		else if(Ptree->data<key)
			return Delete_Node(Ptree->Rchild,key);
		else
			return Delete_Node(Ptree->Lchild,key);	
	}
}
void Delete_P(PNODE &P)
{
	PNODE Q,S;
	if(P->Lchild==NULL)
	{
		Q=P;
		P=P->Rchild;
		free(Q);
	}
	else if(P->Rchild==NULL)
	{
		Q=P;
		P=P->Lchild;
		free(Q);
	}
	else
	{
		S=P->Lchild;
		while(S->Rchild!=NULL)
		{
			S=S->Rchild;
		}
		S->Rchild=P->Rchild;
		Q=P;
		P=P->Lchild;
		free(Q);
	}
}
void Delete_S(PNODE &P)
{
	PNODE Q,S;
	if(!P->Lchild)
	{
		Q=P;
		P=P->Rchild;
		free(Q);
	}
	else if(!P->Rchild)
	{
		Q=P;
		P=P->Lchild;
		free(Q);
	}
	else
	{
		Q=P;
		S=P->Lchild;
		while(S->Rchild!=NULL)
		{
			Q=S;
			S=S->Rchild;
		}
		P->data=S->data;
		if(Q!=P)
			Q->Rchild=S->Lchild;
		else
			Q->Lchild=S->Lchild;
		free(S);
	}

```
### BST存在的问题
数在插入时会导致树的倾斜，不同的插入顺序将会导致树的深度不同，树的深度决定了树的查找
效率，理想高度为logn，最坏情况下所有节点在同一条斜线上此时树深度为n。基于这个问题， 
Balanced BST诞生了，Balanced BST在插入删除时会通过旋转操作将树高度保持在logn，其中
最著名的是AVL和红黑树；
；