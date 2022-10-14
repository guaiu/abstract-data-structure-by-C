#include <stdio.h>
#include <stdlib.h>

/****************/
/*三对角矩阵压缩*/
/****************/

/*注：为了计算简便，本代码全篇使用的均为静态数组*/

#define MaxRow 5
#define MaxSize MaxRow*3-1
typedef int ElemType;

/*Compression:矩阵压缩算法，行序优先*/
void Compression(ElemType (*A)[MaxRow], ElemType *B, ElemType c)
{
	int count = 0;
	for(int i = 0; i < MaxRow; i++)
	{
		if(i == 0){ B[count++] = A[0][0]; B[count++] = A[0][1]; }
		else if(i == MaxRow-1) {
			B[count++] = A[MaxRow-1][MaxRow-2];
			B[count++] = A[MaxRow-1][MaxRow-1];
		}
		else
		{
			for(int j = 0; j < 3; j++)
				B[count++] = A[i][i-1+j];
		}
	}
	B[count] = c;
}

/*Assign:取出原第i行第j列元素存储在e中*/
bool Assign(ElemType *B, int i, int j, ElemType &e)
//a[x][y] = b[k],有公式k=2x+y
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow)
		return false;
	if(j < i-1 || j > i+1)
		e = B[MaxSize-1];  //常数
	else
	    e = B[2*(i-1)+(j-1)];
	return true;
}

/*Value:将原第i行第j列元素的值修改为e(禁止修改常数c)*/
bool Value(ElemType *B, int i, int j, ElemType e)
//a[x][y] = b[k],有公式k=2x+y
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow || j < i-1 || j > i+1)
		return false;
	B[2*(i-1)+(j-1)] = e;
	return true;
}

/*Display:根据压缩数组打印出原矩阵*/
void Display(ElemType *B)
{
	int count = 0;
	for(int i = 0; i < MaxRow; i++)
	{
		for(int j = 0; j < MaxRow; j++)
		{
			if(j < i-1 || j > i+1)
				printf("%4d",B[MaxSize-1]);
			else
				printf("%4d",B[count++]);
		}
		printf("\n");
	}
}

/*测试主函数*/
int main()
{
	ElemType A[MaxRow][MaxRow] = {
		{ 1, 2, 0, 0, 0},
		{ 3, 4, 5, 0, 0},
		{ 0, 6, 7, 8, 0},
		{ 0, 0, 9,10,11},
		{ 0, 0, 0,12,13}
	};
	ElemType c = 0;
	
	ElemType B[MaxSize];
	Compression(A,B,c);
	printf("压缩数组为：\n");
	for(int k = 0; k < MaxSize; k++)
		printf("%3d",B[k]);
	printf("\n原矩阵可由压缩数组还原为：\n");
	Display(B);
	
	ElemType e;
	int i,j;
	printf("输入行、列：\n");
	scanf("%d %d",&i,&j);
	if(Assign(B,i,j,e))
	    printf("第%d行，第%d列元素为：%d\n",i,j,e);
	else
		printf("Error,提取失败\n");
	
	printf("输入行、列，e：\n");
	scanf("%d %d %d",&i,&j,&e);
	if(Value(B,i,j,e))
	    printf("第%d行，第%d列元素为：%d\n",i,j,e);
	else
		printf("Error,修改失败\n");
	printf("压缩数组为：\n");
	for(int k = 0; k < MaxSize; k++)
		printf("%3d",B[k]);
	printf("\n修改后矩阵可由压缩数组还原为：\n");
	Display(B);
	
	return 0;
}