#include <stdio.h>
#include <stdlib.h>

/************************************/
/*给定一个M×N的迷宫图、入口与出口、  *
 *行走规则。求一条从指定入口到出口的 *
 *路径。所求路径必须是简单路径，即路 *
 *径不重复                           */
/*************************************/

/*迷宫举例*/
/*
int mg[10][10]= { 
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
 };
 */


#define MaxSize 64 //最长简单路径大小
#define MaxCol 10  //最大迷宫列数(包括围墙)

typedef struct
{
	int i;  //当前行
	int j;  //当前列
	int di; //下一可走相邻方位的方位号，设定为上0，右1，下2，左3
}Box,ElemType;
typedef struct  //栈数据类型
{
	ElemType data[MaxSize];
	int top;
}StType,SqStack;

/*InitStack:初始化栈*/
void InitStack(SqStack *&s)
{
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
}

/*Push:进栈操作*/
bool Push(SqStack *&s, ElemType e)
{
	if(s->top == MaxSize-1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/*Pop:出栈操作*/
bool Pop(SqStack *&s, ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

/*GetTop:取栈顶元素*/
bool GetTop(SqStack *s, ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

/*mgpath:简单路径迷宫算法*/
bool mgpath(int xi, int yi, int xe, int ye, int (*mg)[MaxCol])
{
    Box e;
	e.i = xi; e.j = yi; e.di = -1;   //定义一个Box元素e初始化为初始方块
	StType *s; InitStack(s);         //定义栈s并初始化
	Push(s,e);                       //初始方块进栈
	mg[e.i][e.j] = -1;               //方块进栈迷宫值设为-1，避免重复路径
	
	
	int find;   //标识当前路径状态
	int i, j;       //记录尝试坐标
	int di;         //记录尝试方位
	while(s->top != -1)   //栈不为空时
	{
		GetTop(s,e);
		i = e.i; j = e.j; di = e.di;//取栈顶元素进行记录
		if(i == xe && j == ye)  //找到了出口，输出路径
		{
			printf("迷宫路径如下:\n");
		    for(int k = 0; k <= s->top; k++)
			{
				printf("\t(%d,%d)",s->data[k].i, s->data[k].j);
		        if( (k+1)%5 == 0)  //每输出5个方块后换行
		            printf("\n");
			}
			return true;
		}
		
		find = 0;  //每次寻路前先清零
		while(di < 4 && find == 0)
		{
			di++;
			switch(di)
			{
				case 0: {
					i = s->data[s->top].i-1;
					j = s->data[s->top].j;
					break;
				}
				case 1: {
					i = s->data[s->top].i;
					j = s->data[s->top].j+1;
					break;
				}
				case 2: {
					i = s->data[s->top].i+1;
					j = s->data[s->top].j;
					break;
				}
				case 3: {
					i = s->data[s->top].i;
					j = s->data[s->top].j-1;
					break;
				}
			}
			if(mg[i][j] == 0)  //如果路径可走,则找到了可走相邻方块(i,j)
			find = 1;          //改变标识状态
		}
		
		if(find == 1)  //有路径可走
		{
			s->data[s->top].di = di;     //修改原栈顶元素的di值
			e.i = i; e.j = j; e.di = -1;
			Push(s,e);                   //可走方块进栈
			mg[i][j] = -1;               //避免重复走到该方块
		}
		else           //无路径可走,退栈回溯
		{
			mg[s->data[s->top].i][s->data[s->top].j] = 0;
			                             //让该位置变为其他路径可走方块
			s->top--;
		}
	}
	//如果退栈直到栈空，则说明没有可走路径，返回false
	return false;
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

    int C, R;
	scanf("%d %d",&C, &R);
    if(!mgpath(1,1,C,R,mg))
        printf("该迷宫问题没有解！");	
    return 0;	
}