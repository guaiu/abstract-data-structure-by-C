#include <stdio.h>
#include <stdlib.h>

/**************************************/
/*设计不带头节点的单链表的相关递归算法*/
/**************************************/

#define MaxSize 10
typedef int ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LinkList;

/*CreateListR:尾插法建立单链表*/
void CreateListR(LinkList *&L, ElemType a[], int n)
{
	LinkList *s, *r;    //s指向新建数据节点，r始终指向尾节点
	int i;
	L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;  //创建头节点
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

/*DestroyList:递归法销毁单链表*/
void DestroyList(LinkList *&L)
{
	if(L == NULL)
		return ;
	else
	{
		DestroyList(L->next);
		free(L);
	}
}//当然，这个算法是低效的

/*ListLength:递归法求单链表长度*/
int ListLength(LinkList *&L)
{
	if(L == NULL)
		return 0;
	else
		return ListLength(L->next)+1;
}//写起来很简单

/*DispListF:正序打印单链表所有元素值*/
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

/*DispListR:逆序打印单链表所有元素值*/
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


/*测试主函数*/
int main()
{
	ElemType arr[MaxSize] = {1,2,3,4,5,6,7,8,9,10};
	LinkList *L, *L1;
	CreateListR(L,arr,MaxSize);
	L1 = L->next;     //L1指向一个不带头节点的单链表
	
	printf("链表长度：%d\n",ListLength(L1));
	printf("正序打印：");
	DispListF(L1);
	printf("\n");
	printf("逆序打印：");
	DispListR(L1);
	printf("\n");
	
	DestroyList(L1);
	system("pause");
	return 0;
}