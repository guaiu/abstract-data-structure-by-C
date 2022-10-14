#include <stdio.h>
#include <stdlib.h>

/************************/
/*单链表实现二路归并算法*
 *及有序表插入算法测试  */
/************************/


typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;

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

/* DispList:若节点不为空，则输出该单链表 */
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

/* Destroy:销毁单链表 */
void DestroyList(LinkList *&L)
{
	LinkList *pre = L, *p = L->next;  //pre指向p的前趋节点
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}

/* ListInsert:有序表的插入算法 */
void ListInsert(LinkList *&L, ElemType e)  //注意，该元素必定插入成功
{
	LinkList *pre = L, *p;
	while(pre->next != NULL && pre->next->data < e)
		pre = pre->next;
	p = (LinkList*)malloc(sizeof(LinkList));
	p->data = e;
	p->next = pre->next;
	pre->next = p;
}

/* UnionList:有序表二路归并算法 */
void UnionList(LinkList *LA, LinkList *LB, LinkList *&LC)
{
	LinkList *pa = LA->next, *pb = LB->next, *r, *s;
	LC = (LinkList*)malloc(sizeof(LinkList));
	r = LC;
	while(pa != NULL && pb != NULL)
	{
		if(pa->data < pb->data)
		{
			s = (LinkList*)malloc(sizeof(LinkList));  //尾插法建表
			s->data = pa->data;
			r->next = s;
			r = s;
			pa = pa->next;
		}
		else
		{
			s = (LinkList*)malloc(sizeof(LinkList));
			s->data = pb->data;
			r->next = s;
			r = s;
			pb = pb->next;
		}
	}
	
	while(pa != NULL)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = pa->data;
		r->next = s;
		r = s;
		pa = pa->next;
	}
	while(pb != NULL)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = pb->data;
		r->next = s;
		r = s;
		pb = pb->next;
	}
	r->next = NULL;
}

/* 测试主程序 */
int main()
{
	ElemType a1[5] = {1,3,5,7,9};
	ElemType a2[4] = {2,4,6,8,};
	int n1 = 5;
	int n2 = 4;
	
	LinkList *LA, *LB, *LC;
	CreateListR(LA,a1,n1);
	CreateListR(LB,a2,n2);
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




















