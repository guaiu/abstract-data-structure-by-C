#include <stdio.h>
#include <stdlib.h>

/**************************/
/*顺序队列数据结构实现尝试*/
/**************************/

#define MaxSize 20
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front,rear;
}SqQueue;

/*InitQueue:初始化队列*/
void InitQueue(SqQueue *&q)
{
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = -1;
}

/*DestroyQueue:销毁队列*/
void DestroyQueue(SqQueue *&q)
{
	free(q);
}

/*QueueEmpty:判断队列是否为空，空则返回true*/
bool QueueEmpty(SqQueue *q)
{
	return (q->front == q->rear);
}

/*enQueue:进队列*/
bool enQueue(SqQueue *&q, ElemType e)
{
	if(q->rear == MaxSize-1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

/*deQueue:出队列*/
bool deQueue(SqQueue *&q, ElemType &e)
{
	if(q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

/*enTest:测试进队列操作*/
void enTest(SqQueue *&q, ElemType e)
{
	(enQueue(q,e))?(printf("入队成功，入队元素为%d\n",e)):(printf("上溢出，无法入队\n"));
}

/*deTest:测试出队列操作*/
void deTest(SqQueue *&q, ElemType &e)
{
	(deQueue(q,e))?(printf("出队成功，出队元素为%d\n",e)):(printf("下溢出，无法出队\n"));
}

/*ComomonTest:通用测试*/
void ComomonTest(SqQueue *q)
{
	(QueueEmpty(q))?(printf("队列为空\n")):(printf("队列不为空\n"));
}

/*测试主程序*/
int main()
{
	ElemType e;
	SqQueue *q;
	InitQueue(q);
	
	/*空队测试*/
	e = 0;
	ComomonTest(q);
	deTest(q,e);
	enTest(q,e);
	
	/*一般队测试*/
	e = 1;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	/*满队测试*/
	q->rear = MaxSize-1;  //简单构造一个满队列
	e = 999;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	
	/*销毁队*/
	printf("队列已销毁\n");
	DestroyQueue(q);
	
	
	system("pause");
	return 0;	
}