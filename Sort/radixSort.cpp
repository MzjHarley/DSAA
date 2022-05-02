/**
 * Count sorting is a non-comparative sort, using the technique of ordering the array subscript, which is a kind of bucket idea; 
 */
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
#define ARR_SIZE 100

void Random(int* a,int len);
void radixSort(int*a,int len);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    radixSort(a,ARR_SIZE);
    print(a,ARR_SIZE);
    return 0;
}
void Random(int* a,int len)
{
    srand(time(0));//set time seed
    for (int i = 0; i < len; i++)
        a[i]=rand()%100+1;//1~100
    
}
void print(int* a,int len)
{
    for (int i = 0; i < len; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
void radixSort(int*a,int len)
{
    int digit=1+log10(*max_element(a,a+len)),count[10]={0},temp[len];
    for(int i=0;i<digit;i++)
    {
        int division=pow(10,i);
        for(int j=0;j<len;j++) count[a[j]/division%10]++; //count low pos to high pos's occurence.
        for(int k=1;k<10;k++)  count[k]+=count[k-1];      //accumulate array count to get number's position.
        for(int m=len-1;m>=0;m--) {int& pos=count[a[m]/division%10];temp[--pos]=a[m];}//reverse operation ensures the array's stablity.
        memcpy(a,temp,sizeof(temp));// copy array temp to array a.
        memset(count,0,sizeof(count));//initial count array 0 to ensure next cycle to be correct.
    }
}
