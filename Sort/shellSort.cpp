/**
 * that's an alternative embodiment of insertSort 
 */ 
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 100

void Random(int* a,int len);
void shellSort(int*a,int len);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    shellSort(a,ARR_SIZE);
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
void shellSort(int*a,int len)
{
    int increase=1;
    while(increase<len/3)//3*increase+1<=len -> increase<=(len-1)/3 -> increase<len/3
        increase=3*increase+1;//confirm the biggest increase
    for (int gap = increase;gap>0;gap=(gap-1)/3)//shrink increase.
        for (int i = gap; i < len; i++)//start from gap to len-1, insertSort the number spaced gap apart.
            for (int j = i; j>gap-1&&a[j]<a[j-gap]; j-=gap)//j-gap>=0 -> j>=gap -> j>gap-1 ,the fore array spaced gap apart is ordered
                swap(a[j],a[j-gap]);
}