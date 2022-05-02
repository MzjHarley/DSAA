/**
 * Count sorting is a non-comparative sort, using the technique of ordering the array subscript, which is a kind of bucket idea; 
 * It is used for large but small range data sorting, such as the age ranking of employees in a large enterprise, and quickly know your college entrance examination ranking
 */

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>

using namespace std;
#define ARR_SIZE 30

void Random(int* a,int len);
void countSort(int*a,int len);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    countSort(a,ARR_SIZE);
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
void countSort(int*a,int len)
{
    int max=*max_element(a,a+len),min=*min_element(a,a+len),count[max-min+1]={0},temp[len];  
    //int *std::min_element<int *>(int *, int *) return min's address.  int *std::max_element<int *>(int *, int *) return max's address. need include <algorithm>
    for(int i=0;i<len;i++) count[a[i]-min]++;//count the number's occurence.
    for(int i=1;i<max-min+1;i++) count[i]+=count[i-1];//accumulate the count array to get number's position (from 1).
    for(int i=len-1;i>=0;i--) {int& pos=count[a[i]-min]; temp[--pos]=a[i];} //reverse operation to ensure the array stablity.
    memcpy(a,temp,sizeof(temp));//void *memcpy(void *__restrict__ _Dst, const void *__restrict__ _Src, size_t _MaxCount),array copy.
}
