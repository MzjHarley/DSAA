/**
 * 本程序用于创建哈夫曼树，并打印出哈夫曼编码。
 */
#include <iostream>
#include<malloc.h>
#include<algorithm>

using namespace std;

typedef struct Huffman
{
    char ch;
    int lc;
    int rc;
    int weight;
    int parent;
} H,*HT;

void createHuffman(HT&ht,int n);
int findMin(HT&ht,int n);
void HuffmanCode(HT ht,int n);

int main()
{
    HT ht;
    int n;
    cout<<"请输入哈夫曼树叶子节点个数:";
    cin>>n;
    createHuffman(ht,n);
    HuffmanCode(ht,n);
    return 0;
}

void createHuffman(HT&ht,int n)
{
    ht=(HT)malloc(sizeof(H)*(n*2));//包含n个叶子节点(1~n)，n-1个新生成的节点(n+1~2n-1)，0号节点不使用。
    if(!ht)
        exit(-1);
    int weight,S1,S2;
    char ch;
    cout<<"请依次为每个叶子节点赋值和权:(字符 权值)"<<endl;
    for(int i=1; i<=n; i++)//为叶子节点赋权并初始化
    {
        cin>>ch;
        cin>>weight;
        ht[i].weight=weight;
        ht[i].ch=ch;
        ht[i].parent=ht[i].rc=ht[i].lc=0;
    }
    for(int i=n+1; i<2*n; i++)//执行n-1次合并创建n-1个新的节点，每次挑选出权值最小的两个节点合并生成新节点，并用新节点代替这两个节点。
    {
        S1=findMin(ht,i-1),S2=findMin(ht,i-1);//挑选
        ht[S1].parent=ht[S2].parent=i;//对挑选出的两个节点进行处理
        ht[i].weight=ht[S1].weight+ht[S2].weight;//赋权
        ht[i].parent=0,ht[i].lc=S1,ht[i].rc=S2;//初始化
    }
}

int findMin(HT&ht,int n)
{
    int minElem=UINT16_MAX,s;
    for(int i=1; i<=n; i++)
        if(ht[i].weight<minElem && ht[i].parent==0)
            minElem=ht[i].weight,s=i;
    ht[s].parent=1;//这里找到最小的权后，据判断条件删除该节点   
    return s;
}

void HuffmanCode(HT ht,int n)
{
    string hc[n+1];//字符串数组保存每个叶子节点的哈夫曼编码。
    if(!hc)
        exit(-1);
    for(int i=1;i<=n;i++)//这里代表每个叶子节点
    {
        string cd;
        for(int j=i,f=ht[j].parent;f!=0;j=f,f=ht[f].parent)//从每个叶子节点回溯，一直到其双亲为0结束，左0右1
        {
            if(ht[f].lc==j)
                cd+='0';
            else if(ht[f].rc==j)
                cd+='1';
        }
        //将cd字符串颠倒赋给hc
        reverse(cd.begin(),cd.end());
        hc[i]=cd;        
        cout<<ht[i].ch<<":";
        cout<<hc[i]<<endl;
    }

}
