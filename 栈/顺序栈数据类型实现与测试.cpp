#include <stdio.h>
#include <stdlib.h>

/********************/
/*˳��ջ�������ͳ���*/
/********************/

#define MaxSize 10

typedef int ElemType;
typedef struct  //˳��ջ����
{
	ElemType data[MaxSize];
	int top;  //ջ��ָ��
}SqStack;

/*InitStack:��ʼ��ջ*/
void InitStack(SqStack *&s)
{
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
}

/*DestroyStack:����ջ*/
void DestroyStack(SqStack *&s)
{
	free(s);
}

/*StackEmpty:�ж�ջ�Ƿ�Ϊ��*/
bool StackEmpty(SqStack *s)
{
	return (s->top == -1);
}

/*Push:��ջ*/
bool Push(SqStack *&s, ElemType e)
{
	if(s->top == MaxSize-1)  //ջ��
	    return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/*Pop:��ջ*/
bool Pop(SqStack *&s, ElemType &e)
{
	if(s->top == -1)  //ջ��
		return false;
    e = s->data[s->top];
	s->top--;
	return true;
}

/*GetTop:ȡջ��Ԫ��*/
bool GetTop(SqStack *s, ElemType &e)
{
	if(s->top == -1)  //ջ��
	    return false;
	e = s->data[s->top];
	return true;
}


/*CommonTest:ջͨ�ò���*/
void CommonTest(SqStack *s, ElemType &e)
{
    (StackEmpty(s))?(printf("��ǰջΪ��\n")):(printf("ջ��Ϊ�գ���%d��ջԪ��\n",(s->top+1)));
	(GetTop(s,e))?(printf("ջ��Ԫ��Ϊ:%d\n",e)):(printf("��������޷�ȡ��ջ��Ԫ��\n"));
}

/*PopTest:���Գ�ջ*/
void PopTest(SqStack *&s, ElemType &e)
{
	(Pop(s,e))?(printf("��ջԪ��Ϊ%d\n",e)):(printf("��������޷���ջ\n"));
}

/*PushTest:���Խ�ջ*/
void PushTest(SqStack *&s, ElemType &e)
{
	(Push(s,e))?(printf("��ջԪ��Ϊ%d\n",e)):(printf("��������޷���ջ\n"));
}

/*����������*/
int main()
{
	ElemType e;
    SqStack *s;
	
	printf("��ʼ��ջ\n");
	InitStack(s);
	
	printf("\n���Կ�ջ��\n");
	CommonTest(s,e);
	e = 0;
	PopTest(s,e);
	PushTest(s,e);
	
	
	printf("\n���Էǿշ���ջ��\n");
	CommonTest(s,e);
	e = 1;
	PushTest(s,e);
	PopTest(s,e);
	
	printf("\n������ջ��\n");
	for(int i = 1; i < MaxSize; i++)
	{
		e = i;
		Push(s,e);
	}
	CommonTest(s,e);
	e = MaxSize;
	PushTest(s,e);
	PopTest(s,e);
	
	printf("\n����ջ\n");
	DestroyStack(s);
	
	system("pause");
	return 0;
}