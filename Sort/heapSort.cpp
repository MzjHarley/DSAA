#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 30

void Random(int* a,int len);
void heapSort(int*a,int len);
void heapify(int*a,int i,int heapsize);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    heapSort(a,ARR_SIZE);
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
//before we start heapSort,we need to convert the array to completely binary tree. It's a logical transformation.
//heap is completely binary tree.
//for example ,array :1 5 6 8 9
//completely binary tree:
//             1
//            / \
//           5   6
//          / \
//         8   9  
// father:i, left child: 2*i+1, right child:2*i+2
// when we start heapSort,we need to know every time it will return a max ,just like bubbleSort. That means every time it's adjusted to a large root heap.
//we divide the array into two parts[ [heap to be adjusted],...,max2,max1 ]
void heapSort(int*a,int len)
{
    if(len<2) return;
    int heapsize=len;//heap 's size.
    for(int i=len-1;i>=0;i--)
        heapify(a,i,heapsize); // adjust heap to be a large root heap;
    // why do we start form len-1 instead of  0? You can use [1 5 6 8 9] to try it.And you will see it.Focus on the two ways'difference.
    swap(a[0],a[--heapsize]);//[(heapsize-1),max]
    while(heapsize>0)
    {
        heapify(a,0,heapsize);//adjust heap to be a large root heap from index 0, because a[0] destroy the large root heap. 
        swap(a[0],a[--heapsize]);
    }
}
// heapify is used to adjust heap to be a large root heap.
void heapify(int*a,int i,int heapsize)
{
    int lc=i*2+1;
    while(lc<heapsize)
    {
        int larger = (lc+1<heapsize)&&(a[lc+1]>a[lc])?lc+1:lc;
        int largest = a[larger]<a[i]?i:larger;
        //get max'index.
        if(i==largest) break;
        else swap(a[i],a[largest]);
        // continue to adjust the heap downwards.
        i = largest;
        lc= i*2+1;
    }
}