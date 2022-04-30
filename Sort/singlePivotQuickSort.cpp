#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 100

void Random(int* a,int len);
void singlePivotQuickSort(int*a,int begin,int end);
int partition(int*a,int left,int right);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    singlePivotQuickSort(a,0,ARR_SIZE);
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
/**
 * 1.patition,based on pivot(the pivot is rightmost number by default) it is divided into two parts,left <= pivot,right > pivot.
 * 2.we use siglePivotQuickSort function to operate on these two parts separately.(begin,pivot's index-1) (pivot's index) (pivot's index +1,end)
 */ 
void singlePivotQuickSort(int*a,int begin,int end)
{
    if(begin<0||end<0||begin>=end) return;
    int middle = partition(a,begin,end);
    singlePivotQuickSort(a,begin,middle-1);
    singlePivotQuickSort(a,middle+1,end);
}
int partition(int*a,int left,int right)
{
    int pivot = a[right],leftptr = left,rightptr=right-1;
    while(leftptr<=rightptr)
    {
        while(leftptr<=rightptr&&a[leftptr]<=pivot) leftptr++;
        while(leftptr<=rightptr&&a[rightptr]>pivot) rightptr--;
        if(leftptr<rightptr) swap(a[leftptr],a[rightptr]);
    }
    //above cycle end array status: (left...rightptr) < (leftptr... ) right
    swap(a[leftptr],a[right]);
    return leftptr;
}