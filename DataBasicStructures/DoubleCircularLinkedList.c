/**
 * ˫��ѭ������ĸ߼�����
 * ˫��ѭ����������˼�壺��һ��˫������ͬʱ��һ��ѭ������
 * ˫��ѭ������Ĳ���:��ʼ������գ����٣��ж��Ƿ�Ϊ�գ��õ����ȣ��õ�ĳ��λ�õ�Ԫ�أ��õ�ĳ��Ԫ�ص�λ�ã�λ��ǰ��ֵǰ����ֵǰ����
 * λ�ú�̣�ֵ��̣�λ�ò��룬ֵ���룬λ��ɾ����ֵɾ�������������򣬵ߵ����.��Լ17��������
 */
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
typedef struct Node
{
    struct Node* left;
    int data;
    struct Node* right;
}N,*PN;
PN initDoubleCircularLinkedList(PN phead);
PN destroyDoubleCircularLinkedList(PN phead);
void clearDoubleCircularLinkedList(PN phead);
bool isEmpty(PN phead);
int getLength(PN phead);
void getElem(PN phead);
int getElemPos(PN phead, int val);
void getPrior(PN phead);
void getPost(PN phead);
bool insertDoubleCircularLinkedList(PN phead);
bool deleteDoubleCircularLinkedList(PN phead);
void reverseTraverse(PN phead);
void sortDoubleCircularLinkedList(PN phead);
void traverseDoubleCircularLinkedList(PN phead);
int main()
{
    printf("***************************************\n");
    printf("*  1.initDoubleCircularLinkedList      *\n");
    printf("*  2.destroyDoubleCircularLinkedList   *\n");
    printf("*  3.Empty Or Not                      *\n");
    printf("*  4.insertDoubleCircularLinkedList    *\n");
    printf("*  5.deleteDoubleCircularLinkedList    *\n");
    printf("*  6.clearDoubleCircularLinkedList     *\n");
    printf("*  7.traverseDoubleCircularLinkedList  *\n");
    printf("*  8.sortDoubleCircularLinkedList      *\n");
    printf("*  9.getElem                           *\n");
    printf("* 10.getElemPos                       *\n");
    printf("* 11.getPrior                         *\n");
    printf("* 12.getPost                          *\n");
    printf("* 13.reverseTraverse                  *\n");
    printf("* 14.getLength                        *\n");
    printf("***************************************\n");
    char str;
    int num;
    int pos;
    int val;
    PN phead=NULL;;
    do
    {
        printf("Input Operand:");
        scanf("%d",&num);
        switch(num)
        {
        case 1:
            phead = initDoubleCircularLinkedList(phead); 
            break;
        case 2:
            phead = destroyDoubleCircularLinkedList(phead);
            break;
        case 3:
            if(NULL == phead)
            {
                printf("phead is NULL.\n");
            }
            else
            {
                if(isEmpty(phead))
                {
                    printf("Empty.\n");
                }
                else
                {
                    printf("Not Empty.\n");
                }
            }
            break;
        case 4:
            insertDoubleCircularLinkedList(phead);
            break;
        case 5:
            deleteDoubleCircularLinkedList(phead);
            break;
        case 6:
            clearDoubleCircularLinkedList(phead);
            break;
        case 7:
            traverseDoubleCircularLinkedList(phead);
            break;
        case 8:
            sortDoubleCircularLinkedList(phead);
            break;
        case 9:
            getElem(phead);
            break;
        case 10:
            printf("����������Ҫ��ѯ��ֵ:");
            scanf("%d",&val);
            getElemPos(phead,val);
            break;
        case 11:
            getPrior(phead);
            break;
        case 12:
            getPost(phead);
            break;
        case 13:
            reverseTraverse(phead);
            break;
        case 14:
            printf("������Ϊ:%d\n",getLength(phead));
            break;
        }
        printf("Continue Or Not(Y/N):");
        scanf(" %c",&str);
    }while(str=='Y' || str=='y');
    return 0;
}
PN initDoubleCircularLinkedList(PN phead)
{
    if(phead)
    {
        phead = destroyDoubleCircularLinkedList(phead);
    }
    int option;
    printf("1.�Զ���ڵ��ʼ����2.���Զ���ڵ��ʼ��.���������ѡ��:");
    scanf("%d",&option);
    if(1 == option)
    {
        phead = (PN)malloc(sizeof(N));
        if(NULL == phead)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        phead->left = phead->right = phead;
        PN ptail = phead;
        int num, val;
        printf("����������Ҫ����Ľڵ���:");
        scanf("%d",&num);
        for(int i = 1;i < num+1;i++)
        {
            printf("��Ϊ��%d���ڵ㸳ֵ:",i);
            scanf("%d",&val);
            PN pnew =(PN)malloc(sizeof(N));
            if(NULL == phead)
            {
                printf("Dynamic malloc failed.\n");
                exit(-1);
            }
            pnew->left = NULL;
            pnew->data = val;
            pnew->right = phead; //���ﲻ��ʼ��ΪNULL�����������ӽڵ�ʱʡһ��

            phead->left = pnew;
            ptail->right = pnew;
            pnew->left = ptail;
            ptail = pnew;
        }
        return phead;
    }
    else if(2 == option)
    {
        phead = (PN)malloc(sizeof(N));
        if(NULL == phead)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        phead->left = phead;
        phead->right = phead;
        return phead;
    }
    else
    {
        printf("option error.\n");
        return NULL;
    }
}
PN destroyDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return NULL;
    }
    clearDoubleCircularLinkedList(phead);
    free(phead);
    return NULL;
}
void clearDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    PN p = phead->right;
    while(p != phead)
    {
        PN q = p->right;
        free(p);
        p = q;
    }
    phead->left = phead->right = phead;
}
bool isEmpty(PN phead)
{
    if(phead->right==phead && phead->left==phead)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int getLength(PN phead)
{
    if(NULL == phead)
    {
        return 0;
    }
    if(isEmpty(phead))
    {
        return 0;
    }
    int length = 0;
    PN p = phead->right;
    while(p != phead)
    {
        length++;
        p = p->right;
    }
    return length;
}
void getElem(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return;
    }
    int pos;
    printf("����������Ҫ����Ԫ�ص�λ��:");
    scanf("%d",&pos);
    if(pos<1 || pos>getLength(phead))
    {
        printf("λ�ô���.\n");
        return;
    }
    int i = 1;
    PN p = phead->right;
    while(i < pos)
    {
        i++;
        p = p->right;
    }
    printf("��%d��λ�õ�Ԫ��Ϊ%d\n",pos,p->data);
}
int getElemPos(PN phead, int val)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return 0;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return 0;
    }
    int times = 0;
    int i = 1;
    PN p = phead->right;
    printf("����Ԫ�ص�λ������Ϊ:");
    while(p != phead)
    {
        if(p->data == val)
        {
            times++;
            printf("%d ",i);
        }
        i++;
        p = p->right;
    }
    if(0 == times)
    {
        printf("none");
    }
    else
    {
        printf(",������%d��.",times);
    }
    printf("\n");
    return times;
}
void getPrior(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return;
    }
    int option;
    printf("1.λ��ǰ����2.ֵǰ��;���������ѡ��:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("����������ҪѰ��ǰ����λ��:");
        scanf("%d",&pos);
        if(pos<2 || pos>getLength(phead))
        {
            printf("��ǰ��.\n");
            return;
        }
        int i = 1;
        PN p = phead->right;
        while(i < pos)
        {
            i++;
            p = p->right;
        }
        printf("��%d��λ�õ�ǰ��Ϊ%d.\n",pos,p->left->data);
    }
    else if(2 == option)
    {
        int val;
        printf("����������ҪѰ��ǰ����ֵ:");
        scanf("%d",&val);
        printf("ǰ������Ϊ:");
        int times = 0;
        PN p = phead->right->right;
        while (p != phead)
        {
            if(p->data == val)
            {
                times++;
                printf("%d ",p->left->data);
            }
            p = p->right;
        }
        if (0 == times)
        {
            printf("none.");
        }
        printf("\n");
    }
    else
    {
        printf("option error");
    }
}
void getPost(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("List is empty.\n");
        return;
    }
    int option;
    printf("1.λ�ú�̣�2.ֵ���;���������ѡ��:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("����������ҪѰ�Һ�̵�λ��:");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(phead)-1)
        {
            printf("�޺��.\n");
            return;
        }
        int i = 1;
        PN p = phead->right;
        while(i < pos)
        {
            i++;
            p = p->right;
        }
        printf("��%d��λ�õ�ǰ��Ϊ%d.\n",pos,p->right->data);
    }
    else if(2 == option)
    {
        int val;
        printf("����������ҪѰ�Һ�̵�ֵ:");
        scanf("%d",&val);
        printf("�������Ϊ:");
        int times = 0;
        PN p = phead->right;
        while (p!=phead && p->right!=phead)
        {
            if(p->data == val)
            {
                times++;
                printf("%d ",p->right->data);
            }
            p = p->right;
        }
        if (0 == times)
        {
            printf("none.");
        }
        printf("\n");
    }
    else
    {
        printf("option error");
    }
}
bool insertDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return false;
    }
    printf("����ǰ:");
    traverseDoubleCircularLinkedList(phead);
    int option;
    printf("1.λ�ò��룬2.ֵ����;���������ѡ��:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("����������Ҫ�����λ��:");
        scanf("%d",&pos);
        if(pos<1 || pos>getLength(phead)+1)
        {
            printf("λ�ô���.\n");
            return false;
        }
        int val;
        printf("����������Ҫ�����ֵ:");
        scanf("%d",&val);
        int i = 0;
        PN p = phead;
        while(i < pos-1)
        {
            i++;
            p = p->right;
        }
        PN pnew = (PN)malloc(sizeof(N));
        if(NULL == pnew)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        pnew->left = pnew->right = NULL;
        pnew->data = val;
        
        pnew->right = p->right;
        pnew->left = p;
        p->right->left = pnew;
        p->right = pnew;
        printf("�����:");
        traverseDoubleCircularLinkedList(phead);
        return true;
    }
    else if(2 == option)
    {
        int val;
        printf("�������ֵ:");
        scanf("%d",&val);
        if(0 == getElemPos(phead,val))
        {
            printf("�����ڸ�ֵ.\n");
            return false;
        }
        int option2;
        printf("1.�����ڸ�ֵǰ�棬2.�����ڸ�ֵ����;���������ѡ��:");
        scanf("%d",&option2);
        int val1;
        printf("��������Ҫ�����ֵ:");
        scanf("%d",&val1);
        if(1 == option2)
        {
            int times = 0;
            PN p = phead;
            while(p->right != phead)
            {
                if(p->right->data == val)
                {
                    times++;
                    PN pnew = (PN)malloc(sizeof(N));
                    if(NULL == pnew)
                    {
                        printf("Dynamic malloc failed.\n");
                        exit(-1);
                    }
                    pnew->left = pnew->right = NULL;
                    pnew->data = val1;

                    pnew->right = p->right;
                    pnew->left = p;
                    p->right->left = pnew;
                    p->right = pnew;
                    p = pnew;
                }
                p=p->right;
            }
            if(0 == times)
            {
                printf("�����ڸ�ֵ.\n");
                return false;
            }
            printf("�����:");
            traverseDoubleCircularLinkedList(phead);
            return true;
        }
        else if(2 == option2)
        {
            int times = 0;
            PN p = phead->right;
            while(p != phead)
            {
                if(p->data == val)
                {
                    times++;
                    PN pnew = (PN)malloc(sizeof(N));
                    if(NULL == pnew)
                    {
                        printf("Dynamic malloc failed.\n");
                        exit(-1);
                    }
                    pnew->left = pnew->right = NULL;
                    pnew->data = val1;

                    pnew->right = p->right;
                    pnew->left = p;
                    p->right->left = pnew;
                    p->right = pnew;
                    p = pnew;
                }
                p = p->right;
            }
            if(0 == times)
            {
                printf("�����ڸ�ֵ.\n");
                return false;
            }
            printf("�����:");
            traverseDoubleCircularLinkedList(phead);
            return true;
        }
        else
        {
            printf("option error.\n");
            return false;
        }
    }
    else
    {
        printf("option error");
        return false;
    }
}
bool deleteDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return false;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return false;
    }
    printf("ɾ��ǰ:");
    traverseDoubleCircularLinkedList(phead);
    int option;
    printf("1.λ��ɾ����2.ֵɾ��;���������ѡ��:");
    scanf("%d",&option);
    if(1 == option)
    {
        int pos;
        printf("����������Ҫɾ����λ��:");
        scanf("%d",&pos);
        int val;
        if(pos<1 || pos>getLength(phead))
        {
            printf("λ�ô���.\n");
            return false;
        }
        int i = 0;
        PN p = phead;
        while(i < pos-1)
        {
            i++;
            p = p->right;
        }
        PN q = p->right;
        p->right = q->right;
        q->right->left = p;
        free(q);
        printf("ɾ����:");
        traverseDoubleCircularLinkedList(phead);
        return true;
    }
    else if(2 == option)
    {
        int val;
        printf("�������ֵ:");
        scanf("%d",&val);
        int times = 0;
        PN p = phead;
        while(p->right != phead)
        {
            if(p->right->data == val)
            {
                times++;
                PN q = p->right;
                p->right = q->right;
                q->right->left = p;
                free(q);
            }
            else
            {
                p = p->right;
            }
        }
        if(0 == times)
        {
            printf("�����ڸ�ֵ.\n");
            return false;
        }
        printf("ɾ����:");
        traverseDoubleCircularLinkedList(phead);
        return true;
    }
    else
    {
        printf("option error.\n");
        return false;
    }
}
void traverseDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return;
    }
    PN p = phead->right;
    while(p != phead)
    {
        printf("%d ",p->data);
        p = p->right;
    }
    printf("\n");
}
void reverseTraverse(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return;
    }
    PN p = phead->left;
    while(p != phead)
    {
        printf("%d ",p->data);
        p = p->left;
    }
    printf("\n");
}
void sortDoubleCircularLinkedList(PN phead)
{
    if(NULL == phead)
    {
        printf("phead is NULL.\n");
        return;
    }
    if(isEmpty(phead))
    {
        printf("It's empty.\n");
        return;
    }
    PN pre,p;
    for(int i = 0;i < getLength(phead)-1;i++)
    {
        pre = phead;
        p = pre->right;
        while(p!=phead && p->right!=phead)
        {
            PN q = p->right;
            if(p->data > q->data)
            {
                pre->right = q;
                q->left = pre;
                p->left = q;
                p->right = q->right;
                q->right->left = p;
                q->right = p;
            }
            pre = pre->right;
            p = pre->right;
        }
    }
}