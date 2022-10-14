#include <stdio.h>
#include <stdlib.h>

/******************/
/* 双链表结构尝试 */
/******************/

typedef int ElemType;
typedef struct DNode  //双链表数据结构
{
	ElemType data;
	DNode *prior;
	DNode *next;
}DLinkList;

/*CreateListF:头插法建立双链表*/
void CreateListF(DLinkList *&L, ElemType a[], int n)
{
	DLinkList *s;
	int i;
	L = (DLinkList*)malloc(sizeof(DLinkList));
	L->prior = L->next = NULL;
	for(i = 0; i < n; i++)
	{
		s = (DLinkList*)malloc(sizeof(DLinkList));
		s->data = a[i];
		s->next = L->next;
		if(L->next != NULL)
			L->next->prior = s;
		L->next = s;
		s->prior = L;
	}
}

/*CreateListR:尾插法建立双链表*/
void CreateListR(DLinkList *&L, ElemType a[], int n)
{
	DLinkList *s, *r;
	int i;
	L = (DLinkList*)malloc(sizeof(DLinkList));
	L->prior = L->next = NULL;  //个人改进
	r = L;
	for(i = 0; i < n; i++)
	{
		s = (DLinkList*)malloc(sizeof(DLinkList));
		s->data = a[i];
		r->next = s;
		s->prior = r;
		r = s;
	}
	r->next = NULL;
}

/*ListInsert:双链表插入插入算法*/
bool ListInsert(DLinkList *&L, int i, ElemType e)
{
	int j = 0;
	DLinkList *p = L, *s;  //p、j用于遍历，s用于指向新节点
	while(j < i-1 && p != NULL)  //查找第i-1个节点
	{
		j++;
		p = p->next;
	}
	if(p == NULL)
		return false;
	else
	{
		s = (DLinkList*)malloc(sizeof(DLinkList));
		s->data = e;
		s->next = p->next;
		if(p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

/*ListDelete:双链表删除算法*/
bool ListDelete(DLinkList *&L, int i, ElemType &e)
{
	int j = 0;
    DLinkList *p = L, *q;  //p、j用于遍历，q用于记录p->next(第i个节点)
	while(j < i-1 && p != NULL)
	{
		j++;
		p = p->next;
	}
	if(p == NULL)  //如果找不到i-1个节点
		return false;
	else
	{
		q = p->next;
		if(q == NULL)  //如果找不到i节点
			return false;
		e = q->data;
		p->next = q->next;
		if(p->next != NULL)
			p->next->prior = p;
		free(q);
		return true;
	}
}

/*InitList:初始化双链表*/
void InitList(DLinkList *&L)
{
	L = (DLinkList*)malloc(sizeof(DLinkList));
	L->prior = L->next = NULL;
}

/*DestroyList:销毁双链表*/
void DestroyList(DLinkList *&L)  //源自个人
{
	DLinkList *p = L;
	while(p->next != NULL)
	{
		p = p->next;
		free(p->prior);
	}
	free(p);
}

/*ListEmpty:判断双链表是否为空*/
bool ListEmpty(DLinkList *L)
{
	return (L->next == NULL);
}

/*ListLength:求双链表长度*/
int ListLength(DLinkList *L)
{
	int n = 0;
	DLinkList *p = L;
	while(p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return (n);
}

/*DispList:输出双链表*/
void DispList(DLinkList *L)
{
	DLinkList *p = L->next;
	while(p != NULL)
	{
		printf("%d ",p->data);  //依据情况具体修改
		p = p->next;
	}
	printf("\n");
}

/*GetElem:求双链表中位置i的数据元素的值*/
bool GetElem(DLinkList *L, int i, ElemType &e)
{
	int j;
	DLinkList *p = L;
	while(j < i && p != NULL)  //寻找第i-1个元素
	{
		j++;
		p = p->next;
	}
	if(p == NULL)
		return false;
	else
	{
		e = p->data;
		return true;
	}
}

/*LocateElem:按元素值查找该元素的逻辑下标*/
int LocateElem(DLinkList *L, ElemType e)
{
	int i = 1;
	DLinkList *p = L->next;
	while(p != NULL && p->data != e)
	{
		p = p->next;
		i++;
	}
	if(p == NULL)
		return 0;
	else
		return (i);
}

/*测试函数3，用于测试GetElem, LocateElem, ListDelete*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	DLinkList *L;
	CreateListR(L,a,n);
	printf("原表为：\n");
	DispList(L);
	
	int i = 0;
	ElemType e;
	
	printf("输入i\n");
	scanf("%d",&i);
	if(GetElem(L,i,e))
		printf("第i个元素是%d\n",e);
	else
		printf("查找失败！\n");
	
	
	printf("输入e\n");
	scanf("%d",&e);
	printf("值为e的数据节点在第%d位\n",LocateElem(L,e));
	
	printf("输入i\n");
	scanf("%d",&i);
	if(ListDelete(L,i,e))
	{
		printf("删除元素为%d,链表现在为：\n",e);
		DispList(L);
	}
	else
		printf("删除失败！\n");
	
	printf("输入i\n");
	scanf("%d",&i);
	printf("输入e\n");
	scanf("%d",&e);
	if(ListInsert(L,i,e))
	{
		printf("插入成功，原表为：\n");
		DispList(L);
	}
	else
		printf("插入失败！\n");
	
	DestroyList(L);
	system("pause");
	return 0;
}*/

/*测试函数2，用于测试InitList,ListLength,DispList,ListEmpty*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	DLinkList *L1, *L2;
	CreateListR(L1,a,n);
	InitList(L2);
	
	printf("%d %d\n",ListLength(L1),ListLength(L2));
	
	if(!ListEmpty(L1))
		DispList(L1);
	else
		printf("L1无法输出");
	DispList(L1);
	if(!ListEmpty(L2))
		DispList(L2);
	else
		printf("L2无法输出");
	DispList(L2);
	
	
	
	DestroyList(L1);
	DestroyList(L2);
	system("pause");
	return 0;
}*/

/*测试函数1，用于测试CreateListF,CreateListR,DispList*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	DLinkList *L1, *L2;
	CreateListF(L1,a,n);
	CreateListR(L2,a,n);
	printf("头插法:\n");
	DispList(L1);
	printf("尾插法:\n");
	DispList(L2);
	
	DestroyList(L1);
	DestroyList(L2);
	system("pause");
	return 0;
}*/

/*空主函数*/
int main()
{
	system("pause");
	return 0;
}