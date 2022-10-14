#include <stdio.h>
#include <stdlib.h>

/******************************/
/*三角矩阵的压缩存储（下三角）*/
/******************************/

/*注：为了计算简便，本代码全篇使用的均为静态数组*/

#define MaxRow 5
#define MaxSize (MaxRow*MaxRow+MaxRow)/2+1
typedef int ElemType;

/*Compression:矩阵压缩算法，行序优先*/
void Compression(ElemType (*A)[MaxRow], ElemType *B, ElemType c)
{
	int count = 0;
	for(int i = 0; i < MaxRow; i++)
		for(int j = 0; j < MaxRow; j++)
			if(i >= j)
				B[count++] = A[i][j];
	B[count] = c;
}

/*Assign:取出原第i行第j列元素存储在e中*/
bool Assign(ElemType *B, int i, int j, ElemType &e)
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow)
		return false;
	
	if(i >= j)             //下三角及对角线
	    e = B[(i*(i-1))/2+j-1];
	else                   //上三角
		e = B[(MaxRow*MaxRow+MaxRow)/2];
	return true;
}

/*Value:将原第i行第j列元素的值修改为e*/
bool Value(ElemType *B, int i, int j, ElemType e)
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow)
		return false;
	
	if(i >= j)             //下三角及对角线
	    B[(i*(i-1))/2+j-1] = e;
	else                   //上三角
		B[(MaxRow*MaxRow+MaxRow)/2] = e;
	return true;
}

/*Display:根据压缩数组打印出原矩阵*/
void Display(ElemType *B)
{
	for(int i = 0; i < MaxRow; i++)
	{
		for(int j = 0; j < MaxRow; j++)
		{
			if(i >= j)
				printf("%4d",B[(i*(i+1))/2+j]);
			else
				printf("%4d",B[(MaxRow*MaxRow+MaxRow)/2]);
		}
		printf("\n");
	}
}

/*测试主函数*/
int main()
{
	ElemType A[MaxRow][MaxRow] = {
		{1,0,0,0,0},
		{1,1,0,0,0},
		{1,2,1,0,0},
		{1,3,3,1,0},
		{1,4,6,4,1}
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