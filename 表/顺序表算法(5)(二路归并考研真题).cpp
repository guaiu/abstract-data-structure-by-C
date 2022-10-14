#include <stdio.h>
#include <stdlib.h>


/******************************************************/
/*二路归并考研真题：一个长度为L（L≥1）的升序序列S，   *
 *处在第[L/2]个 位置的数称为S的中位数。 例如：若序列  *
 *S1=(11,13,15,17,19)，则S1的中位数是15。 两个序列的  *
 *中位数是含它们所有元素的升序序列的中位数。例如，    *
 *若S2=(2,4,6,8,20)，则S1和S2的中位数是11。 现有两个  *
 *等长的升序序列A和B，试设计一个在时间和空间两方面 都 *
 *尽可能高效的算法，找出两个序列A和B的中位数          */
/******************************************************/

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

/* DestroyList:销毁线性表 */
void DestroyList(SqList *&L)
{
	free(L);
}

/* DispList:若线性表不为空，输出线性表 */
void DispList(SqList *L)
{
	int i;
	if(L->length==0)
		return ;
	for(i = 0; i < L->length; i++)
		printf("%d ",L->data[i]);  //该处视ElemType情况修改
	printf("\n");
}

/* M_Search:寻找中位数算法 */
void M_Search(SqList *A, SqList *B, ElemType &e)  //已魔改
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
	//该算法时间复杂度为O(n),空间复杂度为O(1);
}

/* 测试主函数 */
int main()
{
	ElemType S1[5] = {11,13,15,17,19};
	int n1 = 5;
	ElemType S2[5] = {2,4,6,8,20};
	int n2 = 5;
	
	SqList *L1, *L2;
	CreateList(L1,S1,n1);
	CreateList(L2,S2,n2);
	
	printf("原表S1和S2分别为:\n");
	DispList(L1);
	DispList(L2);
	printf("序列S1和序列S2的中位数为:\n");
    ElemType e;
	M_Search(L1,L2,e);
	printf("%d\n",e);
	
	DestroyList(L1);
	DestroyList(L2);
	
	system("pause");
	return 0;
}