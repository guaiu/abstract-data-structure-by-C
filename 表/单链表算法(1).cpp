#include <stdio.h>
#include <stdlib.h>

/******************************************/
/*设计一个算法，删除一个单链表L中元素     *
 *值最大的 节点（假设最大值节点是唯一的） */
/******************************************/

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

/*删除单链中的最大元素（假设该元素唯一）*/
void delmaxnode(LinkList *&L)
{
	LinkList *p = L->next, *pre = L, *maxp = p, *maxpre = pre;
	while(p != NULL)
	{
		if(maxp->data<p->data)  //找到值更大的节点则进行变换
		{
			maxp = p;
			maxpre = pre;
		}
		pre = p;
		p = p->next;
	}
	
	maxpre->next = maxp->next;
	free(maxp);
}

/*测试主程序*/
int main()
{
	ElemType a[5] = {3,1,5,8,0};
	int n = 5;
	LinkList *L;
	CreateListR(L,a,n);
	printf("原表为:\n");
	DispList(L);
	printf("删除最大元素后为:\n");
	delmaxnode(L);
	DispList(L);
	
	DestroyList(L);
	return 0;
}