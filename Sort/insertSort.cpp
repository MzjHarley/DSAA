#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 30

void Random(int* a,int len);
void insertSort(int*a,int len);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    insertSort(a,ARR_SIZE);
    print(a,ARR_SIZE);
    return 0;
}
void Random(int* a,int len)
{
    srand(time(0));//set time seed
    for (int i = 0; i < len; i++)
        a[i]=rand()%30+1;//1~100
}
void print(int* a,int len)
{
    for (int i = 0; i < len; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
void insertSort(int*a,int len)
{
    for(int i=0;i<len-1;i++)//len-1 times traverse,every traverse insert Number into right position.
        for(int j=i+1;j>0&&a[j]<a[j-1];j--)//the fore array is ordered.
            swap(a[j],a[j-1]);
}