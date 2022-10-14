#include <stdio.h>
#include <stdlib.h>

/**************/
/*��ά����ʵ��*/
/**************/

#define MaxRow 3  //��
#define MaxCol 3  //��
typedef int ElemType;
typedef struct
{
	ElemType data[MaxRow*MaxCol];
	int Row;
	int Col;
}Arr;

/*CreateArr_Row:����������˳����t�����ݴ���һ��i��j�еĶ�ά����*/
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

/*CreateArr_Col:����������˳����t�����ݴ���һ��i��j�еĶ�ά����*/
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

/*Value:��i��j��Ԫ�ظ�ֵΪe*/
bool Value(Arr *&a, int i, int j, ElemType e)
{
	if(i < 1 || i > a->Row || j < 1 || j > a->Col)
		return false;
	a->data[(i-1)*MaxCol+j-1] = e;
	return true;
}

/*Assign:ȡ����i�е�j�е�Ԫ��ֵ������e��*/
bool Assign(Arr *&a, int i, int j, ElemType &e)
{
	if(i < 1 || i > a->Row || j < 1 || j > a->Col)
		return false;
	e = a->data[(i-1)*MaxCol+j-1] ;
	return true;
}

/*DispArr:�����ȵ�˳�������ά����*/
void DispArr(Arr *a)
{
	for(int i = 0; i < a->Row; i++)
	{
		for(int j = 0; j < a->Col; j++)
			printf("\t%d",a->data[i*MaxCol+j]);
		printf("\n");
	}
}

/*DestroyArr:���ٶ�ά����*/
void DestroyArr(Arr *&a)
{
	free(a);
}

/*����������*/
int main()
{
	Arr *a1, *a2;
	ElemType e;
	ElemType t[MaxRow*MaxCol] = {1,2,3,4,5,6,7,8,9};
	
	CreateArr_Row(a1,3,3,t);
	CreateArr_Col(a2,3,3,t);
	
	printf("����������Ϊ:\n");
	DispArr(a1);
	printf("����������Ϊ:\n");
	DispArr(a2);
	
	printf("��3�е�1��Ԫ�طֱ���:\n");
	Assign(a1,3,1,e);
	printf("%d\n",e);
	Assign(a2,3,1,e);
	printf("%d\n",e);
	
	printf("����1�е�2��Ԫ���޸�Ϊ0\n");
	e = 0;
	Value(a1,1,2,e);
	Value(a2,1,2,e);
	printf("�޸ĺ�����ֱ�Ϊ:\n");
	printf("����������Ϊ:\n");
	DispArr(a1);
	printf("����������Ϊ:\n");
	DispArr(a2);

    DestroyArr(a1);
    DestroyArr(a2);
	system("pause");
    return 0;	
}