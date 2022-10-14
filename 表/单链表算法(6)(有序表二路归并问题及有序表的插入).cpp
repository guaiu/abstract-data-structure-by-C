#include <stdio.h>
#include <stdlib.h>

/************************/
/*������ʵ�ֶ�·�鲢�㷨*
 *�����������㷨����  */
/************************/


typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;

/* CreateListR:β�巨���������� */
void CreateListR(LinkList *&L, ElemType a[], int n)
{
	LinkList *s, *r;    //sָ���½����ݽڵ㣬rʼ��ָ��β�ڵ�
	int i;
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;  //����ͷ�ڵ�
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

/* DispList:���ڵ㲻Ϊ�գ�������õ����� */
void DispList(LinkList *L)
{
	LinkList *p = L->next;
	while(p!=NULL)
	{
		printf("%d ",p->data); //������ı�����
		p = p->next;
	}
	printf("\n");
}

/* Destroy:���ٵ����� */
void DestroyList(LinkList *&L)
{
	LinkList *pre = L, *p = L->next;  //preָ��p��ǰ���ڵ�
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}

/* ListInsert:�����Ĳ����㷨 */
void ListInsert(LinkList *&L, ElemType e)  //ע�⣬��Ԫ�رض�����ɹ�
{
	LinkList *pre = L, *p;
	while(pre->next != NULL && pre->next->data < e)
		pre = pre->next;
	p = (LinkList*)malloc(sizeof(LinkList));
	p->data = e;
	p->next = pre->next;
	pre->next = p;
}

/* UnionList:������·�鲢�㷨 */
void UnionList(LinkList *LA, LinkList *LB, LinkList *&LC)
{
	LinkList *pa = LA->next, *pb = LB->next, *r, *s;
	LC = (LinkList*)malloc(sizeof(LinkList));
	r = LC;
	while(pa != NULL && pb != NULL)
	{
		if(pa->data < pb->data)
		{
			s = (LinkList*)malloc(sizeof(LinkList));  //β�巨����
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

/* ���������� */
int main()
{
	ElemType a1[5] = {1,3,5,7,9};
	ElemType a2[4] = {2,4,6,8,};
	int n1 = 5;
	int n2 = 4;
	
	LinkList *LA, *LB, *LC;
	CreateListR(LA,a1,n1);
	CreateListR(LB,a2,n2);
	printf("a1ԭ��Ϊ:\n");
	DispList(LA);
	printf("a2ԭ��Ϊ:\n");
	DispList(LB);
	printf("��·�鲢��Ϊ:\n");
	UnionList(LA,LB,LC);
	DispList(LC);
	
	printf("������ԣ����������㷨:\n");
	ElemType e;
	printf("����e���������:\n");
	scanf("%d",&e);
	ListInsert(LC,e);
	printf("�����Ϊ:\n");
	DispList(LC);
	
	
	DestroyList(LA);
	DestroyList(LB);
	DestroyList(LC);
	
	system("pause");
	return 0;
}




















