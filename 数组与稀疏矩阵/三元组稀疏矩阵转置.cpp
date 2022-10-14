#include <stdio.h>
#include <stdlib.h>

/********************/
/*三元组稀疏矩阵转置*/
/********************/

#define MaxSize 100
#define M 6
#define N 5
typedef int ElemType;
typedef struct
{
	int r;        //行号
	int c;        //列号
	ElemType d;   //元素值
}TupNode;         //三元组定义

typedef struct
{
	int rows;     //行数值
	int cols;     //列数值
	int nums;     //非零元素个数
	TupNode data[MaxSize];
}TSMatrix;        //三元组顺序表定义

/*CreatMat:稀疏数组压缩算法(行优先)*/
void CreatMat(TSMatrix &t, ElemType A[M][N])
{
	int i,j;
	t.rows = M; t.cols = N; t.nums = 0;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
			if(A[i][j] != 0)
			{
				t.data[t.nums].r = i;
				t.data[t.nums].c = j;
				t.data[t.nums].d = A[i][j];
				t.nums++;
			}
	}
}

/*DispMat:输出三元组*/
void DispMat(TSMatrix t)
{
	int i;
	if(t.nums <= 0)
		return;
	printf("\t%d\t%d\t%d\n",t.rows,t.cols,t.nums);
	printf("-------------------------\n");
	for(i = 0; i < t.nums; i++)
		printf("\t%d\t%d\t%d\n",t.data[i].r, t.data[i].c, t.data[i].d);
}

/*DispArr:根据三元组输出原矩阵*/
void DispArr(TSMatrix t)
{
	if(t.nums <= 0)
		return;
	
	int k = 0;
	for(int i = 0; i < t.rows; i++)
	{
		while(k < t.nums && i > t.data[k].r) k++;  //移动行
		for(int j = 0; j < t.cols; j++)
		{
			while(k < t.nums && i == t.data[k].r && j > t.data[k].c)
				k++;                               //移动列
			if(t.data[k].r == i && t.data[k].c == j)
				printf("\t%d",t.data[k].d);
			else
				printf("\t%d",0);				
		}
		printf("\n");
	}
}

/*TranTat:矩阵转置*/
void TranTat(TSMatrix t, TSMatrix &tb)
{
	int p, q = 0, v;
	tb.rows = t.cols; tb.cols = t.rows; tb.nums = t.nums;
	if(t.nums != 0)
	{
		for(v = 0; v < t.cols; v++)        //tb.data[q]中以列序排列
			for(p = 0; p < t.nums; p++)    //p为t.data的下标
			    if(t.data[p].c == v)
				{
					tb.data[q].r = t.data[p].c;
					tb.data[q].c = t.data[p].r;
					tb.data[q].d = t.data[p].d;
					q++;
				}
	}
}

/*测试函数*/
int main()
{
	ElemType A[M][N] = {
		{ 0, 1, 0, 0, 0},
		{ 0, 2, 0, 0, 0},
		{ 0, 0, 0, 0, 0},
		{ 0, 0, 3, 4, 5},
		{ 0, 0, 0, 0, 0},
		{ 6, 0, 0, 7, 0}
	};
	TSMatrix t;
	CreatMat(t,A);
	
	printf("压缩数组为：\n");
	DispMat(t);
	printf("\n原矩阵可由压缩数组还原为：\n");
	DispArr(t);
	
	TSMatrix tb;
	TranTat(t,tb);
	printf("转置数组为：\n");
	DispMat(tb);
	printf("\n转置矩阵可由压缩数组还原为：\n");
	DispArr(tb);
	
	system("pause");
	return 0;
}