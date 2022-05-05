/**
 * This program  encodes 27 letters of a-z and space as huffman code,encodes the string as huffman code and decodes the huffman code as string.
 */

#include <iostream>
#include<malloc.h>
#include<algorithm>
#include<string>
using namespace std;
typedef struct Huffman
{
    char ch;
    int lc;
    int rc;
    int weight;
    int parent;
} H,*HT;
string s;
int arr[27];
string hc[28];
void inputArg();
void initArg();
void create(HT&ht,int n);
void printC(HT ht,int n);
void codeToChar(HT ht);
void charToCode(HT ht);
int findMin(HT&ht,int n);
void HuffmanCode(HT ht,int n);
int main()
{
    cout<<"***********************************************************************************"<<endl;
    cout<<"****************** 1.输入HuffmanTree的参数.                        ****************"<<endl;
    cout<<"****************** 2.初始化HuffmanTree参数.<含有26字母及空格>      ****************"<<endl;
    cout<<"****************** 3.创建HuffmanTree和编码表.                      ****************"<<endl;
    cout<<"****************** 4.输出编码表.                                   ****************"<<endl;
    cout<<"****************** 5.输出编码，并翻译为字符.                       ****************"<<endl;
    cout<<"****************** 6.输入字符，并实现转码.                         ****************"<<endl;
    cout<<"****************** 7.退出.                                         ****************"<<endl;
    cout<<"***********************************************************************************"<<endl;
    int choice;
    HT ht;
    while(true)
    {
        cout<<"请输入选择:";
        cin>>choice;
        if(choice>0&&choice<8)
        {
            switch(choice)
            {
            case 1:
                inputArg();
                break;
            case 2:
                initArg();
                break;
            case 3:
                create(ht,27);
                break;
            case 4:
                printC(ht,27);
                break;
            case 5:
                codeToChar(ht);
                break;
            case 6:
                charToCode(ht);
                break;
            case 7:
                return 0;
            }
        }
    }
    return 0;
}
void inputArg()
{
    s="abcdefghijklmnopqrstuvwxyz ";
}
void initArg()
{
    int arr2[27]={64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 5, 32, 20, 57, 63, 15, 1, 48, 51, 80, 23, 8, 18, 1, 16, 1, 168};
    memcpy(arr,arr2,sizeof(arr2));
}
void create(HT&ht,int n)
{
    ht=(HT)malloc(sizeof(H)*(n*2));
    if(!ht)
        exit(-1);
    int weight,S1,S2;
    for(int i=1; i<=n; i++)
    {
        ht[i].ch=s[i-1];
        ht[i].weight=arr[i-1];
        ht[i].parent=ht[i].rc=ht[i].lc=0;
    }
    for(int i=n+1; i<2*n; i++)
    {
        S1=findMin(ht,i-1),S2=findMin(ht,i-1);
        ht[S1].parent=ht[S2].parent=i;
        ht[i].weight=ht[S1].weight+ht[S2].weight;
        ht[i].parent=0,ht[i].lc=S1,ht[i].rc=S2;
    }
}

int findMin(HT&ht,int n)
{
    int minElem=10000,s;
    for(int i=1; i<=n; i++)
        if(ht[i].weight<minElem && ht[i].parent==0)
            minElem=ht[i].weight,s=i;
    ht[s].parent=1;
    return s;
}

void printC(HT ht,int n)
{
    for(int i=1; i<=n; i++)
    {
        string cd;
        for(int j=i,f=ht[j].parent; f!=0; j=f,f=ht[f].parent)
        {
            if(ht[f].lc==j)
                cd+='0';
            else if(ht[f].rc==j)
                cd+='1';
        }
        reverse(cd.begin(),cd.end());
        hc[i]=cd;
        cout<<ht[i].ch<<":";
        cout<<hc[i]<<endl;
    }

}
void codeToChar(HT ht)
{
    string s1;
    fflush(stdin); //clear standard inputstream buffer,that's really important.
    getline(cin,s1);//getline allows string to be assigned a value with spaces. 
    for(int i=0; i<s1.length(); i++)
    {
        if(s1[i]==' ')
            cout<<hc[27];
        else
            cout<<hc[s1[i]-96];
    }
    cout<<endl;
}
void charToCode(HT ht)
{
    string s2;
    cin>>s2;
    for(int i=0; i<s2.length();)
    {
        int t=2*27-1;//from root to traverse
        while(ht[t].lc&&ht[t].rc)//lc and rc is exist,which indicates that it's not leaves node.then continue to cycle.
        {
            if(s2[i]=='0')
            {
                t=ht[t].lc;
                if(!ht[t].lc &&!ht[t].rc) cout<<ht[t].ch;
            }
            else
            {
                t=ht[t].rc;
                if(!ht[t].lc &&!ht[t].rc) cout<<ht[t].ch;
            }
            i++;//prepare for next cycle.
        }
    }
    cout<<endl;
}