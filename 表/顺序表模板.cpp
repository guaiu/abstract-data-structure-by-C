#include <stdio.h>
#include <stdlib.h>

/***************************************/
/*          ˳���ṹ����             */
/***************************************/

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

/* InitList:������˳��� */
void InitList(SqList *&L)
{
	L = (SqList*)malloc(sizeof(SqList));
	L->length = 0;
}

/* DestroyList:�������Ա� */
void DestroyList(SqList *&L)
{
	free(L);
}

/* ListEmpty:�ж��Ƿ�Ϊ�ձ�,�ձ���true */
bool ListEmpty(SqList *L)
{
	return (L->length==0);
}

/* ListLength:�������Ա�ĳ��� */
int ListLength(SqList *L)
{
	return (L->length);
}

/* DispList:�����Ա�Ϊ�գ�������Ա� */
void DispList(SqList *L)
{
	int i;
	if(ListEmpty(L))
		return ;
	for(i = 0; i < L->length; i++)
		printf("%d",L->data[i]);  //�ô���ElemType����޸�
	printf("\n");
}

/* GetElem:��ĳ������Ԫ��ֵ */
bool GetElem(SqList *L, int i, ElemType &e)
{
	if(i<1 || i>L->length)
		return false;
	e = L->data[i-1];
	return true;
}

/* LocateElem:������˳����ҵ�һ��ֵ����e��ȵ�Ԫ�ص��߼�λ���������ڣ�����0 */
int LocateElem(SqList *L, ElemType e)
{
	int i = 0;
	while(i<L->length && L->data[i]!=e)
		i++;
	if(i>=L->length)
		return 0;
	else
		return i+1;
}

/* ListInsert:��������Ԫ�� */
bool ListInsert(SqList *&L, int i, ElemType e)
{
	int j;
	if(i<1 || i>L->length+1)
		return false;
	i--;
	for(j = L->length; j > i; j--)
		L->data[j] = L->data[j-1];
	L->data[i] = e;
	L->length++;
	return true;
}

/* ListDelete;ɾ������Ԫ�� */
bool ListDelete(SqList *&L, int i, ElemType &e)
{
	int j;
	if(i<1 || i>L->length)
		return false;
	i--;
	e = L->data[i];
	for(j = i; j < L->length; j++)
		L->data[j] = L->data[j+1];
	L->length--;
	return true;
}

int main()
{
	system("pause");
	return 0;
}