#include <stdio.h>
#include <stdlib.h>

/******************/
/*一维数组结构尝试*/
/******************/

#define MaxSize 5
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
}Arr;

/*InitArr:初始化*/
void InitArr(Arr *&a)
{
	a = (Arr*)malloc(sizeof(Arr));
}

/*Value:元素赋值*/
bool Value(Arr *&a, int i,ElemType e)
{
	if(i < 0 || i >= MaxSize-1)
		return false;
	a->data[i] = e;
	return true;
}

/*Assign:取元素值*/
bool Assign(Arr *a, int i, ElemType &e)
{
	if(i < 0 || i >= MaxSize-1)
		return false;
	e = a->data[i];
	return true;
}

/*DispArr:输出数组所有元素值*/
void DispArr(Arr *a)
{
	for(int i = 0; i < MaxSize; i++)
		printf("%d",a->data[i]);
	printf("\n");
}

int main()
{
	Arr *a;
	int i;
	ElemType e;
	InitArr(a);
	for(int k = 0; k < MaxSize; k++)
		a->data[k] = 0;
	
	scanf("%d %d",&i, &e);
	Value(a,i,e);
	scanf("%d %d",&i, &e);
	Value(a,i,e);
	
	scanf("%d",&i);
	Assign(a,i,e);
	printf("%d\n",e);
	scanf("%d",&i);
	Assign(a,i,e);
	printf("%d\n",e);
	
	DispArr(a);
	system("pause");
	return 0;
}