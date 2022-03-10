/**
 * @author OMNSP
 * @aim 简单顺序存储结构的的创建和遍历
 */
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
typedef struct ArrayList
{
    int data;
}A,*PA;
PA ConstructArrayList(int len);
void TraverseArrayList(PA PArr, int len);
PA FreeArrayList(PA PArr);
int main()
{
    int len = 0;
    printf("请输入你想要构造元素的个数：");
    scanf("%d",&len);
    PA PArr = ConstructArrayList(len);
    TraverseArrayList(PArr,len);
    PArr = FreeArrayList(PArr);
    return 0;
}
PA ConstructArrayList(int len)
{
    int val = 0;
    PA PArr = (PA)malloc(sizeof(A)*len);
    if (NULL == PArr)
    {
        printf("Dynamic memory allocation failed.\n");
        exit(-1);
    }
    for ( int i = 0;i < len;i++)
    {
        printf("请为第%d个元素赋值:",i+1);
        scanf("%d",&val);
        PArr[i].data = val;
    }
    return PArr;
}
void TraverseArrayList(PA PArr,int len)
{
     for(int i = 0;i < len;i++)
     {
        printf("%d ",PArr[i].data);   
     }
     printf("\n");
}
PA FreeArrayList(PA PArr)
{
    free(PArr);
    return NULL;
}
