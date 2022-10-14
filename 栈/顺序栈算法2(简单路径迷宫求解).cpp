#include <stdio.h>
#include <stdlib.h>

/************************************/
/*����һ��M��N���Թ�ͼ���������ڡ�  *
 *���߹�����һ����ָ����ڵ����ڵ� *
 *·��������·�������Ǽ�·������· *
 *�����ظ�                           */
/*************************************/

/*�Թ�����*/
/*
int mg[10][10]= { 
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
 };
 */


#define MaxSize 64 //���·����С
#define MaxCol 10  //����Թ�����(����Χǽ)

typedef struct
{
	int i;  //��ǰ��
	int j;  //��ǰ��
	int di; //��һ�������ڷ�λ�ķ�λ�ţ��趨Ϊ��0����1����2����3
}Box,ElemType;
typedef struct  //ջ��������
{
	ElemType data[MaxSize];
	int top;
}StType,SqStack;

/*InitStack:��ʼ��ջ*/
void InitStack(SqStack *&s)
{
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
}

/*Push:��ջ����*/
bool Push(SqStack *&s, ElemType e)
{
	if(s->top == MaxSize-1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/*Pop:��ջ����*/
bool Pop(SqStack *&s, ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

/*GetTop:ȡջ��Ԫ��*/
bool GetTop(SqStack *s, ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

/*mgpath:��·���Թ��㷨*/
bool mgpath(int xi, int yi, int xe, int ye, int (*mg)[MaxCol])
{
    Box e;
	e.i = xi; e.j = yi; e.di = -1;   //����һ��BoxԪ��e��ʼ��Ϊ��ʼ����
	StType *s; InitStack(s);         //����ջs����ʼ��
	Push(s,e);                       //��ʼ�����ջ
	mg[e.i][e.j] = -1;               //�����ջ�Թ�ֵ��Ϊ-1�������ظ�·��
	
	
	int find;   //��ʶ��ǰ·��״̬
	int i, j;       //��¼��������
	int di;         //��¼���Է�λ
	while(s->top != -1)   //ջ��Ϊ��ʱ
	{
		GetTop(s,e);
		i = e.i; j = e.j; di = e.di;//ȡջ��Ԫ�ؽ��м�¼
		if(i == xe && j == ye)  //�ҵ��˳��ڣ����·��
		{
			printf("�Թ�·������:\n");
		    for(int k = 0; k <= s->top; k++)
			{
				printf("\t(%d,%d)",s->data[k].i, s->data[k].j);
		        if( (k+1)%5 == 0)  //ÿ���5���������
		            printf("\n");
			}
			return true;
		}
		
		find = 0;  //ÿ��Ѱ·ǰ������
		while(di < 4 && find == 0)
		{
			di++;
			switch(di)
			{
				case 0: {
					i = s->data[s->top].i-1;
					j = s->data[s->top].j;
					break;
				}
				case 1: {
					i = s->data[s->top].i;
					j = s->data[s->top].j+1;
					break;
				}
				case 2: {
					i = s->data[s->top].i+1;
					j = s->data[s->top].j;
					break;
				}
				case 3: {
					i = s->data[s->top].i;
					j = s->data[s->top].j-1;
					break;
				}
			}
			if(mg[i][j] == 0)  //���·������,���ҵ��˿������ڷ���(i,j)
			find = 1;          //�ı��ʶ״̬
		}
		
		if(find == 1)  //��·������
		{
			s->data[s->top].di = di;     //�޸�ԭջ��Ԫ�ص�diֵ
			e.i = i; e.j = j; e.di = -1;
			Push(s,e);                   //���߷����ջ
			mg[i][j] = -1;               //�����ظ��ߵ��÷���
		}
		else           //��·������,��ջ����
		{
			mg[s->data[s->top].i][s->data[s->top].j] = 0;
			                             //�ø�λ�ñ�Ϊ����·�����߷���
			s->top--;
		}
	}
	//�����ջֱ��ջ�գ���˵��û�п���·��������false
	return false;
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

    int C, R;
	scanf("%d %d",&C, &R);
    if(!mgpath(1,1,C,R,mg))
        printf("���Թ�����û�н⣡");	
    return 0;	
}