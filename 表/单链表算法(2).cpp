#include <stdio.h>
#include <stdlib.h>

/********************************************/
/*假设有一个带头节点的单链表L={a1,a2,…,an}。*
 *设 计一个算法将所有节点逆置，即：         *
 *L={an，an-1，…，a1}                       */
/********************************************/

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

/*逆置单链表*/
void Reverse(LinkList *&L)
{
	LinkList *p = L->next, *q;  //思路：分链的思想
	L->next = NULL;  //分出头节点
	while(p != NULL)
	{
		q = p->next;
		p->next = L->next;  //头插法建表
		L->next = p;
		p = q;
	}
}

int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	LinkList *L;
	CreateListR(L,a,n);
	printf("原表：\n");
	DispList(L);
	printf("逆置后：\n");
	Reverse(L);
	DispList(L);
	
	DestroyList(L);
	system("pause");
	
	return 0;
}