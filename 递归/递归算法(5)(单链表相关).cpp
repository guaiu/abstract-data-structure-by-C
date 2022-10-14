#include <stdio.h>
#include <stdlib.h>

/**************************************/
/*��Ʋ���ͷ�ڵ�ĵ��������صݹ��㷨*/
/**************************************/

#define MaxSize 10
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;

/*CreateListR:β�巨����������*/
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

/*DestroyList:�ݹ鷨���ٵ�����*/
void DestroyList(LinkList *&L)
{
	if(L == NULL)
		return ;
	else
	{
		DestroyList(L->next);
		free(L);
	}
}//��Ȼ������㷨�ǵ�Ч��

/*ListLength:�ݹ鷨��������*/
int ListLength(LinkList *&L)
{
	if(L == NULL)
		return 0;
	else
		return ListLength(L->next)+1;
}//д�����ܼ�

/*DispListF:�����ӡ����������Ԫ��ֵ*/
void DispListF(LinkList *&L)
{
	if(L == NULL)
		return ;
	else
	{
		printf("%d ",L->data);
		DispListF(L->next);
	}
}

/*DispListR:�����ӡ����������Ԫ��ֵ*/
void DispListR(LinkList *&L)
{
	if(L == NULL)
		return ;
	else
	{
		DispListR(L->next);
		printf("%d ",L->data);
	}
}


/*����������*/
int main()
{
	ElemType arr[MaxSize] = {1,2,3,4,5,6,7,8,9,10};
	LinkList *L, *L1;
	CreateListR(L,arr,MaxSize);
	L1 = L->next;     //L1ָ��һ������ͷ�ڵ�ĵ�����
	
	printf("�����ȣ�%d\n",ListLength(L1));
	printf("�����ӡ��");
	DispListF(L1);
	printf("\n");
	printf("�����ӡ��");
	DispListR(L1);
	printf("\n");
	
	DestroyList(L1);
	system("pause");
	return 0;
}