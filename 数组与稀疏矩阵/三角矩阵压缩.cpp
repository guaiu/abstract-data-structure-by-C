#include <stdio.h>
#include <stdlib.h>

/******************************/
/*���Ǿ����ѹ���洢�������ǣ�*/
/******************************/

/*ע��Ϊ�˼����㣬������ȫƪʹ�õľ�Ϊ��̬����*/

#define MaxRow 5
#define MaxSize (MaxRow*MaxRow+MaxRow)/2+1
typedef int ElemType;

/*Compression:����ѹ���㷨����������*/
void Compression(ElemType (*A)[MaxRow], ElemType *B, ElemType c)
{
	int count = 0;
	for(int i = 0; i < MaxRow; i++)
		for(int j = 0; j < MaxRow; j++)
			if(i >= j)
				B[count++] = A[i][j];
	B[count] = c;
}

/*Assign:ȡ��ԭ��i�е�j��Ԫ�ش洢��e��*/
bool Assign(ElemType *B, int i, int j, ElemType &e)
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow)
		return false;
	
	if(i >= j)             //�����Ǽ��Խ���
	    e = B[(i*(i-1))/2+j-1];
	else                   //������
		e = B[(MaxRow*MaxRow+MaxRow)/2];
	return true;
}

/*Value:��ԭ��i�е�j��Ԫ�ص�ֵ�޸�Ϊe*/
bool Value(ElemType *B, int i, int j, ElemType e)
{
	if(i < 1 || i > MaxRow || j < 1 || j > MaxRow)
		return false;
	
	if(i >= j)             //�����Ǽ��Խ���
	    B[(i*(i-1))/2+j-1] = e;
	else                   //������
		B[(MaxRow*MaxRow+MaxRow)/2] = e;
	return true;
}

/*Display:����ѹ�������ӡ��ԭ����*/
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

/*����������*/
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