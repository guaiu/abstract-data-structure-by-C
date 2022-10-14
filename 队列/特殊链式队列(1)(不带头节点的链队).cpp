#include <stdio.h>
#include <stdlib.h>

/****************************************************/
/*�����������ݽṹ����:                             *
 *����һ������ͷ�ڵ�ֻ��һ��β�ڵ�ָ��rear��ѭ��    *
 *������洢���У���ƶ��еĳ�ʼ�������Ӻͳ��ӵ��㷨*/
/****************************************************/

/*               �㷨����                  */
/*
  ����ͨ��β�ڵ�ָ��rearΨһ��ʶ
  rear->next��ָ���ͷ  
  ��Ҫ�أ�  
  �ӿ�������rear=NULL
  ����������������
  ����e������������e�Ľڵ���뵽�������β
  ���Ӳ�����ɾ���������׽ڵ�                
                                            */
/*                                          */

#define MaxSize 20
typedef int ElemType;
typedef struct qnode  //���ݽڵ�
{
	ElemType data;
	struct qnode *next;
}QNode,LiQueue;

/*InitQueue:���г�ʼ��*/
void InitQueue(LiQueue *&rear)
{
	rear = NULL;
}

/*QueueEmpty:�ж϶����Ƿ�Ϊ�գ����򷵻�true*/
bool QueueEmpty(LiQueue *rear)
{
	return (rear == NULL);
}

/*DestroyQueue:���ٶ���*/
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

/*enQueue:���*/
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

/*deQueue:����*/
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

/*enTest:��������в���*/
void enTest(LiQueue *&q,ElemType e)
{
	LiQueue *p;
	enQueue(q,e);
	p = q;
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


























 