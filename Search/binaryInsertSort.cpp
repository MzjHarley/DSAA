#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>

using namespace std;
#define ARR_SIZE 30

void Random(int* a,int len);
bool binarySearch(int*a,int len,int n);
void print(int* a,int len);

int main()
{
    int a[ARR_SIZE],n;
    Random(a,ARR_SIZE);
    sort(a,a+ARR_SIZE);//binarySearch require the array  to be ordered.
    print(a,ARR_SIZE);
    cin>>n;
    if(binarySearch(a,ARR_SIZE,n)) cout<<"Exist"<<endl;
    else cout<<"Not Exist."<<endl;
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
    for(int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
bool binarySearch(int*a,int len,int n)
{
    int left=0,right=len-1;
    while (left<=right)
    {
        int middle=(left+right)/2;
        if(a[middle]==n) return true;
        else if(a[middle]<n) left=middle+1;
        else right=middle-1;
    }
    return false;
}