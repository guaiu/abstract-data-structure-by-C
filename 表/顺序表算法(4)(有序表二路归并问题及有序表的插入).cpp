#include <stdio.h>
#include <stdlib.h>


/**********************/
/*顺序表二路归并算法  *
 *及有序表插入算法测试*/
/**********************/

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

/*附加测试*/
/*ListInsert:有序表的插入算法*/
void ListInsert(SqList *&L, ElemType e)  //注意：此处必定插入成功
{
	int i = 0, j;
	while(i < L->length && L->data[i] < e)
		i++;
	for(j = L->length; j > i; j--)  //后移
		L->data[j] = L->data[j-1];
	L->data[i] = e;
	L->length++;
}

/*UnionList:有序表二路归并算法*/
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
	
	while(i < LA->length)  //LA尚未扫描完
	{
		LC->data[k] = LA->data[i];
		i++; k++;
	}
	while(j < LB->length)  //LB尚未扫描完
	{
		LC->data[k] = LB->data[j];
		j++; k++;
	}
	LC->length = k;
	
	//本算法时间复杂度为O(m+n),空间复杂度为O(m+n)
}

/*测试主函数*/
int main()
{
	ElemType a1[5] = {1,3,5,7,9};
	ElemType a2[4] = {2,4,6,8,};
	int n1 = 5;
	int n2 = 4;
	
	SqList *LA, *LB, *LC;
	CreateList(LA,a1,n1);
	CreateList(LB,a2,n2);
	printf("a1原表为:\n");
	DispList(LA);
	printf("a2原表为:\n");
	DispList(LB);
	printf("二路归并后为:\n");
	UnionList(LA,LB,LC);
	DispList(LC);
	
	printf("额外测试：有序表插入算法:\n");
	ElemType e;
	printf("输入e并插入表中:\n");
	scanf("%d",&e);
	ListInsert(LC,e);
	printf("插入后为:\n");
	DispList(LC);
	
	
	DestroyList(LA);
	DestroyList(LB);
	DestroyList(LC);
	
	system("pause");
	return 0;
}