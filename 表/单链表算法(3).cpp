#include <stdio.h>
#include <stdlib.h>

/************************************************/
/*假设有一个带头节点的单链表L={a1，b1，a2，     *
 *b2，…，an，bn}。设计一个算法将其拆分成两个    *
 *带头节点的单链表 L1和L2： L1={a1，a2，…，an}，*
 *L2={bn，bn-1，…，b1} 要求L1使用L的头节点。    */
/************************************************/

typedef int ElemType;
typedef struct LNode  //单链表数据类型
{
	ElemType data;
    LNode *next;
}LinkList;

/*尾接法建表*/
void CreateListR(LinkList *&L, ElemType a[], int n)
{
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;
	LinkList *s, *r = L;
	for(int i = 0; i < n; i++)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = a[i];
		r->next = s;
		r = r->next;
	}
	r->next = NULL; 
}

/*头插法建表*/
void CreateListF(LinkList *&L, ElemType a[], int n)
{
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;
	LinkList *s;
	for(int i = 0; i < n; i++)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

/*输出单链表*/
void DispList(LinkList *L)
{
	LinkList *p = L->next;
	while(p != NULL)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
}

/*销毁链表*/
void DestroyList(LinkList *L)
{
	LinkList *p = L->next, *pre = L;
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre); 
}

/*拆分单链表*/
void split(LinkList *&L, LinkList *&L1, LinkList *&L2)  //L1尾插法，L2头插法 
{
	LinkList *p = L->next, *q, *r1;  //p,q用于遍历单链表元素，r1用于尾插法建表
	L1 = L;  //L1利用原来L的头节点
	r1 = L1;
	L2 = (LinkList*)malloc(sizeof(LinkList));
	L2->next = NULL;
	
	while(p != NULL)
	{
		r1->next = p;  //尾插
		r1 = p;
		p = p->next;
		q = p->next;  //头插
		p->next = L2->next;
		L2->next = p;
		p = q;
	}
	r1->next = NULL;
}

int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	LinkList *L;
	CreateListR(L,a,n);
	printf("原表为：\n");
	DispList(L);
	
	printf("拆分后L1，L2分别为：\n");
	LinkList *L1, *L2;
	split(L,L1,L2);
	DispList(L1);
	DispList(L2);
	
	
	DestroyList(L1);
	DestroyList(L2);
	
	system("pause");
	return 0;	
}