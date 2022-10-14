#include <stdio.h>
#include <stdlib.h>

/******************/
/*���������ݽṹ����*/
/******************/


typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;

/* CreateListF:ͷ�巨���������� */
void CreateListF(LinkList *&L, ElemType a[], int n)
{
	LinkList *s;  //sָ���½����ݽڵ�
	int i;
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;  //����ͷ�ڵ�
	for(i = 0; i < n; i++)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = a[i];
		s->next = L->next;
		L->next = s;
	}
}

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

/* InitList:�����յ����� */
void InitList(LinkList *&L)
{
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;
}

/* DestroyList:���ٵ����� */
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

/* ListEmpty:�ж��Ƿ�Ϊ�ձ����򷵻��� */
bool ListEmpty(LinkList *L)
{
	return (L->next==NULL);
}

/* ListLength:�����Ա�Ľڵ����(ͷ�ڵ�����0) */
int ListLength(LinkList *L)
{
	int n = 0;
	LinkList *p = L;  //pָ�����ݽڵ㣬��ʼʱָ��ͷ�ڵ㣬n��Ϊ0
	while(p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return n;  //ѭ��������pָ��β�ڵ㣬nΪ�ڵ����
}

/* DispList:��������� */
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

/* GetElem:��������λ��Ϊi������Ԫ�ز�������e��;���Ҳ����򷵻ؼ� */
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

/* LocateElem:Ѱ����eֵ��ȵĵ�һ���ڵ㲢�����߼�λ��;������ʧ���򷵻ؼ� */
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

/* ListInsert:��iλ�ò���һ��Ԫ��ֵΪe�Ľڵ㣬������ʧ���򷵻ؼ� */
bool ListInsert(LinkList *&L, int i, ElemType e)
{
	int j = 0;
	LinkList *p = L, *s; //pָ��ͷ�ڵ㣬j�����ҵ�i-1�ڵ㴦��sָ���½����ڵ�
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

/* ListDelete:ɾ���߼�λ��Ϊi�Ľڵ㲢���ڵ�ֵ�洢��e��;��ɾ��ʧ�ܣ��򷵻ؼ� */
bool ListDelete(LinkList *&L, int i, ElemType &e)
{
	int j = 0;  //�����ҵ�ԭ��i-1���ڵ�
	LinkList *p = L, *q;  //pָ��ԭ��i-1���ڵ㣬qָ��ԭi���ڵ�
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

/*���Ժ���3�����ڲ���GetElem, LocateElem, ListDelete*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	LinkList *L;
	CreateListR(L,a,n);
	printf("ԭ��Ϊ��\n");
	DispList(L);
	
	
	int i = 0;
	ElemType e;
	
	
	printf("����i\n");
	scanf("%d",&i);
	if(GetElem(L,i,e))
		printf("��i��Ԫ����%d\n",e);
	else
		printf("����ʧ�ܣ�\n");
	
	
	
	printf("����e\n");
	scanf("%d",&e);
	printf("ֵΪe�����ݽڵ��ڵ�%dλ\n",LocateElem(L,e));
	
	
	printf("����i\n");
	scanf("%d",&i);
	if(ListDelete(L,i,e))
	{
		printf("ɾ��Ԫ��Ϊ%d,��������Ϊ��\n",e);
		DispList(L);
	}
	else
		printf("ɾ��ʧ�ܣ�\n");
	
	printf("����i\n");
	scanf("%d",&i);
	printf("����e\n");
	scanf("%d",&e);
	if(ListInsert(L,i,e))
	{
		printf("����ɹ���ԭ��Ϊ��\n");
		DispList(L);
	}
	else
		printf("����ʧ�ܣ�\n");
	
	DestroyList(L);
	system("pause");
	return 0;

}
*/

/*���Ժ���2�����ڲ���InitList,ListLength,DispList,ListEmpty*/
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
		printf("L1�޷����");
	DispList(L1);
	if(!ListEmpty(L2))
		DispList(L2);
	else
		printf("L2�޷����");
	DispList(L2);
	
	
	
	DestroyList(L1);
	DestroyList(L2);
	system("pause");
	return 0;
}*/

/*���Ժ���1�����ڲ���CreateListF,CreateListR,DispList*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	LinkList *L1, *L2;
	CreateListF(L1,a,n);
	CreateListR(L2,a,n);
	printf("ͷ�巨:\n");
	DispList(L1);
	printf("β�巨:\n");
	DispList(L2);
	
	DestroyList(L1);
	DestroyList(L2);
	system("pause");
	return 0;
}*/