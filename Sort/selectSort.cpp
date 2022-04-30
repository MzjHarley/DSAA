#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 30

void Random(int* a,int len);
void selectSort(int*a,int len);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    selectSort(a,ARR_SIZE);
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
void selectSort(int*a,int len)
{
    for (int  i = 0; i < len-1; i++)//len-1 times traverse,every traverse get a minNumber.
    {
        int minpos=i;
        for (int j = i+1; j < len; j++)
            minpos=a[j]<a[minpos]?j:minpos;
        swap(a[i],a[minpos]);
    }
}
