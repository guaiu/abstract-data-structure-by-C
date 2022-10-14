#include <stdio.h>
#include <stdlib.h>

/**************************/
/*���ζ������ݽṹ����*/
/**************************/

/*           ע��������ζ�����Ҫ��                 */
/*�ӿ�������front = rear
 *����������(rear+1)%MaxSize = front
 *����e������rear=(rear+1)%MaxSize; ��e����rear��
 *����e������front=(front+1)%MaxSize; ȡ��front��Ԫ��e;*/
/*                                                     */
 
#define MaxSize 20
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front,rear;
}QuType;

/*InitQueue:��ʼ������*/
void InitQueue(QuType *&q)
{
	q = (QuType*)malloc(sizeof(QuType));
	q->front = q->rear = -1;
}

/*DestroyQueue:���ٶ���*/
void DestroyQueue(QuType *&q)
{
	free(q);
}

/*QueueEmpty:�ж϶����Ƿ�Ϊ�գ����򷵻�true*/
bool QueueEmpty(QuType *q)
{
	return (q->front == q->rear);
}

/*enQueue:������*/
bool enQueue(QuType *&q, ElemType e)
{
	if((q->rear+1)%MaxSize == q->front)
		return false;
	q->rear = (q->rear+1)%MaxSize;
	q->data[q->rear] = e;
	return true;
}

/*deQueue:������*/
bool deQueue(QuType *&q, ElemType &e)
{
	if(q->front == q->rear)
		return false;
	q->front = (q->front+1)%MaxSize;
	e = q->data[q->front];
	return true;
}

/*enTest:���Խ����в���*/
void enTest(QuType *&q, ElemType e)
{
	(enQueue(q,e))?(printf("��ӳɹ������Ԫ��Ϊ%d\n",e)):(printf("��������޷����\n"));
}

/*deTest:���Գ����в���*/
void deTest(QuType *&q, ElemType &e)
{
	(deQueue(q,e))?(printf("���ӳɹ�������Ԫ��Ϊ%d\n",e)):(printf("��������޷�����\n"));
}

/*ComomonTest:ͨ�ò���*/
void ComomonTest(QuType *q)
{
	(QueueEmpty(q))?(printf("����Ϊ��\n")):(printf("���в�Ϊ��\n"));
}

/*����������*/
int main()
{
	ElemType e;
	QuType *q;
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
	q->front = (q->rear+1)%MaxSize; 
	q->data[(q->front+1)%MaxSize] = 999;    //�򵥹���һ��������
	e = 1000;
	ComomonTest(q);
	enTest(q,e);
	deTest(q,e);
	
	
	/*���ٶ�*/
	printf("����������\n");
	DestroyQueue(q);
	
	
	system("pause");
	return 0;	
}