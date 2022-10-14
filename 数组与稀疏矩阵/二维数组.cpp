#include <stdio.h>
#include <stdlib.h>

/**************/
/*二维数组实现*/
/**************/

#define MaxRow 3  //行
#define MaxCol 3  //列
typedef int ElemType;
typedef struct
{
	ElemType data[MaxRow*MaxCol];
	int Row;
	int Col;
}Arr;

/*CreateArr_Row:依据行优先顺序用t中数据创造一个i行j列的二维数组*/
void CreateArr_Row(Arr *&a, int i, int j,ElemType t[])
{
	a = (Arr*)malloc(sizeof(Arr));
	int count = 0;
	for(int k = 0; k < i; k++)
		for(int u = 0; u < j; u++)
			a->data[k*MaxCol+u] = t[count++];
	a->Row = i;
	a->Col = j;
}

/*CreateArr_Col:依据列优先顺序用t中数据创造一个i行j列的二维数组*/
void CreateArr_Col(Arr *&a, int i, int j,ElemType t[])
{
	a = (Arr*)malloc(sizeof(Arr));
	int count = 0;
    for(int u = 0; u < j; u++)
	    for(int k = 0; k < i; k++)
			a->data[k*MaxCol+u] = t[count++];
	a->Row = i;
	a->Col = j;
}

/*Value:给i行j列元素赋值为e*/
bool Value(Arr *&a, int i, int j, ElemType e)
{
	if(i < 1 || i > a->Row || j < 1 || j > a->Col)
		return false;
	a->data[(i-1)*MaxCol+j-1] = e;
	return true;
}

/*Assign:取出第i行第j列的元素值储存在e中*/
bool Assign(Arr *&a, int i, int j, ElemType &e)
{
	if(i < 1 || i > a->Row || j < 1 || j > a->Col)
		return false;
	e = a->data[(i-1)*MaxCol+j-1] ;
	return true;
}

/*DispArr:行优先的顺序输出二维数组*/
void DispArr(Arr *a)
{
	for(int i = 0; i < a->Row; i++)
	{
		for(int j = 0; j < a->Col; j++)
			printf("\t%d",a->data[i*MaxCol+j]);
		printf("\n");
	}
}

/*DestroyArr:销毁二维数组*/
void DestroyArr(Arr *&a)
{
	free(a);
}

/*测试主程序*/
int main()
{
	Arr *a1, *a2;
	ElemType e;
	ElemType t[MaxRow*MaxCol] = {1,2,3,4,5,6,7,8,9};
	
	CreateArr_Row(a1,3,3,t);
	CreateArr_Col(a2,3,3,t);
	
	printf("行优先数组为:\n");
	DispArr(a1);
	printf("列优先数组为:\n");
	DispArr(a2);
	
	printf("第3行第1列元素分别是:\n");
	Assign(a1,3,1,e);
	printf("%d\n",e);
	Assign(a2,3,1,e);
	printf("%d\n",e);
	
	printf("将第1行第2列元素修改为0\n");
	e = 0;
	Value(a1,1,2,e);
	Value(a2,1,2,e);
	printf("修改后数组分别为:\n");
	printf("行优先数组为:\n");
	DispArr(a1);
	printf("列优先数组为:\n");
	DispArr(a2);

    DestroyArr(a1);
    DestroyArr(a2);
	system("pause");
    return 0;	
}