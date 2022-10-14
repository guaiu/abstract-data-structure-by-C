#include <stdio.h>
#include <stdlib.h>

/****************************************************/
/*特殊链队数据结构尝试:                             *
 *采用一个不带头节点只有一个尾节点指针rear的循环    *
 *单链表存储队列，设计队列的初始化、进队和出队等算法*/
/****************************************************/

/*               算法描述                  */
/*
  链队通过尾节点指针rear唯一标识
  rear->next将指向队头  
  四要素：  
  队空条件：rear=NULL
  队满条件：不考虑
  进队e操作：将包含e的节点插入到单链表表尾
  出队操作：删除单链表首节点                
                                            */
/*                                          */

#define MaxSize 20
typedef int ElemType;
typedef struct qnode  //数据节点
{
	ElemType data;
	struct qnode *next;
}QNode,LiQueue;

/*InitQueue:队列初始化*/
void InitQueue(LiQueue *&rear)
{
	rear = NULL;
}

/*QueueEmpty:判断队列是否为空，是则返回true*/
bool QueueEmpty(LiQueue *rear)
{
	return (rear == NULL);
}

/*DestroyQueue:销毁队列*/
void DestroyQueue(LiQueue *&rear)
{
	LiQueue *q;
	if(rear == NULL)
		return ;
	while(rear->next != rear)
	{
		q = rear->next;
		rear->next = q->next;
		free(q);
	}
	free(rear);
}

/*enQueue:入队*/
void enQueue(LiQueue *&rear, ElemType e)
{
	LiQueue *p;
	p = (LiQueue*)malloc(sizeof(LiQueue));
	p->data = e;
	if(rear == NULL)
	{
		p->next = p;
		rear = p;
	}
	else
	{
		p->next = rear->next;
		rear->next = p;
		rear = p;
	}
}

/*deQueue:出队*/
bool deQueue(LiQueue *&rear, ElemType &e)
{
	LiQueue *q;
	if(rear == NULL)
		return false;
	else if(rear->next == rear)
	{
		e = rear->data;
		free(rear);
		rear = NULL;
	}
	else
	{
		q = rear->next;
		e = q->data;
		rear->next = q->next;
		free(q);
	}
	return true;
}

/*enTest:测试入队列操作*/
void enTest(LiQueue *&q,ElemType e)
{
	LiQueue *p;
	enQueue(q,e);
	p = q;
	printf("入队成功，入队元素为%d\n",p->data);
}

/*deTest:测试出队列操作*/
void deTest(LiQueue *&q, ElemType &e)
{
	(deQueue(q,e))?(printf("出队成功，出队元素为%d\n",e)):(printf("下溢出，无法出队\n"));
}

/*ComomonTest:通用测试*/
void ComomonTest(LiQueue *q)
{
	(QueueEmpty(q))?(printf("队列为空\n")):(printf("队列不为空\n"));
}

/*测试主程序*/
int main()
{
	ElemType e;
	LiQueue *q;
	InitQueue(q);
	
	/*空队测试*/
	e = 0;
	ComomonTest(q);
	deTest(q,e);
	enTest(q,e);
	
	/*一般队测试(两次)*/
	e = 1;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	e = 2;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	/*销毁队*/
	printf("队列已销毁\n");
	DestroyQueue(q);
	
	
	system("pause");
	return 0;	
}


























 