#include <stdio.h>
#include <stdlib.h>

/****************************************/
/*设有一个仅由红（0）、白 （1）、兰（2）*
*这三种颜色的条块组成的条块序列。假设该 *
*序列采用单链表存储，设计一个时间复杂度 *
*为O(n)的算法，使得这些条块按红、白、兰 *
*的顺序排好，即排成荷兰国旗图案         */
/****************************************/

typedef int ElemType;
typedef struct LNode  //单链表数据类型
{
	ElemType data;
	LNode *next;
}LinkList;

/*尾插法建单链表*/
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

/*输出单链表*/
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

/*销毁单链表*/
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


/*荷兰国旗算法*/
void move2(LinkList *&L)
{
	LinkList *L1, *L2, *r, *r1, *r2, *p;  //注意L1和L2不带头节点,
	L1 = NULL;                            //r(r1,r2)用于尾插法建表
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

/*测试主程序*/
int main()
{
	ElemType a[12] = {1,0,2,1,0,0,1,2,2,1,0,2};
	int n = 12;
	LinkList *L;
	CreateListR(L,a,n);
	printf("原表为：\n");
	DispList(L);
	
	printf("经算法排列后为：\n");
	move2(L);
	DispList(L);
	
	DestroyList(L);
	system("pause");
	return 0;
}