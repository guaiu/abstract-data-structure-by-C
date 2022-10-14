#include <stdio.h>
#include <stdlib.h>


/*********************************/
/*线性表应用-两个表的自然连接问题*/
/*********************************/

#define MaxCol 10  //最大列数
typedef int ElemType;
typedef struct Node1  //数据节点类型
{
	ElemType data[MaxCol];
	struct Node1 *next;
}DList;

typedef struct Node2  //头节点类型
{
	int Row, Col;
	DList *next;
}HList;

/*CreateTable:交互式创建单链表*/
void CreateTable(HList *&h)
{
	int i, j;
	DList *r, *s;
	h = (HList*)malloc(sizeof(HList));
	h->next = NULL;
	printf("表的行数，列数：\n");
	scanf("%d %d",&h->Row, &h->Col);
	for(i = 0; i < h->Row; i++)
	{
		printf("第%d行：\n",i+1);
		s = (DList*)malloc(sizeof(DList));
		for(j = 0; j < h->Col; j++)
			scanf("%d",&s->data[j]);
		if(h->next == NULL)  //尾插法建表
		    h->next = s;
		else
			r->next = s;
		r = s;	
	}
	r->next = NULL;
}

/*DestroyTable:销毁单链表*/
void DestroyTable(HList *&h)
{
	DList *pre = h->next, *p = pre->next;  //注意头节点和数据节点为不同类型
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
	free(h);
}

/*DispTable:输出单链表*/
void DispTable(HList *h)
{
	int j;
	DList *p = h->next;
	while(p != NULL)
	{
		for(j = 0; j < h->Col; j++)
			printf("%4d",p->data[j]);
		printf("\n");
		p = p->next;
	}
}

/*LinkTable:表连接算法*/
void LinkTable(HList *h1, HList *h2, HList *&h)
{
	int i, j, k;
	DList *p = h1->next, *q, *s, *r;
	
	printf("连接字段是:第一个表序号，第二个表序号:");
	scanf("%d %d",&i,&j);
	
	h = (HList*)malloc(sizeof(HList));
	h->next = NULL;
	h->Row = 0;
	h->Col = h1->Col+h2->Col;
	
	while(p != NULL)  //扫描表1
	{
		q = h2->next;
		while(q != NULL)  //扫描表2
		{
			if(p->data[i-1] == q->data[j-1])
			{
				s = (DList*)malloc(sizeof(DList));
				for(k = 0; k < h1->Col; k++)
					s->data[k] = p->data[k];
				for(k = 0; k < h2->Col; k++)
					s->data[h1->Col+k] = q->data[k];
				
				if(h->next == NULL)  //尾插法建表
					h->next = s;
				else
					r->next = s;
				r = s;
				h->Row++;
			}
			q = q->next;
		}
		p = p->next;
	}
	r->next = NULL;
}

/*测试主函数*/
int main()
{
	HList *h1, *h2, *h;
	printf("表1:\n");
	CreateTable(h1);
	printf("表2:\n");
	CreateTable(h2);
	LinkTable(h1,h2,h);
	printf("连接结果表:\n");
	DispTable(h);
	DestroyTable(h1);
	DestroyTable(h2);
	DestroyTable(h);
	
	return 0;
}