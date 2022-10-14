#include <stdio.h>
#include <stdlib.h>

/***********************************************/
/*��һ����ͷ�ڵ��˫����L�����һ���㷨������  *
 *��Ԫ�����ã�����1��Ԫ�ر�Ϊ���һ��Ԫ�أ���2 *
 *��Ԫ�ر�Ϊ���� ��2��Ԫ�أ��������һ��Ԫ�ر�  *
 *Ϊ��1��Ԫ��                                  */
/***********************************************/

typedef int ElemType;
typedef struct DNode  //˫�������ݽṹ
{
	ElemType data;
	DNode *prior;
	DNode *next;
}DLinkList;

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

/*Reverse:����˫��������Ԫ��*/
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

/*����������*/
int main()
{
	ElemType a[10] = {1,2,3,4,5,6,7,8,9,10};
	int n = 10;
	DLinkList *L;
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