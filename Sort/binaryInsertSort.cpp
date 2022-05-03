#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
#define ARR_SIZE 30

void Random(int* a,int len);
void binaryInsertSort(int*a,int len);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE];
    Random(a,ARR_SIZE);
    binaryInsertSort(a,ARR_SIZE);
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
void binaryInsertSort(int*a,int len)
{
    for(int i=1;i<len;i++)
    {
        int left=0,right=i-1,temp=a[i];//[(left,right) temp],temp will be inserted in (left,right).
        while(left<=right)
        {
            int middle=(left+right)/2;
            a[middle]<=temp?left=middle+1:right=middle-1;//a[middle]<=a[i] ensure the array's stablity.
        }//right+1 is the a[i]'s position. we can use 1 2 3 2 to explain it. 
        //Also the last cycle is left=right,then the cycle will stop,but right+1(left) is always the element's insert position. 
        for(int j=i-1;j>=right+1;j--) a[j+1]=a[j];
        a[right+1]=temp;
    }
}