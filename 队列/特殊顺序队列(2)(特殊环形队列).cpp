#include <stdio.h>
#include <stdlib.h>

/****************************/
/*特殊环形队列结构类型设计：*
 *对于环形队列来说，如果知道*
 *队头指针和队列中元素个数，*
 *则可以计算出队尾指针。也就*
 *是说，可以用队列中元素个数*
 *代替队尾指针。            */
/****************************/

/*                   算法描述                                  */
/*
  已知front、rear，求队中元素个数count：
  count=(rear-front+MaxSize)%MaxSize
  已知front、count，求rear：
  rear=(front+count)%MaxSize
  已知rear、count，求front：
  front=(rear-count+MaxSize)%MaxSize   

  若仅保留队头指针，有：
  队空条件：count＝0 
  队满条件：count＝MaxSize 
  进队e操作：rear=(rear+1)%MaxSize; 将e放在rear处; count++;
  出队操作：front=(front+1)%MaxSize;  取出front处元素e; count--;*/
/*                                                              */

#define MaxSize 20
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front;          //仅保留队头指针
	int count;
}QuType;

/*InitQueue:初始化队列*/
void InitQueue(QuType *&qu)
{
	qu = (QuType*)malloc(sizeof(QuType));
	qu->front = 0;
	qu->count = 0;
}

/*EnQueue:进队*/
bool EnQueue(QuType *&qu, ElemType x)
{
	int rear;
	if(qu->count == MaxSize)
		return false;
	else
	{
		rear = (qu->front+qu->count)%MaxSize;
		rear = (rear+1)%MaxSize;
		qu->data[rear] = x;
		qu->count++;
		return true;
	}
}
/*DeQueue:出队*/
bool DeQueue(QuType *&qu, ElemType &x)
{
	if(qu->count == 0)
		return false;
	else
	{
		qu->front = (qu->front+1)%MaxSize;
		x = qu->data[qu->front];
		qu->count--;
		return true;
	}
}

/*DestroyQueue*/
void DestroyQueue(QuType *&qu)
{
	free(qu);
}

/*QueueEmpty:判断队列是否为空，是则返回true*/
bool QueueEmpty(QuType *qu)
{
	return (qu->count == 0);
}

/*EnTest:测试进队列操作*/
void EnTest(QuType *&q, ElemType e)
{
	(EnQueue(q,e))?(printf("入队成功，入队元素为%d\n",e)):(printf("上溢出，无法入队\n"));
}

/*DeTest:测试出队列操作*/
void DeTest(QuType *&q, ElemType &e)
{
	(DeQueue(q,e))?(printf("出队成功，出队元素为%d\n",e)):(printf("下溢出，无法出队\n"));
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
	QuType *qu;
	InitQueue(qu);
	
	/*空队测试*/
	e = 0;
	ComomonTest(qu);
	DeTest(qu,e);
	EnTest(qu,e);
	
	/*一般队测试*/
	e = 1;
	ComomonTest(qu);
	EnTest(qu,e);
	DeTest(qu,e);
	
	/*满队测试*/
	qu->count = MaxSize; 
	qu->data[(qu->front+1)%MaxSize] = 999;    //简单构造一个满队列
	e = 1000;
	ComomonTest(qu);
	EnTest(qu,e);
	DeTest(qu,e);
	
	
	/*销毁队*/
	printf("队列已销毁\n");
	DestroyQueue(qu);
	
	system("pause");
	return 0;	
}