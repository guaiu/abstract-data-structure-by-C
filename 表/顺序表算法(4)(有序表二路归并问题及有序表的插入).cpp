#include <stdio.h>
#include <stdlib.h>


/**********************/
/*˳����·�鲢�㷨  *
 *�����������㷨����*/
/**********************/

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

/*���Ӳ���*/
/*ListInsert:�����Ĳ����㷨*/
void ListInsert(SqList *&L, ElemType e)  //ע�⣺�˴��ض�����ɹ�
{
	int i = 0, j;
	while(i < L->length && L->data[i] < e)
		i++;
	for(j = L->length; j > i; j--)  //����
		L->data[j] = L->data[j-1];
	L->data[i] = e;
	L->length++;
}

/*UnionList:������·�鲢�㷨*/
void UnionList(SqList *LA, SqList *LB, SqList *&LC)
{
	int i = 0, j = 0, k = 0;
	LC = (SqList*)malloc(sizeof(SqList));
	while(i < LA->length && j < LB->length)
	{
		if(LA->data[i] < LB->data[j])
		{
			LC->data[k] = LA->data[i];
			i++; k++;
		}
		else
		{
			LC->data[k] = LB->data[j];
			j++; k++;
		}
	}
	
	while(i < LA->length)  //LA��δɨ����
	{
		LC->data[k] = LA->data[i];
		i++; k++;
	}
	while(j < LB->length)  //LB��δɨ����
	{
		LC->data[k] = LB->data[j];
		j++; k++;
	}
	LC->length = k;
	
	//���㷨ʱ�临�Ӷ�ΪO(m+n),�ռ临�Ӷ�ΪO(m+n)
}

/*����������*/
int main()
{
	ElemType a1[5] = {1,3,5,7,9};
	ElemType a2[4] = {2,4,6,8,};
	int n1 = 5;
	int n2 = 4;
	
	SqList *LA, *LB, *LC;
	CreateList(LA,a1,n1);
	CreateList(LB,a2,n2);
	printf("a1ԭ��Ϊ:\n");
	DispList(LA);
	printf("a2ԭ��Ϊ:\n");
	DispList(LB);
	printf("��·�鲢��Ϊ:\n");
	UnionList(LA,LB,LC);
	DispList(LC);
	
	printf("������ԣ����������㷨:\n");
	ElemType e;
	printf("����e���������:\n");
	scanf("%d",&e);
	ListInsert(LC,e);
	printf("�����Ϊ:\n");
	DispList(LC);
	
	
	DestroyList(LA);
	DestroyList(LB);
	DestroyList(LC);
	
	system("pause");
	return 0;
}