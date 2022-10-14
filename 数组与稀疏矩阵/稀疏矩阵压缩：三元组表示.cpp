#include <stdio.h>
#include <stdlib.h>

/**************************/
/*稀疏矩阵压缩：三元组表示*/
/**************************/

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

/*Value:修改原矩阵A[i][j]的值为x*/
bool Value(TSMatrix &t, int i, int j, ElemType x)
{
	int k = 0, k1;
	if(i < 0 || i > t.rows-1 || j < 0 || j > t.cols-1)
		return false;
	while(k < t.nums && i > t.data[k].r) k++;  //查找行
	while(k < t.nums && i== t.data[k].r && j > t.data[k].c)
		k++;                                   //查找列
	
	if(t.data[k].r == i && t.data[k].c == j)   //存在这样的元素
	    t.data[k].d = x;
	else                 //不存在这样的元素时插入一个元素
	{
		for(k1 = t.nums-1; k1 > k; k1--)
			t.data[k1+1] = t.data[k1];
		
		t.data[k].r = i; t.data[k].c = j; t.data[k].d = x;
		t.nums++;
	}
	return true;
}

/*Assign:将原矩阵A[i][j]的值赋给x*/
bool Assign(TSMatrix t, int i, int j, ElemType &x)
{
	int k = 0;
	if(i < 0 || i > t.rows-1 || j < 0 || j > t.cols-1)
		return false;
	while(k < t.nums && i > t.data[k].r) k++;  //查找行
	while(k < t.nums && i== t.data[k].r && j > t.data[k].c)
		k++;                                   //查找列
	
	if(t.data[k].r == i && t.data[k].c == j)   //存在这样的元素
	    x = t.data[k].d;
	else                                       //没有找到，为0
		x = 0;
	return true;
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

/*测试主函数*/
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
	
	ElemType x;
	int i,j;
	printf("输入下标i,j：\n");
	scanf("%d %d",&i,&j);
	if(Assign(t,i,j,x))
	    printf("A[%d][%d]为：%d\n",i,j,x);
	else
		printf("Error,提取失败\n");
	
	printf("输入下标i,j与值x：\n");
	scanf("%d %d %d",&i,&j,&x);
	if(Value(t,i,j,x))
	    printf("A[%d][%d]更改为：%d\n",i,j,x);
	else
		printf("Error,修改失败\n");
	printf("压缩数组为：\n");
	DispMat(t);
	printf("\n修改后矩阵可由压缩数组还原为：\n");
	DispArr(t);
	
	system("pause");
	return 0;
}