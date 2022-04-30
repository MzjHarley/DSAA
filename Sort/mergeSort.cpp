#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 100

void Random(int* a,int len);
void mergeSort(int*a,int begin,int end);
void merge(int*a,int begin,int middle,int end);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    mergeSort(a,0,ARR_SIZE);
    print(a,ARR_SIZE);
    return 0;
}
void Random(int* a,int len)
{
    srand(time(0));//set time seed
    for (int i = 0; i < len; i++)
        a[i]=rand()%10000+1;//1~100
    
}
void print(int* a,int len)
{
    for (int i = 0; i < len; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
void mergeSort(int*a,int begin,int end)
{
    if(begin>=end||begin<0||end<0) return;
    int middle=(begin+end)/2;
    mergeSort(a,begin,middle);
    mergeSort(a,middle+1,end);
    merge(a,begin,middle,end);
}
void merge(int*a,int begin,int middle,int end)
{
    int temp[end-begin+1];// assist array.
    int left = begin,right=middle+1,cnt=0;
    while(left<=middle&&right<=end) temp[cnt++]=a[left]<=a[right]?a[left++]:a[right++];
    while(left<=middle) temp[cnt++]=a[left++];
    while(right<=end) temp[cnt++]=a[right++];
    for(int i=0;i<end-begin+1;i++) a[i+begin]=temp[i];
}