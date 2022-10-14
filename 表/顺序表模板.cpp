#include <stdio.h>
#include <stdlib.h>

/***************************************/
/*          顺序表结构尝试             */
/***************************************/

#define MaxSize 30  //该顺序表的最大长度

typedef int ElemType;
typedef struct  //顺序表类型
{
	ElemType data[MaxSize];
	int length;
}SqList;

/* CreateList:创建顺序表 */
void CreateList(SqList *&L, ElemType a[], int n)
{
	int i;
    L = (SqList*)malloc(sizeof(SqList));
    for(i = 0; i < n; i++)
		L->data[i] = a[i];
	L->length = n;
}

/* InitList:创建空顺序表 */
void InitList(SqList *&L)
{
	L = (SqList*)malloc(sizeof(SqList));
	L->length = 0;
}

/* DestroyList:销毁线性表 */
void DestroyList(SqList *&L)
{
	free(L);
}

/* ListEmpty:判断是否为空表,空表返回true */
bool ListEmpty(SqList *L)
{
	return (L->length==0);
}

/* ListLength:返回线性表的长度 */
int ListLength(SqList *L)
{
	return (L->length);
}

/* DispList:若线性表不为空，输出线性表 */
void DispList(SqList *L)
{
	int i;
	if(ListEmpty(L))
		return ;
	for(i = 0; i < L->length; i++)
		printf("%d",L->data[i]);  //该处视ElemType情况修改
	printf("\n");
}

/* GetElem:求某个数据元素值 */
bool GetElem(SqList *L, int i, ElemType &e)
{
	if(i<1 || i>L->length)
		return false;
	e = L->data[i-1];
	return true;
}

/* LocateElem:按运算顺序查找第一个值域与e相等的元素的逻辑位序，若不存在，返回0 */
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

/* ListInsert:插入数据元素 */
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

/* ListDelete;删除数据元素 */
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