#include <stdio.h>
#include <stdlib.h>

/*************************************/
/*�ö�������Թ����⣨���·����     *
 *����һ��M��N���Թ�ͼ���������ڡ�  *
 *���߹�����һ����ָ����ڵ����ڵ� *
 *·��������·�����������·����     */
/*************************************/

/*       �Թ�����       */
/*int mg[10][10]= { 
 {1, 1,1,1,1,1,1,1,1, 1},
 
 {1, 0,0,1,0,0,0,1,0, 1}, 
 {1, 0,0,1,0,0,0,1,0, 1}, 
 {1, 0,0,0,0,1,1,0,0, 1}, 
 {1, 0,1,1,1,0,0,0,0, 1}, 
 {1, 0,0,0,1,0,0,0,0, 1}, 
 {1, 0,1,0,0,0,1,0,0, 1}, 
 {1, 0,1,1,1,0,1,1,0, 1}, 
 {1, 1,0,0,0,0,0,0,0, 1}, 

{1, 1,1,1,1,1,1,1,1, 1}
 };                       */
/*                        */

#define MaxSize 64
#define MaxCol 10

typedef struct
{
	int i,j;             //����λ��
	int pre;             //��·������һ�����ڶ����е��±�
}Box,ElemType;                    //��������
typedef struct
{
	Box data[MaxSize];
	int front,rear;
}SqQueue;                //˳�������

/*InitQueue:��ʼ������*/
void InitQueue(SqQueue *&q)
{
	q = (SqQueue*)malloc(sizeof(SqQueue));
	q->front = q->rear = -1;
}

/*enQueue:����*/
bool enQueue(SqQueue *&q, ElemType e)
{
	if(q->rear == MaxSize-1)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

/*deQueue:����*/
bool deQueue(SqQueue *&q, ElemType &e)
{
	if(q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

/*PathPrint:��ӡ�Թ�·��*/
void PathPrint(SqQueue *q, ElemType TheEnd)
//��Ϊ��Ҫ���յ���ݵ���㣬���Խ���һ��ջ����Ϊ��������
{
	Box Path[MaxSize];           //ջ����
	int top = -1;
	
	Box e = TheEnd;
	while(e.pre != -1)           //��·����ջ
	{
		top++;
		Path[top] = e;
		e = q->data[e.pre];
	}
	top++;Path[top] = e;         //�����ջ
	
	int count = 0;
	printf("�Թ�·�����£�\n");  //��ջ
	while(top != -1)
	{
		printf("\t(%d,%d)",Path[top].i, Path[top].j);
		top--; count++;
		if(count == 5){printf("\n"); count = 0;}
	}
}

/*mgpath:������·���Թ��㷨*/
bool mgpath(int xi, int yi, int xe, int ye, int (*mg)[MaxCol])
//����·��Ϊ��(xi, yi)->(xe,ye)
{
	SqQueue *q;
	InitQueue(q);                           //����˳���
	Box e; e.i = xi; e.j = yi; e.pre = -1;  
	enQueue(q,e);                            //(xi,yi)����
	mg[xi][yi] = -1;                  //����Թ�ֵ��Ϊ-1��
	                                  //�����ظ�����
									  
									  
	int i, j;          //��¼��������
	int di;            //��¼���Է�λ
	int find = 0;      //���״̬
	Box e2;            //��ʱ����
	while(q->front != q->rear && !find)  //���в���ѭ��
	{
		deQueue(q,e);              //����
		i = e.i; j = e.j;          //��¼��ǰ����
		if(i == xe && j == ye)//�ҵ����ڣ����·��
		{
			find = 1;
		    PathPrint(q,e);
			return true;
		}
		for(di = 0; di < 4; di++)  //�ѵ�ǰ���ӷ���ÿ�����ڿ��߷������
		{
			switch(di)
			{
				case 0: i = e.i-1; j = e.j; break;
				case 1: i = e.i; j = e.j+1; break;
				case 2: i = e.i+1; j = e.j; break;
				case 3: i = e.i; j = e.j-1; break;
			}
			if(mg[i][j] == 0)
			{
				e2.i = i; e2.j = j; e2.pre = q->front;  //�������Ԫ��
				enQueue(q,e2);                         //���
				mg[i][j] = -1;                         //�޸��Թ�ֵ
			}
		}
	}
	return false;  //δ�ҵ��κ�·������false
}

/*����������:ֱ�Ӳ���ĳ���Թ�*/
int main()
{
	int mg[MaxCol][MaxCol]= { 
{1,1,1,1,1,1,1,1,1,1},
{1,0,0,1,0,0,0,1,0,1}, 
{1,0,0,1,0,0,0,1,0,1}, 
{1,0,0,0,0,1,1,0,0,1}, 
{1,0,1,1,1,0,0,0,0,1}, 
{1,0,0,0,1,0,0,0,0,1}, 
{1,0,1,0,0,0,1,0,0,1}, 
{1,0,1,1,1,0,1,1,0,1}, 
{1,1,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1}
 };

    if(!mgpath(1,1,8,8,mg))
        printf("���Թ�����û�н⣡");	
    return 0;	
}