/**
 * 采用同一目录下的test.txt中的数据进行测试
 * 迷宫求解问题利用栈的特性进行回溯找到一条路，它可能不是最短路径，但一定是按照我们制定的顺序生成的路径。
 * 步骤：1.初始化迷宫
 *       2.输入入口和出口
 *       3.找到路径
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
FILE*fp;//设置一个存放数剧的文件。
#define MAXSIZE 25 //设立迷宫最大长度为25
typedef int MazeType[MAXSIZE][MAXSIZE]; //设立迷宫数据类型MazeType，其本质为二维数组
MazeType m;//设立迷宫数据类型的一个全局变量
int row, column;//迷宫的行和列，并且都为全局变量，省了传参的麻烦事。

//打印迷宫
void printMaze()
{
    for(int i = 0;i < row;i++)
    {
        for(int j = 0;j < column;j++)
            printf("%-3d",m[i][j]);
        printf("\n");
    }
    printf("\n");
}
/**
 * 初始化迷宫，墙为 0，1为可行走的单元格
 * 类似下面这种效果：
 * 初步初始状态
 * 0 0 0 0 0
 * 0 1 1 1 0
 * 0 1 1 1 0
 * 0 1 1 1 0
 * 0 0 0 0 0
 * 在迷宫内添加墙后的最终状态
 * 0 0 0 0 0
 * 0 1 1 1 0
 * 0 1 0 1 0
 * 0 1 0 1 0
 * 0 0 0 0 0
 * 初始化结束
 */
void InitMaze()
{
    //输入迷宫的行和列(包括外墙)
    fscanf(fp,"%d %d",&row,&column);//从文件中读取数据赋给变量
    //设立外墙为0
    for(int i = 0;i < column;i++)
    {
        m[0][i] = 0;//第一行为墙
        m[row-1][i] = 0;//最后一行为墙
    }
    for(int i = 0;i < row;i++)
    {
        m[i][0] = 0;//第一列为墙
        m[i][column-1] = 0;//最后一列为墙
    }
    //设立其余为1
    for(int i = 1;i < row-1;i++)
        for(int j = 1;j < column-1;j++)
            m[i][j] = 1;
    //效果类似于
    //0 0 0
    //0 1 0
    //0 0 0
    //这里结束迷宫的初步初始化
    //下面设置迷宫内的墙
    int num;//迷宫内的墙数
    //输入迷宫内墙的单元数;
    fscanf(fp,"%d",&num);
    //依次输入迷宫内墙的坐标;
    int x1, y1;
    for(int i = 0;i < num;i++)
    {
        fscanf(fp,"%d %d",&x1,&y1);
        m[x1][y1] = 0;
    }
    //效果类似于
    //0 0 0 0
    //0 1 0 0
    //0 1 1 0
    //0 0 0 0
    printf("迷宫结构如下:\n");
    printMaze();
}

typedef struct PosType
{
    int x;//行
    int y;//列
}PosType;//设立迷宫内坐标数据类型，由行和列组成，能够精准定位到一个位置
PosType dire[4] = {{0,1},{1,0},{0,-1},{-1,0}};//{行增量，列增量}，按照东南西北的顺序寻找路径
bool Pass(PosType t)//判断当前位置可否可通过
{
    if(1 == m[t.x][t.y])
        return true;
    else
        return false;
}

#define INIT_STACK_SIZE 10 //栈的初始容量
#define INCREASE 2 //栈的增量
typedef struct ElemType//栈内元素类型
{
    int ord;//通道块路径序号
    PosType pos;//通道块位置
    int di;//通道块走向下一通道块的方向，0~3表示东南西北
}ElemType;
typedef struct Stack
{
    ElemType * pbase;
    ElemType * ptop;
    int stackSize;
}S,*PS;
PS destroyStack(PS ps);
PS initStack(PS ps);
bool isEmpty(PS ps);
void push(PS ps,ElemType val);
ElemType pop(PS ps);

/**
 * 寻找按照我们规定顺序的从入口到出口的路径。
 */ 
