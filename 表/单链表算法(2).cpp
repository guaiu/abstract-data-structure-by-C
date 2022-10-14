#include <stdio.h>
#include <stdlib.h>

/********************************************/
/*������һ����ͷ�ڵ�ĵ�����L={a1,a2,��,an}��*
 *�� ��һ���㷨�����нڵ����ã�����         *
 *L={an��an-1������a1}                       */
/********************************************/

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

/*���õ�����*/
void Reverse(LinkList *&L)
{
	LinkList *p = L->next, *q;  //˼·��������˼��
	L->next = NULL;  //�ֳ�ͷ�ڵ�
	while(p != NULL)
	{
		q = p->next;
		p->next = L->next;  //ͷ�巨����
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
	printf("ԭ��\n");
	DispList(L);
	printf("���ú�\n");
	Reverse(L);
	DispList(L);
	
	DestroyList(L);
	system("pause");
	
	return 0;
}