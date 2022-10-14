#include <stdio.h>
#include <stdlib.h>

/***********************************************/
/*设计判断带头节点的循环双链表L（含两个以上    *
 *的节点）是否对称相等的算法                   */
/***********************************************/

#define MaxSize 20

typedef int ElemType;
typedef struct DNode  //双链表数据结构
{
	ElemType data;
	DNode *prior;
	DNode *next;
}DLinkList;

/*CreateListR:尾插法建立循环双链表*/
void CreateListR(DLinkList *&L, ElemType a[], int n)
{
	DLinkList *s, *r;
	int i;
	L = (DLinkList*)malloc(sizeof(DLinkList));
	L->prior = L->next = NULL;  //个人改进
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

/*DispList:输出循环双链表*/
void DispList(DLinkList *L)
{
	DLinkList *p = L->next;
	if(p->next != NULL)
	{
		while(p->next != L)
	    {
		    printf("%d ",p->data);  //依据情况具体修改
		    p = p->next;
	    }
	    printf("%d",p->data);
	}
	printf("\n");
}

/*DestroyList:销毁双链表*/
void DestroyList(DLinkList *&L)  //源自个人
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

/*Equal:判断双链表是否对称*/
int Equal(DLinkList *L)
{
	int same = 1;  //标识变量
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

/*测试主程序*/
int main()
{
	int n = 0;
	ElemType a[MaxSize];
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	
	DLinkList *L;
	CreateListR(L,a,n);
	printf("原表为：\n");
	DispList(L);
	if(Equal(L))
		printf("这是对称表\n");
	else
		printf("该表不对称\n");
	
	DestroyList(L);
	system("pause");
	return 0;
}