bool MazePath(PosType entrance,PosType exit)
{
    PosType curPos = entrance;//当前位置在入口
    PS ps = NULL;
    ElemType e;//栈元素
    ps = initStack(ps);
    int curStep = 1;//当前足迹，开始时在入口处，初值为1
    do
    {
        if(Pass(curPos))//如果当前位置可以通过，留下足迹并将当前位置的信息压栈,curPos按照顺序变成下一个位置
        {
            m[curPos.x][curPos.y] = curStep;
            e.ord = curStep;//栈元素的序号为当前足迹
            e.pos = curPos;//栈元素的位置为当前位置
            e.di = 0;//从东开始，故下一位置的方向为东
            push(ps,e);
            if(curPos.x==exit.x && curPos.y==exit.y)//若到达终点
                return true;

            curStep++;//当前足迹加1
            //curPos按照顺序变成下一个位置。
            curPos.x += dire[e.di].x;
            curPos.y += dire[e.di].y;
        }
        else//如果当前位置不能通过，则回溯到前一位置，改变e.di，到下一位置，再进行判断。如果所有方向得到的下一个位置都不可通过，标记当前位置为-1再进行回溯
        {
            if(!isEmpty(ps))
            {
                e = pop(ps);//回溯到前一位置
                curStep--;
                while(e.di==3 && !isEmpty(ps))
                {
                    m[e.pos.x][e.pos.y] = -1;
                    e = pop(ps);
                    curStep--;
                }
                if(e.di < 3)//未到最后一个方向
                {
                    e.di++;
                    push(ps,e);//入栈该位置的下一个方向
                    curStep++;
                    curPos = e.pos;
                    curPos.x += dire[e.di].x;
                    curPos.y += dire[e.di].y;
                }
            }
        }
    } while (!isEmpty(ps));
    ps = destroyStack(ps);
    return false;
}

int main()
{
    fp = fopen("test.txt","r");
    if(fp)
    {
        printf("打开文件成功.\n");
    }
    else
    {
        printf("打开文件失败.\n");
        exit(-1);
    }
    InitMaze();//初始化迷宫
    PosType entrance, exit;//迷宫的入口处和出口处
    // 输入入口的坐标;
    fscanf(fp,"%d %d",&entrance.x,&entrance.y);
    //输入出口的坐标;
    fscanf(fp,"%d %d",&exit.x,&exit.y);
    if(MazePath(entrance,exit))
    {
        printf("存在路径:\n");
        printMaze();
    }
    else
    {
        printf("路径不存在.\n");
    }
    return 0;
}
/**
结果如下:
迷宫结构如下:
0  0  0  0  0  0  0  0  0  0  
0  1  1  0  1  1  1  0  1  0  
0  1  1  0  1  1  1  0  1  0  
0  1  1  1  1  0  0  1  1  0  
0  1  0  0  0  1  1  1  1  0  
0  1  1  1  0  1  1  1  1  0  
0  1  0  1  1  1  0  1  1  0
0  1  0  0  0  1  0  0  1  0
0  0  1  1  1  1  1  1  1  0
0  0  0  0  0  0  0  0  0  0

存在路径:
0  0  0  0  0  0  0  0  0  0
0  1  2  0  -1 -1 -1 0  1  0
0  1  3  0  -1 -1 -1 0  1  0
0  5  4  -1 -1 0  0  1  1  0
0  6  0  0  0  1  1  1  1  0
0  7  8  9  0  1  1  1  1  0
0  1  0  10 11 12 0  1  1  0
0  1  0  0  0  13 0  0  1  0
0  0  1  1  1  14 15 16 17 0
0  0  0  0  0  0  0  0  0  0
*/
PS destroyStack(PS ps)
{
    free(ps->pbase);
    free(ps);
    return NULL;
}
PS initStack(PS ps)
{
    if(ps)
    {
        ps = destroyStack(ps);
    }
    ps = (PS)malloc(sizeof(S));
    if(NULL == ps)
    {
        printf("Dynamic malloc failed.\n");
        exit(-1);
    }
    else
    {
        ps->pbase = (ElemType*)malloc(sizeof(ElemType)*INIT_STACK_SIZE);
        if(NULL == ps->pbase)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps->ptop = ps->pbase;
        ps->stackSize = INIT_STACK_SIZE;
    }
    return ps;
}
bool isEmpty(PS ps)
{
    if(ps->pbase == ps->ptop)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void push(PS ps,ElemType val)
{
    if((ps->ptop - ps->pbase) == ps->stackSize)
    {
        ps->pbase = (ElemType*)realloc(ps->pbase, sizeof(ElemType)*((ps->ptop - ps->pbase)+INCREASE));
        if(NULL == ps->pbase)
        {
            printf("Dynamic malloc failed.\n");
            exit(-1);
        }
        ps->ptop = (ps->ptop - ps->pbase) + ps->pbase;
    }
    *(ps->ptop) = val;
    ps->ptop++;
}
ElemType pop(PS ps)
{
    ps->ptop--;
    return *(ps->ptop);
}
