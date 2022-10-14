#include <stdio.h>
#include <stdlib.h>

/**************************************************/
/*设顺序表L有10个整数。设计一个算法，以第一个元*
 *素为分界线（基准），将所有小于等于它的元素移到*
 *该元素的前面， 将所有大于它的元素移到该元素的后*
 *面。                                         */
 /*************************************************/
 
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
			printf("%d ",L->data[i]);  //视情况修改输出语句
	printf("\n");
}

/* move1:算法一 */
void move1(Sqlist *&L)
{
	int i = 0, j = L->length-1;
	ElemType temp;
	ElemType pivot = L->data[0];  //以data[0]为基准
	while(i < j)
	{
		while(i < j && L->data[j] > pivot)
			j--;  //j从后往前，寻找<=pivot的元素
		while(i < j && L->data[i] <= pivot)
			i++;  //从前往后，寻找>pivot的元素
		if(i < j)
		{
			temp = L->data[i];  //L->data[i]与L->data[j]值交换
			L->data[i] = L->data[j];
			L->data[j] = temp;
		}
	}//上述过程完成最后一次值交换之后必定是j移向i
	temp = L->data[0];  //L->data[0]与L->data[j]值交换
	L->data[0] = L->data[j];
	L->data[j] = temp;
}

/* move2:算法二 */
void move2(Sqlist *&L)
{
	int i = 0, j = L->length-1;
	ElemType pivot = L->data[0];  //以data[0]为基准
	while(i < j)
	{
		while(j > i && L->data[j] > pivot)
			j--;  //从右往左扫描，找一个<=pivot的data[j]
		L->data[i] = L->data[j];  //将其放入data[i]处
		while(i < j && L->data[i] <= pivot)
			i++;  //从左往右扫描，找一个>pivot的记录data[i]
		L->data[j] = L->data[i];  //将其放入data[j]处
	}//上述过程完成最后一次值交换后必定是j移向i,且i处为"空"
	L->data[i] = pivot;  //放置基准
}//算法二的性能比算法一高

int main()
{
	int n = 0;
	ElemType a[MaxSize];
	printf("输入数组的长度，然后依次输入各个元素的值：\n");
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);  //依照情况改变相关语句
	
	printf("\n\n\n执行算法一的结果为：\n");
	Sqlist *L1;
	CreateList(L1,a,n);
	move1(L1);
	DispList(L1);
	DestroyList(L1);
	L1 = NULL;
	
	printf("\n\n\n执行算法二的结果为： \n");
	Sqlist *L2;
	CreateList(L2,a,n);
	move2(L2);
	DispList(L2);
	DestroyList(L2);
	L2 = NULL;
	
	return 0;
}