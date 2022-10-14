#include <stdio.h>
#include <stdlib.h>

/****************************/
/*���⻷�ζ��нṹ������ƣ�*
 *���ڻ��ζ�����˵�����֪��*
 *��ͷָ��Ͷ�����Ԫ�ظ�����*
 *����Լ������βָ�롣Ҳ��*
 *��˵�������ö�����Ԫ�ظ���*
 *�����βָ�롣            */
/****************************/

/*                   �㷨����                                  */
/*
  ��֪front��rear�������Ԫ�ظ���count��
  count=(rear-front+MaxSize)%MaxSize
  ��֪front��count����rear��
  rear=(front+count)%MaxSize
  ��֪rear��count����front��
  front=(rear-count+MaxSize)%MaxSize   

  ����������ͷָ�룬�У�
  �ӿ�������count��0 
  ����������count��MaxSize 
  ����e������rear=(rear+1)%MaxSize; ��e����rear��; count++;
  ���Ӳ�����front=(front+1)%MaxSize;  ȡ��front��Ԫ��e; count--;*/
/*                                                              */

#define MaxSize 20
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front;          //��������ͷָ��
	int count;
}QuType;

/*InitQueue:��ʼ������*/
void InitQueue(QuType *&qu)
{
	qu = (QuType*)malloc(sizeof(QuType));
	qu->front = 0;
	qu->count = 0;
}

/*EnQueue:����*/
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
/*DeQueue:����*/
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

/*QueueEmpty:�ж϶����Ƿ�Ϊ�գ����򷵻�true*/
bool QueueEmpty(QuType *qu)
{
	return (qu->count == 0);
}

/*EnTest:���Խ����в���*/
void EnTest(QuType *&q, ElemType e)
{
	(EnQueue(q,e))?(printf("��ӳɹ������Ԫ��Ϊ%d\n",e)):(printf("��������޷����\n"));
}

/*DeTest:���Գ����в���*/
void DeTest(QuType *&q, ElemType &e)
{
	(DeQueue(q,e))?(printf("���ӳɹ�������Ԫ��Ϊ%d\n",e)):(printf("��������޷�����\n"));
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
	QuType *qu;
	InitQueue(qu);
	
	/*�նӲ���*/
	e = 0;
	ComomonTest(qu);
	DeTest(qu,e);
	EnTest(qu,e);
	
	/*һ��Ӳ���*/
	e = 1;
	ComomonTest(qu);
	EnTest(qu,e);
	DeTest(qu,e);
	
	/*���Ӳ���*/
	qu->count = MaxSize; 
	qu->data[(qu->front+1)%MaxSize] = 999;    //�򵥹���һ��������
	e = 1000;
	ComomonTest(qu);
	EnTest(qu,e);
	DeTest(qu,e);
	
	
	/*���ٶ�*/
	printf("����������\n");
	DestroyQueue(qu);
	
	system("pause");
	return 0;	
}