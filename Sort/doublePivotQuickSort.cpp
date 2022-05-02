#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 20

void Random(int* a,int len);
void doublePivotQuickSort(int*a,int begin,int end);
void partition(int*a,int pivot1,int pivot2,int& leftptr,int middle,int& rightptr);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    doublePivotQuickSort(a,0,ARR_SIZE-1);
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
void doublePivotQuickSort(int*a,int begin,int end)
{
    if(begin<0||end<0||begin>=end) return;
    if(a[begin]>a[end]) swap(a[begin],a[end]);//we rule that left pivot must be less than right pivot.
    int leftptr=begin,middle=leftptr+1,rightptr=end,pivot1=a[begin],pivot2=a[end];
    partition(a,pivot1,pivot2,leftptr,middle,rightptr);//the function will divide array into three parts:(begin, leftptr-1) leftptr (leftptr+1,rightptr-1) rightptr (rightptr+1,end)
    doublePivotQuickSort(a,begin,leftptr-1);
    doublePivotQuickSort(a,leftptr+1,rightptr-1);
    doublePivotQuickSort(a,rightptr+1,end);
}
void partition(int*a,int pivot1,int pivot2,int& leftptr,int middle,int& rightptr)
{
    int left=leftptr,right=rightptr;//save the two pivot's index to swap with leftptr and rightptr.
    // we can use the example:5 1 2 3 6 7 1 18 8 10 11 9 to understand the follow cycle
    while (middle<rightptr)
    {
        if(a[middle]<=pivot1) swap(a[++leftptr],a[middle++]);
        else if(a[middle]<=pivot2) middle++;
        else//a[middle]>pivot2
        {
            while(a[--rightptr]>pivot2) if(rightptr<=middle) goto here;//>pivot2, rightptr move the left.
            if(a[rightptr]<=pivot1) {swap(a[rightptr],a[middle]);swap(a[++leftptr],a[middle++]);}
            else swap(a[middle++],a[rightptr]);
        }
    }
    here:
    swap(a[left],a[leftptr]);
    swap(a[rightptr],a[right]);   
}