#include <stdio.h>
#include <stdlib.h>


/******************************************/
/*设有一个条块序列，每个条块为红 （0）    *
*、白（1）、兰（2）三种颜色中的一种。假   *
*设该序列 采用顺序表存储，设计一个时间复  *
*杂度为O(n)的算法，使得 这些条块按红、白、*
*兰的顺序排好，即排成荷兰国旗图案。       */
/******************************************/

#define MaxSize 20

typedef int ElemType;
typedef struct  //顺序表类型
{
	ElemType data[MaxSize];
	int length;
}SqList;


/*创建顺序表*/
void CreateList(SqList *&L, ElemType a[], int n)
{
	L = (SqList*)malloc(sizeof(SqList));
	for(int i = 0; i < n; i++)
		L->data[i] = a[i];
	L->length = n;
}

/*输出顺序表*/
void DispList(SqList *L)
{
	
	if(L->length == 0)
		return ;
	for(int i = 0; i < L->length; i++)
		printf("%d ",L->data[i]);
	printf("\n");
}

/*销毁顺序表*/
void DestroyList(SqList *&L)
{
	free(L);
}

/*元素值交换*/
void swap(ElemType &a1, ElemType &a2)
{
	ElemType temp;
	temp = a1;
	a1 = a2;
	a2 = temp;
}

/*荷兰国旗排列算法*/
void move1(SqList *&L)
{
	int i = -1, j = 0, k = L->length;  //j用于遍历，i用于扩大0元素区间，k用于扩大2元素区间
	while(j < k)
	{
		if(L->data[j] == 0)  //j指向元素0：说明它属于前部，i增1（扩大0元素区间），
		{                    //将i、j位置的元素交换，j++。 
			i++;
			swap(L->data[i], L->data[j]);
			j++;
		}
		else if(L->data[j] == 2)  //j指向元素2：说明它属于后部，k减1（扩大2元素区间），
		{                         //将j、k位置的元素 交换，此时j位置的元素可能还要
			k--;                  //交换到前部，所以j不前进
			swap(L->data[k], L->data[j]);
		}
		else j++;  //j指向元素1：说明它属于中部，保持不动，j++。 
	}
}

/*测试主程序*/
int main()
{
	ElemType a[12] = {1,0,2,1,0,0,1,2,2,1,0,2};
	int n = 12;
	SqList *L;
	CreateList(L,a,n);
	printf("原表为：\n");
	DispList(L);
	
	printf("经算法排列后为：\n");
	move1(L);
	DispList(L);
	
	DestroyList(L);
	system("pause");
	return 0;
}