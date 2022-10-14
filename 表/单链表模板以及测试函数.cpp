#include <stdio.h>
#include <stdlib.h>

/******************/
/*单链表数据结构尝试*/
/******************/


typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;

/* CreateListF:头插法建立单链表 */
void CreateListF(LinkList *&L, ElemType a[], int n)
{
	LinkList *s;  //s指向新建数据节点
	int i;
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;  //创建头节点
	for(i = 0; i < n; i++)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

/* CreateListR:尾插法建立单链表 */
void CreateListR(LinkList *&L, ElemType a[], int n)
{
	LinkList *s, *r;    //s指向新建数据节点，r始终指向尾节点
	int i;
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;  //创建头节点
	r = L;
	for(i = 0; i < n; i++)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = a[i];
		r->next = s;
		r = s;
	}
	r->next = NULL;
}

/* InitList:建立空单链表 */
void InitList(LinkList *&L)
{
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;
}

/* DestroyList:销毁单链表 */
void DestroyList(LinkList *&L)
{
	LinkList *pre = L, *p = L->next;  //pre指向p的前驱节点
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}

/* ListEmpty:判断是否为空表，是则返回真 */
bool ListEmpty(LinkList *L)
{
	return (L->next==NULL);
}

/* ListLength:求线性表的节点个数(头节点算作0) */
int ListLength(LinkList *L)
{
	int n = 0;
	LinkList *p = L;  //p指向数据节点，开始时指向头节点，n置为0
	while(p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return n;  //循环结束，p指向尾节点，n为节点个数
}

/* DispList:输出单链表 */
void DispList(LinkList *L)
{
	LinkList *p = L->next;
	while(p!=NULL)
	{
		printf("%d ",p->data); //视情况改变该语句
		p = p->next;
	}
	printf("\n");
}

/* GetElem:求单链表中位置为i的数据元素并储存在e中;若找不到则返回假 */
bool GetElem(LinkList *L, int i, ElemType &e)
{
	int j = 0;
	LinkList *p = L;
	while(j < i && p != NULL)
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

/* LocateElem:寻找与e值相等的第一个节点并返回逻辑位置;若查找失败则返回假 */
int LocateElem(LinkList *L, ElemType e)
{
	int i = 1;
	LinkList *p = L->next;
	while(p != NULL && p->data != e)
	{
		p = p->next;
		i++;
	}
	if(p == NULL)
		return false;
	else
		return i;
}

/* ListInsert:在i位置插入一个元素值为e的节点，若插入失败则返回假 */
bool ListInsert(LinkList *&L, int i, ElemType e)
{
	int j = 0;
	LinkList *p = L, *s; //p指向头节点，j用于找到i-1节点处，s指向新建立节点
	while(j < i-1 && p != NULL)
	{
		j++;
		p = p->next;
	}
	if(p == NULL)
		return false;
	else
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}
}

/* ListDelete:删除逻辑位置为i的节点并将节点值存储在e中;若删除失败，则返回假 */
bool ListDelete(LinkList *&L, int i, ElemType &e)
{
	int j = 0;  //用于找到原第i-1个节点
	LinkList *p = L, *q;  //p指向原第i-1个节点，q指向原i个节点
	while(j < i-1 && p!= NULL)
	{
		j++;
		p = p->next;
	}
	if(p == NULL)
		return false;
	else
	{
		q = p->next;
		if(q == NULL)
			return false;
		e = q->data;
		p->next = q->next;
		free(q);
		return true;
	}
}

int main()
{
	system("pause");
	return 0;
}

/*测试函数3，用于测试GetElem, LocateElem, ListDelete*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	LinkList *L;
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

}
*/

/*测试函数2，用于测试InitList,ListLength,DispList,ListEmpty*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	LinkList *L1, *L2;
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
	LinkList *L1, *L2;
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