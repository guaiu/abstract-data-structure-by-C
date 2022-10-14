#include <stdio.h>
#include <stdlib.h>

/******************************************/
/*���һ���㷨��ɾ��һ��������L��Ԫ��     *
 *ֵ���� �ڵ㣨�������ֵ�ڵ���Ψһ�ģ� */
/******************************************/

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

/*ɾ�������е����Ԫ�أ������Ԫ��Ψһ��*/
void delmaxnode(LinkList *&L)
{
	LinkList *p = L->next, *pre = L, *maxp = p, *maxpre = pre;
	while(p != NULL)
	{
		if(maxp->data<p->data)  //�ҵ�ֵ����Ľڵ�����б任
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

/*����������*/
int main()
{
	ElemType a[5] = {3,1,5,8,0};
	int n = 5;
	LinkList *L;
	CreateListR(L,a,n);
	printf("ԭ��Ϊ:\n");
	DispList(L);
	printf("ɾ�����Ԫ�غ�Ϊ:\n");
	delmaxnode(L);
	DispList(L);
	
	DestroyList(L);
	return 0;
}