#include <stdio.h>
#include <stdlib.h>

/****************************************/
/*����һ�����ɺ죨0������ ��1��������2��*
*��������ɫ��������ɵ��������С������ *
*���в��õ�����洢�����һ��ʱ�临�Ӷ� *
*ΪO(n)���㷨��ʹ����Щ���鰴�졢�ס��� *
*��˳���źã����ųɺ�������ͼ��         */
/****************************************/

typedef int ElemType;
typedef struct LNode  //��������������
{
	ElemType data;
	LNode *next;
}LinkList;

/*β�巨��������*/
void CreateListR(LinkList *&L, ElemType a[], int n)
{
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;
	LinkList *r = L, *s;
	for(int i = 0; i < n; i++)
	{
		s = (LinkList*)malloc(sizeof(LinkList));
		s->data = a[i];
		r->next = s;
		r = s;
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

/*���ٵ�����*/
void DestroyList(LinkList *&L)
{
	LinkList *pre = L, *p = L->next;
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}


/*���������㷨*/
void move2(LinkList *&L)
{
	LinkList *L1, *L2, *r, *r1, *r2, *p;  //ע��L1��L2����ͷ�ڵ�,
	L1 = NULL;                            //r(r1,r2)����β�巨����
	L2 = NULL;
	p = L->next;
	r = L;
	
	while(p != NULL)
	{
		if(p->data == 0)
		{r->next = p; r = p;}
	
		else if(p->data == 1)
		{
			if(L1 == NULL)
			{L1 = p; r1 = p;}
			else
			{r1->next = p; r1 = p;}
		}
		
		else //p->data==2
		{
			if(L2 == NULL)
			{L2 = p; r2 = p;}
			else
			{r2->next = p; r2 = p;}
		}
	    p = p->next;
	}
	r->next = r1->next = r2->next = NULL;
	r->next = L1;
	r1->next = L2;
}

/*����������*/
int main()
{
	ElemType a[12] = {1,0,2,1,0,0,1,2,2,1,0,2};
	int n = 12;
	LinkList *L;
	CreateListR(L,a,n);
	printf("ԭ��Ϊ��\n");
	DispList(L);
	
	printf("���㷨���к�Ϊ��\n");
	move2(L);
	DispList(L);
	
	DestroyList(L);
	system("pause");
	return 0;
}