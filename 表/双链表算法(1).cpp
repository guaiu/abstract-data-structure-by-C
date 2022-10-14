#include <stdio.h>
#include <stdlib.h>

/***********************************************/
/*有一个带头节点的双链表L，设计一个算法将其所  *
 *有元素逆置，即第1个元素变为最后一个元素，第2 *
 *个元素变为倒数 第2个元素，…，最后一个元素变  *
 *为第1个元素                                  */
/***********************************************/

typedef int ElemType;
typedef struct DNode  //双链表数据结构
{
	ElemType data;
	DNode *prior;
	DNode *next;
}DLinkList;

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

/*Reverse:逆置双链表所有元素*/
void Reverse(DLinkList *&L)
{
	DLinkList *p = L->next, *q;
	L->next = NULL;
	while(p != NULL)
	{
		q = p->next;
		p->next = L->next;
		if(L->next != NULL)
			L->next->prior = p;
		L->next = p;
		p->prior = L;
		p = q;
	}
}

/*测试主函数*/
int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	DLinkList *L;
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