#include <stdio.h>
#include <stdlib.h>

/**************************/
/*˳��������ݽṹʵ�ֳ���*/
/**************************/

#define MaxSize 20
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front,rear;
}SqQueue;

/*InitQueue:��ʼ������*/
void InitQueue(SqQueue *&q)
{
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = -1;
}

/*DestroyQueue:���ٶ���*/
void DestroyQueue(SqQueue *&q)
{
	free(q);
}

/*QueueEmpty:�ж϶����Ƿ�Ϊ�գ����򷵻�true*/
bool QueueEmpty(SqQueue *q)
{
	return (q->front == q->rear);
}

/*enQueue:������*/
bool enQueue(SqQueue *&q, ElemType e)
{
	if(q->rear == MaxSize-1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

/*deQueue:������*/
bool deQueue(SqQueue *&q, ElemType &e)
{
	if(q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

/*enTest:���Խ����в���*/
void enTest(SqQueue *&q, ElemType e)
{
	(enQueue(q,e))?(printf("��ӳɹ������Ԫ��Ϊ%d\n",e)):(printf("��������޷����\n"));
}

/*deTest:���Գ����в���*/
void deTest(SqQueue *&q, ElemType &e)
{
	(deQueue(q,e))?(printf("���ӳɹ�������Ԫ��Ϊ%d\n",e)):(printf("��������޷�����\n"));
}

/*ComomonTest:ͨ�ò���*/
void ComomonTest(SqQueue *q)
{
	(QueueEmpty(q))?(printf("����Ϊ��\n")):(printf("���в�Ϊ��\n"));
}

/*����������*/
int main()
{
	ElemType e;
	SqQueue *q;
	InitQueue(q);
	
	/*�նӲ���*/
	e = 0;
	ComomonTest(q);
	deTest(q,e);
	enTest(q,e);
	
	/*һ��Ӳ���*/
	e = 1;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	/*���Ӳ���*/
	q->rear = MaxSize-1;  //�򵥹���һ��������
	e = 999;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	
	/*���ٶ�*/
	printf("����������\n");
	DestroyQueue(q);
	
	
	system("pause");
	return 0;	
}