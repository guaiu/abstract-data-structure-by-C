#include <stdio.h>
#include <stdlib.h>

/****************/
/*���ԽǾ���ѹ��*/
/****************/

/*ע��Ϊ�˼����㣬������ȫƪʹ�õľ�Ϊ��̬����*/

#define MaxRow 5
#define MaxSize MaxRow*3-1
typedef int ElemType;

/*Compression:����ѹ���㷨����������*/
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

/*Assign:ȡ��ԭ��i�е�j��Ԫ�ش洢��e��*/
bool Assign(ElemType *B, int i, int j, ElemType &e)
//a[x][y] = b[k],�й�ʽk=2x+y
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow)
		return false;
	if(j < i-1 || j > i+1)
		e = B[MaxSize-1];  //����
	else
	    e = B[2*(i-1)+(j-1)];
	return true;
}

/*Value:��ԭ��i�е�j��Ԫ�ص�ֵ�޸�Ϊe(��ֹ�޸ĳ���c)*/
bool Value(ElemType *B, int i, int j, ElemType e)
//a[x][y] = b[k],�й�ʽk=2x+y
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow || j < i-1 || j > i+1)
		return false;
	B[2*(i-1)+(j-1)] = e;
	return true;
}

/*Display:����ѹ�������ӡ��ԭ����*/
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

/*����������*/
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
	printf("ѹ������Ϊ��\n");
	for(int k = 0; k < MaxSize; k++)
		printf("%3d",B[k]);
	printf("\nԭ�������ѹ�����黹ԭΪ��\n");
	Display(B);
	
	ElemType e;
	int i,j;
	printf("�����С��У�\n");
	scanf("%d %d",&i,&j);
	if(Assign(B,i,j,e))
	    printf("��%d�У���%d��Ԫ��Ϊ��%d\n",i,j,e);
	else
		printf("Error,��ȡʧ��\n");
	
	printf("�����С��У�e��\n");
	scanf("%d %d %d",&i,&j,&e);
	if(Value(B,i,j,e))
	    printf("��%d�У���%d��Ԫ��Ϊ��%d\n",i,j,e);
	else
		printf("Error,�޸�ʧ��\n");
	printf("ѹ������Ϊ��\n");
	for(int k = 0; k < MaxSize; k++)
		printf("%3d",B[k]);
	printf("\n�޸ĺ�������ѹ�����黹ԭΪ��\n");
	Display(B);
	
	return 0;
}