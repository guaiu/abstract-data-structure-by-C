#include <stdio.h>
#include <stdlib.h>

/*************************************/
/*用队列求解迷宫问题（最短路径）     *
 *给定一个M×N的迷宫图、入口与出口、  *
 *行走规则。求一条从指定入口到出口的 *
 *路径。所求路径必须是最短路径。     */
/*************************************/

/*       迷宫举例       */
/*int mg[10][10]= { 
 {1, 1,1,1,1,1,1,1,1, 1},
 
 {1, 0,0,1,0,0,0,1,0, 1}, 
 {1, 0,0,1,0,0,0,1,0, 1}, 
 {1, 0,0,0,0,1,1,0,0, 1}, 
 {1, 0,1,1,1,0,0,0,0, 1}, 
 {1, 0,0,0,1,0,0,0,0, 1}, 
 {1, 0,1,0,0,0,1,0,0, 1}, 
 {1, 0,1,1,1,0,1,1,0, 1}, 
 {1, 1,0,0,0,0,0,0,0, 1}, 

{1, 1,1,1,1,1,1,1,1, 1}
 };                       */
/*                        */

#define MaxSize 64
#define MaxCol 10

typedef struct
{
	int i,j;             //方块位置
	int pre;             //本路径中上一方块在队列中的下标
}Box,ElemType;                    //方块类型
typedef struct
{
	Box data[MaxSize];
	int front,rear;
}SqQueue;                //顺序队类型

/*InitQueue:初始化队列*/
void InitQueue(SqQueue *&q)
{
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = -1;
}

/*enQueue:进队*/
bool enQueue(SqQueue *&q, ElemType e)
{
	if(q->rear == MaxSize-1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

/*deQueue:出队*/
bool deQueue(SqQueue *&q, ElemType &e)
{
	if(q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

/*PathPrint:打印迷宫路径*/
void PathPrint(SqQueue *q, ElemType TheEnd)
//因为需要从终点回溯到起点，所以建立一个栈来作为辅助工具
{
	Box Path[MaxSize];           //栈工具
	int top = -1;
	
	Box e = TheEnd;
	while(e.pre != -1)           //将路径入栈
	{
		top++;
		Path[top] = e;
		e = q->data[e.pre];
	}
	top++;Path[top] = e;         //入口入栈
	
	int count = 0;
	printf("迷宫路径如下：\n");  //出栈
	while(top != -1)
	{
		printf("\t(%d,%d)",Path[top].i, Path[top].j);
		top--; count++;
		if(count == 5){printf("\n"); count = 0;}
	}
}

/*mgpath:求解最短路径迷宫算法*/
bool mgpath(int xi, int yi, int xe, int ye, int (*mg)[MaxCol])
//搜索路径为：(xi, yi)->(xe,ye)
{
	SqQueue *q;
	InitQueue(q);                           //定义顺序队
	Box e; e.i = xi; e.j = yi; e.pre = -1;  
	enQueue(q,e);                            //(xi,yi)进队
	mg[xi][yi] = -1;                  //入口迷宫值设为-1，
	                                  //避免重复搜索
									  
									  
	int i, j;          //记录尝试坐标
	int di;            //记录尝试方位
	int find = 0;      //标记状态
	Box e2;            //临时变量
	while(q->front != q->rear && !find)  //队列不空循环
	{
		deQueue(q,e);              //出队
		i = e.i; j = e.j;          //记录当前坐标
		if(i == xe && j == ye)//找到出口，输出路径
		{
			find = 1;
		    PathPrint(q,e);
			return true;
		}
		for(di = 0; di < 4; di++)  //把当前出队方块每个相邻可走方块入队
		{
			switch(di)
			{
				case 0: i = e.i-1; j = e.j; break;
				case 1: i = e.i; j = e.j+1; break;
				case 2: i = e.i+1; j = e.j; break;
				case 3: i = e.i; j = e.j-1; break;
			}
			if(mg[i][j] == 0)
			{
				e2.i = i; e2.j = j; e2.pre = q->front;  //生成入队元素
				enQueue(q,e2);                         //入队
				mg[i][j] = -1;                         //修改迷宫值
			}
		}
	}
	return false;  //未找到任何路径返回false
}

/*测试主函数:直接测试某个迷宫*/
int main()
{
	int mg[MaxCol][MaxCol]= { 
{1,1,1,1,1,1,1,1,1,1},
{1,0,0,1,0,0,0,1,0,1}, 
{1,0,0,1,0,0,0,1,0,1}, 
{1,0,0,0,0,1,1,0,0,1}, 
{1,0,1,1,1,0,0,0,0,1}, 
{1,0,0,0,1,0,0,0,0,1}, 
{1,0,1,0,0,0,1,0,0,1}, 
{1,0,1,1,1,0,1,1,0,1}, 
{1,1,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1}
 };

    if(!mgpath(1,1,8,8,mg))
        printf("该迷宫问题没有解！");	
    return 0;	
}