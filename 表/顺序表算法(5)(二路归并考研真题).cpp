#include <stdio.h>
#include <stdlib.h>


/******************************************************/
/*��·�鲢�������⣺һ������ΪL��L��1������������S��   *
 *���ڵ�[L/2]�� λ�õ�����ΪS����λ���� ���磺������  *
 *S1=(11,13,15,17,19)����S1����λ����15�� �������е�  *
 *��λ���Ǻ���������Ԫ�ص��������е���λ�������磬    *
 *��S2=(2,4,6,8,20)����S1��S2����λ����11�� ��������  *
 *�ȳ�����������A��B�������һ����ʱ��Ϳռ������� �� *
 *�����ܸ�Ч���㷨���ҳ���������A��B����λ��          */
/******************************************************/

#define MaxSize 30  //��˳������󳤶�

typedef int ElemType;
typedef struct  //˳�������
{
	ElemType data[MaxSize];
	int length;
}SqList;

/* CreateList:����˳��� */
void CreateList(SqList *&L, ElemType a[], int n)
{
	int i;
    L = (SqList*)malloc(sizeof(SqList));
    for(i = 0; i < n; i++)
		L->data[i] = a[i];
	L->length = n;
}

/* DestroyList:�������Ա� */
void DestroyList(SqList *&L)
{
	free(L);
}

/* DispList:�����Ա�Ϊ�գ�������Ա� */
void DispList(SqList *L)
{
	int i;
	if(L->length==0)
		return ;
	for(i = 0; i < L->length; i++)
		printf("%d ",L->data[i]);  //�ô���ElemType����޸�
	printf("\n");
}

/* M_Search:Ѱ����λ���㷨 */
void M_Search(SqList *A, SqList *B, ElemType &e)  //��ħ��
{
	int i, j, k, n;
	i = j = k = 0;
	n = (A->length + B->length)/2;
	while(i < n && j < n)
	{
		k++;
		if(A->data[i] < B->data[j])
		{
			if(k == n)
			{e = A->data[i]; break;}
		    i++;
		}
		else
		{
			if(k == n)
			{e = B->data[j]; break;}
			j++;
		}
	}
	//���㷨ʱ�临�Ӷ�ΪO(n),�ռ临�Ӷ�ΪO(1);
}

/* ���������� */
int main()
{
	ElemType S1[5] = {11,13,15,17,19};
	int n1 = 5;
	ElemType S2[5] = {2,4,6,8,20};
	int n2 = 5;
	
	SqList *L1, *L2;
	CreateList(L1,S1,n1);
	CreateList(L2,S2,n2);
	
	printf("ԭ��S1��S2�ֱ�Ϊ:\n");
	DispList(L1);
	DispList(L2);
	printf("����S1������S2����λ��Ϊ:\n");
    ElemType e;
	M_Search(L1,L2,e);
	printf("%d\n",e);
	
	DestroyList(L1);
	DestroyList(L2);
	
	system("pause");
	return 0;
}