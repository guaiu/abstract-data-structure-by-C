#include <stdio.h>
#include <stdlib.h>

/******************/
/* ˫����ṹ���� */
/******************/

typedef int ElemType;
typedef struct DNode  //˫�������ݽṹ
{
	ElemType data;
	DNode *prior;
	DNode *next;
}DLinkList;

/*CreateListF:ͷ�巨����˫����*/
void CreateListF(DLinkList *&L, ElemType a[], int n)
{
	DLinkList *s;
	int i;
	L = (DLinkList*)malloc(sizeof(DLinkList));
	L->prior = L->next = NULL;
	for(i = 0; i < n; i++)
	{
		s = (DLinkList*)malloc(sizeof(DLinkList));
		s->data = a[i];
		s->next = L->next;
		if(L->next != NULL)
			L->next->prior = s;
		L->next = s;
		s->prior = L;
	}
}

/*CreateListR:β�巨����˫����*/
void CreateListR(DLinkList *&L, ElemType a[], int n)
{
	DLinkList *s, *r;
	int i;
	L = (DLinkList*)malloc(sizeof(DLinkList));
	L->prior = L->next = NULL;  //���˸Ľ�
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

/*ListInsert:˫�����������㷨*/
bool ListInsert(DLinkList *&L, int i, ElemType e)
{
	int j = 0;
	DLinkList *p = L, *s;  //p��j���ڱ�����s����ָ���½ڵ�
	while(j < i-1 && p != NULL)  //���ҵ�i-1���ڵ�
	{
		j++;
		p = p->next;
	}
	if(p == NULL)
		return false;
	else
	{
		s = (DLinkList*)malloc(sizeof(DLinkList));
		s->data = e;
		s->next = p->next;
		if(p->next != NULL)
			p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
}

/*ListDelete:˫����ɾ���㷨*/
bool ListDelete(DLinkList *&L, int i, ElemType &e)
{
	int j = 0;
    DLinkList *p = L, *q;  //p��j���ڱ�����q���ڼ�¼p->next(��i���ڵ�)
	while(j < i-1 && p != NULL)
	{
		j++;
		p = p->next;
	}
	if(p == NULL)  //����Ҳ���i-1���ڵ�
		return false;
	else
	{
		q = p->next;
		if(q == NULL)  //����Ҳ���i�ڵ�
			return false;
		e = q->data;
		p->next = q->next;
		if(p->next != NULL)
			p->next->prior = p;
		free(q);
		return true;
	}
}

/*InitList:��ʼ��˫����*/
void InitList(DLinkList *&L)
{
	L = (DLinkList*)malloc(sizeof(DLinkList));
	L->prior = L->next = NULL;
}

/*DestroyList:����˫����*/
void DestroyList(DLinkList *&L)  //Դ�Ը���
{
	DLinkList *p = L;
	while(p->next != NULL)
	{
		p = p->next;
		free(p->prior);
	}
	free(p);
}

/*ListEmpty:�ж�˫�����Ƿ�Ϊ��*/
bool ListEmpty(DLinkList *L)
{
	return (L->next == NULL);
}

/*ListLength:��˫������*/
int ListLength(DLinkList *L)
{
	int n = 0;
	DLinkList *p = L;
	while(p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return (n);
}

/*DispList:���˫����*/
void DispList(DLinkList *L)
{
	DLinkList *p = L->next;
	while(p != NULL)
	{
		printf("%d ",p->data);  //������������޸�
		p = p->next;
	}
	printf("\n");
}

/*GetElem:��˫������λ��i������Ԫ�ص�ֵ*/
bool GetElem(DLinkList *L, int i, ElemType &e)
{
	int j;
	DLinkList *p = L;
	while(j < i && p != NULL)  //Ѱ�ҵ�i-1��Ԫ��
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

/*LocateElem:��Ԫ��ֵ���Ҹ�Ԫ�ص��߼��±�*/
int LocateElem(DLinkList *L, ElemType e)
{
	int i = 1;
	DLinkList *p = L->next;
	while(p != NULL && p->data != e)
	{
		p = p->next;
		i++;
	}
	if(p == NULL)
		return 0;
	else
		return (i);
}

/*���Ժ���3�����ڲ���GetElem, LocateElem, ListDelete*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	DLinkList *L;
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
}*/

/*���Ժ���2�����ڲ���InitList,ListLength,DispList,ListEmpty*/
/*int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	DLinkList *L1, *L2;
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
	DLinkList *L1, *L2;
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

/*��������*/
int main()
{
	system("pause");
	return 0;
}