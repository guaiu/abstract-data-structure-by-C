#include <stdio.h>
#include <stdlib.h>

/******************/
/*链队数据结构尝试*/
/******************/

/*           链队的四要素            */
/*
  队空：front=rear=NULL;
  队满：不考虑
  入队e：将包含e的节点插入单链表表尾
  出队e：删除单链表首数据节点         
                                      */
/*                                    */

#define MaxSize 20
typedef int ElemType;
typedef struct qnode  //数据节点类型
{
	ElemType data;
	struct qnode *next;
}QNode;

typedef struct     //头节点类型
{
	QNode *front;  //队头
	QNode *rear;   //队尾
}LiQueue;

/*InitQueue:初始化队列*/
void InitQueue(LiQueue *&q)
{
	q = (LiQueue*)malloc(sizeof(LiQueue));
	q->front = q->rear = NULL;
}

/*DestroyQueue;销毁队列*/
void DestroyQueue(LiQueue *&q)
{
	QNode *p = q->front, *r;
	if(p != NULL)
	{
		r = p->next;
		while(r != NULL)
		{
			free(p);
			p = r; r = p->next;
		}
	}
	free(p);free(q);
}

/*QueueEmpty:判断队列是否为空，是则返回true*/
bool QueueEmpty(LiQueue *q)
{
	return (q->rear == NULL);
}

/*enQueue:进队*/
void enQueue(LiQueue *&q, ElemType e)
{
	QNode *p;
	p = (QNode*)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
	if(q->rear == NULL)
		q->front = q->rear = p;
	else
	{
		q->rear->next = p;
		q->rear = p;
	}
}

/*deQueue:出队*/
bool deQueue(LiQueue *&q, ElemType &e)
{
	QNode *t;
	if(q->rear == NULL)
		return false;
	t = q->front;
	if(q->front == q->rear)
		q->front = q->rear = NULL;
	else
		q->front = q->front->next;
	e = t->data;
	free(t);
	return true;
}

/*enTest:测试入队列操作*/
void enTest(LiQueue *&q,ElemType e)
{
	QNode *p;
	enQueue(q,e);
    p = q->rear;
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