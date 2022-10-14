#include <stdio.h>
#include <stdlib.h>

/**************************************************/
/*��˳���L��10�����������һ���㷨���Ե�һ��Ԫ*
 *��Ϊ�ֽ��ߣ���׼����������С�ڵ�������Ԫ���Ƶ�*
 *��Ԫ�ص�ǰ�棬 �����д�������Ԫ���Ƶ���Ԫ�صĺ�*
 *�档                                         */
 /*************************************************/
 
#define MaxSize 20
typedef int ElemType;
typedef struct  //˳�����������
{
	ElemType data[MaxSize];
	int length;
}Sqlist;

/* CreateList:����˳��� */
void CreateList(Sqlist *&L, ElemType a[], int n)
{
	int i;
	L = (Sqlist*)malloc(sizeof(Sqlist));
	for(i = 0; i < n; i++)
		L->data[i] = a[i];
	
	L->length = n;
}

/* DestroyList:����˳��� */
void DestroyList(Sqlist *&L)
{
	free(L);
}

/* ListEmpty:�ж��Ƿ�Ϊ�ձ����򷵻��� */
bool ListEmpty(Sqlist *L)
{
	return (L->length == 0);
}

/* DispList:��˳���Ϊ�գ����˳��� */
void DispList(Sqlist *L)
{
	int i;
	if(ListEmpty(L))
		return ;
	else
		for(i = 0; i < L->length; i++)
			printf("%d ",L->data[i]);  //������޸�������
	printf("\n");
}

/* move1:�㷨һ */
void move1(Sqlist *&L)
{
	int i = 0, j = L->length-1;
	ElemType temp;
	ElemType pivot = L->data[0];  //��data[0]Ϊ��׼
	while(i < j)
	{
		while(i < j && L->data[j] > pivot)
			j--;  //j�Ӻ���ǰ��Ѱ��<=pivot��Ԫ��
		while(i < j && L->data[i] <= pivot)
			i++;  //��ǰ����Ѱ��>pivot��Ԫ��
		if(i < j)
		{
			temp = L->data[i];  //L->data[i]��L->data[j]ֵ����
			L->data[i] = L->data[j];
			L->data[j] = temp;
		}
	}//��������������һ��ֵ����֮��ض���j����i
	temp = L->data[0];  //L->data[0]��L->data[j]ֵ����
	L->data[0] = L->data[j];
	L->data[j] = temp;
}

/* move2:�㷨�� */
void move2(Sqlist *&L)
{
	int i = 0, j = L->length-1;
	ElemType pivot = L->data[0];  //��data[0]Ϊ��׼
	while(i < j)
	{
		while(j > i && L->data[j] > pivot)
			j--;  //��������ɨ�裬��һ��<=pivot��data[j]
		L->data[i] = L->data[j];  //�������data[i]��
		while(i < j && L->data[i] <= pivot)
			i++;  //��������ɨ�裬��һ��>pivot�ļ�¼data[i]
		L->data[j] = L->data[i];  //�������data[j]��
	}//��������������һ��ֵ������ض���j����i,��i��Ϊ"��"
	L->data[i] = pivot;  //���û�׼
}//�㷨�������ܱ��㷨һ��

int main()
{
	int n = 0;
	ElemType a[MaxSize];
	printf("��������ĳ��ȣ�Ȼ�������������Ԫ�ص�ֵ��\n");
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);  //��������ı�������
	
	printf("\n\n\nִ���㷨һ�Ľ��Ϊ��\n");
	Sqlist *L1;
	CreateList(L1,a,n);
	move1(L1);
	DispList(L1);
	DestroyList(L1);
	L1 = NULL;
	
	printf("\n\n\nִ���㷨���Ľ��Ϊ�� \n");
	Sqlist *L2;
	CreateList(L2,a,n);
	move2(L2);
	DispList(L2);
	DestroyList(L2);
	L2 = NULL;
	
	return 0;
}