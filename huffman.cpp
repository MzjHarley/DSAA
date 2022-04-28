/**
 * ���������ڴ�����������������ӡ�����������롣
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
    cout<<"�������������Ҷ�ӽڵ����:";
    cin>>n;
    createHuffman(ht,n);
    HuffmanCode(ht,n);
    return 0;
}

void createHuffman(HT&ht,int n)
{
    ht=(HT)malloc(sizeof(H)*(n*2));//����n��Ҷ�ӽڵ�(1~n)��n-1�������ɵĽڵ�(n+1~2n-1)��0�Žڵ㲻ʹ�á�
    if(!ht)
        exit(-1);
    int weight,S1,S2;
    char ch;
    cout<<"������Ϊÿ��Ҷ�ӽڵ㸳ֵ��Ȩ:(�ַ� Ȩֵ)"<<endl;
    for(int i=1; i<=n; i++)//ΪҶ�ӽڵ㸳Ȩ����ʼ��
    {
        cin>>ch;
        cin>>weight;
        ht[i].weight=weight;
        ht[i].ch=ch;
        ht[i].parent=ht[i].rc=ht[i].lc=0;
    }
    for(int i=n+1; i<2*n; i++)//ִ��n-1�κϲ�����n-1���µĽڵ㣬ÿ����ѡ��Ȩֵ��С�������ڵ�ϲ������½ڵ㣬�����½ڵ�����������ڵ㡣
    {
        S1=findMin(ht,i-1),S2=findMin(ht,i-1);//��ѡ
        ht[S1].parent=ht[S2].parent=i;//����ѡ���������ڵ���д���
        ht[i].weight=ht[S1].weight+ht[S2].weight;//��Ȩ
        ht[i].parent=0,ht[i].lc=S1,ht[i].rc=S2;//��ʼ��
    }
}

int findMin(HT&ht,int n)
{
    int minElem=UINT16_MAX,s;
    for(int i=1; i<=n; i++)
        if(ht[i].weight<minElem && ht[i].parent==0)
            minElem=ht[i].weight,s=i;
    ht[s].parent=1;//�����ҵ���С��Ȩ�󣬾��ж�����ɾ���ýڵ�   
    return s;
}

void HuffmanCode(HT ht,int n)
{
    string hc[n+1];//�ַ������鱣��ÿ��Ҷ�ӽڵ�Ĺ��������롣
    if(!hc)
        exit(-1);
    for(int i=1;i<=n;i++)//�������ÿ��Ҷ�ӽڵ�
    {
        string cd;
        for(int j=i,f=ht[j].parent;f!=0;j=f,f=ht[f].parent)//��ÿ��Ҷ�ӽڵ���ݣ�һֱ����˫��Ϊ0��������0��1
        {
            if(ht[f].lc==j)
                cd+='0';
            else if(ht[f].rc==j)
                cd+='1';
        }
        //��cd�ַ����ߵ�����hc
        reverse(cd.begin(),cd.end());
        hc[i]=cd;        
        cout<<ht[i].ch<<":";
        cout<<hc[i]<<endl;
    }

}