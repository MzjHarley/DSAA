#include <iostream>
#include <stdlib.h>
#include<stack>
#include<queue>
using namespace std;

typedef struct TNode
{
    char data;
    struct TNode* LC;
    struct TNode* RC;
} T,*PT;
void createTree(PT &root);
void preTraverse(PT root);
void postTraverse(PT root);
void MiddleTraverse(PT root);
void MiddleTraverse2(PT root);
void LevelTraverse(PT root);
int getHeight(PT root);
int getLeafNum(PT root);
int main()
{
    PT root;
    createTree(root);//input:ABC##DE#G##F###
    preTraverse(root);
    cout<<"\n";
    postTraverse(root);
    cout<<"\n";
    MiddleTraverse(root);
    cout<<"\n";
    MiddleTraverse2(root);
    LevelTraverse(root);
    cout<<getHeight(root)<<endl;
    cout<<getLeafNum(root);
    return 0;
}
/**
 * create binary tree using the preceding order.
*/
void createTree(PT &root)
{
    char ch;
    cin>>ch;
    if(ch=='#')
        root=NULL;
    else
    {
        root=(PT)malloc(sizeof(T));
        if(!root) exit(-1);
        root->data=ch;
        createTree(root->LC);
        createTree(root->RC);
    }
}
void preTraverse(PT root)
{
    if(root)
    {
        cout<<root->data<<" ";
        preTraverse(root->LC);
        preTraverse(root->RC);
    }
}
void postTraverse(PT root)
{
    if(root)
    {
        postTraverse(root->LC);
        postTraverse(root->RC);
        cout<<root->data<<" ";
    }

}
void MiddleTraverse(PT root)
{
    if(root)
    {
        MiddleTraverse(root->LC);
        cout<<root->data<<" ";
        MiddleTraverse(root->RC);
    }
}
void MiddleTraverse2(PT root)
{
    stack<PT>s;
    PT p = root,q;
    while(!s.empty() || p)
    {
        if(p)
        {
            s.push(p);
            p=p->LC;
        }
        else
        {
            q=s.top();
            s.pop();
            cout<<q->data<<" ";
            p=q->RC;
        }
    }
    cout<<"\n";
}
void LevelTraverse(PT root)
{
    if(!root)
        return;
    else
    {
        queue<PT> q;
        PT p=root,t;
        q.push(p);
        while(!q.empty())
        {
            t=q.front();
            q.pop();
            cout<<t->data<<" ";
            if(t->LC)
                q.push(t->LC);
            if(t->RC)
                q.push(t->RC);
        }
        cout<<endl;
    }
}
int getHeight(PT root)
{
    if(!root)
        return 0;
    else
        return getHeight(root->LC)>getHeight(root->RC)?getHeight(root->LC)+1:getHeight(root->RC)+1;
}
int getLeafNum(PT root)
{
    if(!root)
        return 0;
    else if(!root->LC&&!root->LC)
        return 1;
    else
        return getLeafNum(root->LC)+getLeafNum(root->RC);
}
