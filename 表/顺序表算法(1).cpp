#include <stdio.h>
#include <stdlib.h>

/**********************************************/
/*问题描述：已知长度为n的线性表A采用顺序存储结*
 *构。设计 一个时间复杂度为O(n)、空间复杂度   *
 *为O(1)的算法，该算法删除线性表中所有值为x的*
 *数据元素。                                  */
 /*********************************************/
 
#define MaxSize 20
typedef int ElemType;
typedef struct  //顺序表数据类型
{
	ElemType data[MaxSize];
	int length;
}Sqlist;

/* CreateList:创建顺序表 */
void CreateList(Sqlist *&L, ElemType a[], int n)
{
	int i;
	L = (Sqlist*)malloc(sizeof(Sqlist));
	for(i = 0; i < n; i++)
		L->data[i] = a[i];
	
	L->length = n;
}

/* DestroyList:销毁顺序表 */
void DestroyList(Sqlist *&L)
{
	free(L);
}

/* ListEmpty:判断是否为空表，是则返回真 */
bool ListEmpty(Sqlist *L)
{
	return (L->length == 0);
}

/* DispList:若顺序表不为空，输出顺序表 */
void DispList(Sqlist *L)
{
	int i;
	if(ListEmpty(L))
		return ;
	else
		for(i = 0; i < L->length; i++)
			printf("%d",L->data[i]);  //视情况修改输出语句
	printf("\n");
}

/* delnode1:算法一， 扫描顺序表A，重建A只包含不等于x的元素。*/
void delnode1(Sqlist *&L, ElemType x)
{
	int k = 0, i;
	for(i = 0; i < L->length; i++)
		if(L->data[i] != x)
		{
			L->data[k] = L->data[i];
			k++;
		}
	L->length = k;
}

/* delnode2:算法二，将不为x的元素前移k个位置，最后修改A的长度。*/
void delnode2(Sqlist *&L, ElemType x)
{
	int k = 0, i;
	for(i = 0; i < L->length; i++)
	{
		if(L->data[i] == x)
			k++;
		else
			L->data[i-k] = L->data[i];
	}
	L->length -= k;
}

int main()
{
	int n = 0;
	ElemType a[MaxSize];
	printf("输入数组元素的长度，然后依次输入数组长度的值：\n");
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);  //视情况修改相关语句
	
	ElemType x;
    printf("输入要删除的值：\n");
	scanf("%d",&x); //视情况修改相关语句
	
	printf("\n\n\n算法一执行的结果：\n");
	Sqlist *L1;
	CreateList(L1,a,n);
	delnode1(L1,x);
	DispList(L1);
	DestroyList(L1);
	L1 = NULL;
	
	printf("\n\n\n算法二执行的结果：\n");
    Sqlist *L2;
	CreateList(L2,a,n);
	delnode2(L2,x);
	DispList(L2);
	DestroyList(L2);
	L2 = NULL;
	
	return 0;
}
















