#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 20

void Random(int* a,int len);
void singlePivotQuickSort(int*a,int begin,int end);
void partition(int*a,int pivot,int &leftptr,int rightptr);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    singlePivotQuickSort(a,0,ARR_SIZE-1);
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
 * 2.we use siglePivotQuickSort function to operate on these two parts separately.(begin,leftptr-1) (leftptr) (leftptr+1,end)
 */ 
void singlePivotQuickSort(int*a,int begin,int end)
{
    if(begin<0||end<0||begin>=end) return;
    int pivot = a[end],leftptr = begin,rightptr=end-1;
    partition(a,pivot,leftptr,rightptr);
    singlePivotQuickSort(a,begin,leftptr-1);
    singlePivotQuickSort(a,leftptr+1,end);
}
void partition(int*a,int pivot,int& leftptr,int rightptr)
{
    int right = rightptr+1;//right is pivot's index.
    while(leftptr<=rightptr)
    {
        while(leftptr<=rightptr&&a[leftptr]<=pivot) leftptr++;
        while(leftptr<=rightptr&&a[rightptr]>pivot) rightptr--;
        if(leftptr<rightptr) swap(a[leftptr],a[rightptr]);
    }
    //above cycle end array status: (left,rightptr)  (leftptr,right-1) right
    // rightptr = leftptr-1;
    swap(a[leftptr],a[right]);
    //now the array status :(left,rightptr) leftptr(is pivot) (leftptr+1,right)
}
