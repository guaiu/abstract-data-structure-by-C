#include <stdio.h>
#include <stdlib.h>

/***********************************************/
/*����жϴ�ͷ�ڵ��ѭ��˫����L������������    *
 *�Ľڵ㣩�Ƿ�Գ���ȵ��㷨                   */
/***********************************************/

#define MaxSize 20

typedef int ElemType;
typedef struct DNode  //˫�������ݽṹ
{
	ElemType data;
	DNode *prior;
	DNode *next;
}DLinkList;

/*CreateListR:β�巨����ѭ��˫����*/
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
	r->next = L;
	L->prior = r;
}

/*DispList:���ѭ��˫����*/
void DispList(DLinkList *L)
{
	DLinkList *p = L->next;
	if(p->next != NULL)
	{
		while(p->next != L)
	    {
		    printf("%d ",p->data);  //������������޸�
		    p = p->next;
	    }
	    printf("%d",p->data);
	}
	printf("\n");
}

/*DestroyList:����˫����*/
void DestroyList(DLinkList *&L)  //Դ�Ը���
{
	DLinkList *p = L;
	if(p->next != NULL)
	    while(p->next != L)
	    {
		    p = p->next;
		    free(p->prior);
	    }
	free(p);
}

/*Equal:�ж�˫�����Ƿ�Գ�*/
int Equal(DLinkList *L)
{
	int same = 1;  //��ʶ����
	DLinkList *p = L->next, *q = L->prior;
	while(same == 1)
	{
		if(p->data != q->data)
			same = 0;
		else
		{
			if(p == q || p == q->prior)
				break;
			q = q->prior;
			p = p->next;
		}
	}
	return same;
}

/*����������*/
int main()
{
	int n = 0;
	ElemType a[MaxSize];
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	
	DLinkList *L;
	CreateListR(L,a,n);
	printf("ԭ��Ϊ��\n");
	DispList(L);
	if(Equal(L))
		printf("���ǶԳƱ�\n");
	else
		printf("�ñ��Գ�\n");
	
	DestroyList(L);
	system("pause");
	return 0;
}