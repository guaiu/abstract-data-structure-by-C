#include <stdio.h>
#include <stdlib.h>

/******************/
/*�������ݽṹ����*/
/******************/

/*           ���ӵ���Ҫ��            */
/*
  �ӿգ�front=rear=NULL;
  ������������
  ���e��������e�Ľڵ���뵥�����β
  ����e��ɾ�������������ݽڵ�         
                                      */
/*                                    */

#define MaxSize 20
typedef int ElemType;
typedef struct qnode  //���ݽڵ�����
{
	ElemType data;
	struct qnode *next;
}QNode;

typedef struct     //ͷ�ڵ�����
{
	QNode *front;  //��ͷ
	QNode *rear;   //��β
}LiQueue;

/*InitQueue:��ʼ������*/
void InitQueue(LiQueue *&q)
{
	q = (LiQueue*)malloc(sizeof(LiQueue));
	q->front = q->rear = NULL;
}

/*DestroyQueue;���ٶ���*/
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

/*QueueEmpty:�ж϶����Ƿ�Ϊ�գ����򷵻�true*/
bool QueueEmpty(LiQueue *q)
{
	return (q->rear == NULL);
}

/*enQueue:����*/
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

/*deQueue:����*/
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

/*enTest:��������в���*/
void enTest(LiQueue *&q,ElemType e)
{
	QNode *p;
	enQueue(q,e);
    p = q->rear;
	printf("��ӳɹ������Ԫ��Ϊ%d\n",p->data);
}

/*deTest:���Գ����в���*/
void deTest(LiQueue *&q, ElemType &e)
{
	(deQueue(q,e))?(printf("���ӳɹ�������Ԫ��Ϊ%d\n",e)):(printf("��������޷�����\n"));
}

/*ComomonTest:ͨ�ò���*/
void ComomonTest(LiQueue *q)
{
	(QueueEmpty(q))?(printf("����Ϊ��\n")):(printf("���в�Ϊ��\n"));
}

/*����������*/
int main()
{
	ElemType e;
	LiQueue *q;
	InitQueue(q);
	
	/*�նӲ���*/
	e = 0;
	ComomonTest(q);
	deTest(q,e);
	enTest(q,e);
	
	/*һ��Ӳ���(����)*/
	e = 1;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	e = 2;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	/*���ٶ�*/
	printf("����������\n");
	DestroyQueue(q);
	
	
	system("pause");
	return 0;	
}