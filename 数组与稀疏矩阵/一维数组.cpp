#include <stdio.h>
#include <stdlib.h>

/******************/
/*һά����ṹ����*/
/******************/

#define MaxSize 5
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
}Arr;

/*InitArr:��ʼ��*/
void InitArr(Arr *&a)
{
	a = (Arr*)malloc(sizeof(Arr));
}

/*Value:Ԫ�ظ�ֵ*/
bool Value(Arr *&a, int i,ElemType e)
{
	if(i < 0 || i >= MaxSize-1)
		return false;
	a->data[i] = e;
	return true;
}

/*Assign:ȡԪ��ֵ*/
bool Assign(Arr *a, int i, ElemType &e)
{
	if(i < 0 || i >= MaxSize-1)
		return false;
	e = a->data[i];
	return true;
}

/*DispArr:�����������Ԫ��ֵ*/
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