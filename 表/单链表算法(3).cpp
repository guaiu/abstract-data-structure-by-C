#include <stdio.h>
#include <stdlib.h>

/************************************************/
/*������һ����ͷ�ڵ�ĵ�����L={a1��b1��a2��     *
 *b2������an��bn}�����һ���㷨�����ֳ�����    *
 *��ͷ�ڵ�ĵ����� L1��L2�� L1={a1��a2������an}��*
 *L2={bn��bn-1������b1} Ҫ��L1ʹ��L��ͷ�ڵ㡣    */
/************************************************/

typedef int ElemType;
typedef struct LNode  //��������������
{
	ElemType data;
    LNode *next;
}LinkList;

/*β�ӷ�����*/
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

/*ͷ�巨����*/
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

/*���������*/
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

/*��������*/
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

/*��ֵ�����*/
void split(LinkList *&L, LinkList *&L1, LinkList *&L2)  //L1β�巨��L2ͷ�巨 
{
	LinkList *p = L->next, *q, *r1;  //p,q���ڱ���������Ԫ�أ�r1����β�巨����
	L1 = L;  //L1����ԭ��L��ͷ�ڵ�
	r1 = L1;
	L2 = (LinkList*)malloc(sizeof(LinkList));
	L2->next = NULL;
	
	while(p != NULL)
	{
		r1->next = p;  //β��
		r1 = p;
		p = p->next;
		q = p->next;  //ͷ��
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
	printf("ԭ��Ϊ��\n");
	DispList(L);
	
	printf("��ֺ�L1��L2�ֱ�Ϊ��\n");
	LinkList *L1, *L2;
	split(L,L1,L2);
	DispList(L1);
	DispList(L2);
	
	
	DestroyList(L1);
	DestroyList(L2);
	
	system("pause");
	return 0;	
}