#include <stdio.h>
#include <stdlib.h>

/**************************/
/*环形队列数据结构尝试*/
/**************************/

/*           注意事项：环形队列四要素                 */
/*队空条件：front = rear
 *队满条件：(rear+1)%MaxSize = front
 *进队e操作：rear=(rear+1)%MaxSize; 将e放在rear处
 *出队e操作：front=(front+1)%MaxSize; 取出front处元素e;*/
/*                                                     */
 
#define MaxSize 20
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front,rear;
}QuType;

/*InitQueue:初始化队列*/
void InitQueue(QuType *&q)
{
	q = (QuType*)malloc(sizeof(QuType));
	q->front = q->rear = -1;
}

/*DestroyQueue:销毁队列*/
void DestroyQueue(QuType *&q)
{
	free(q);
}

/*QueueEmpty:判断队列是否为空，空则返回true*/
bool QueueEmpty(QuType *q)
{
	return (q->front == q->rear);
}

/*enQueue:进队列*/
bool enQueue(QuType *&q, ElemType e)
{
	if((q->rear+1)%MaxSize == q->front)
		return false;
	q->rear = (q->rear+1)%MaxSize;
	q->data[q->rear] = e;
	return true;
}

/*deQueue:出队列*/
bool deQueue(QuType *&q, ElemType &e)
{
	if(q->front == q->rear)
		return false;
	q->front = (q->front+1)%MaxSize;
	e = q->data[q->front];
	return true;
}

/*enTest:测试进队列操作*/
void enTest(QuType *&q, ElemType e)
{
	(enQueue(q,e))?(printf("入队成功，入队元素为%d\n",e)):(printf("上溢出，无法入队\n"));
}

/*deTest:测试出队列操作*/
void deTest(QuType *&q, ElemType &e)
{
	(deQueue(q,e))?(printf("出队成功，出队元素为%d\n",e)):(printf("下溢出，无法出队\n"));
}

/*ComomonTest:通用测试*/
void ComomonTest(QuType *q)
{
	(QueueEmpty(q))?(printf("队列为空\n")):(printf("队列不为空\n"));
}

/*测试主程序*/
int main()
{
	ElemType e;
	QuType *q;
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
	q->front = (q->rear+1)%MaxSize; 
	q->data[(q->front+1)%MaxSize] = 999;    //简单构造一个满队列
	e = 1000;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	
	/*销毁队*/
	printf("队列已销毁\n");
	DestroyQueue(q);
	
	
	system("pause");
	return 0;	
}