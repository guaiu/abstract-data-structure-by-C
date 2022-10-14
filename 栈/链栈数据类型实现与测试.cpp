#include <stdio.h>
#include <stdlib.h>

/******************/
/*��ջ�������ͳ���*/
/******************/

typedef int ElemType;
typedef struct linknode
{
	ElemType data;
	struct linknode *next;
}LiStack;

/*InitStack:��ʼ��ջ*/
void InitStack(LiStack *&s)
{
	s = (LiStack*)malloc(sizeof(LiStack));
	s->next = NULL;
}

/*DestroyStack:����ջ*/
void DestroyStack(LiStack *&s)
{
	LiStack *p = s, *q = s->next;
	while(q != NULL)
	{
		free(p);
		p = q;
		q = p->next;
	}
	free(p);
}

/*StackEmpty:�ж�ջ�Ƿ�Ϊ��*/
bool StackEmpty(LiStack *s)
{
	return (s->next == NULL);
}

/*Push:��ջ*/
void Push(LiStack *&s, ElemType e)
{
	LiStack *p;
	p = (LiStack*)malloc(sizeof(LiStack));  //ͷ�巨����
	p->data = e;
	p->next = s->next;
	s->next = p;
}

/*Pop:��ջ*/
bool Pop(LiStack *&s, ElemType &e)
{
	LiStack *p;
	if(s->next == NULL)
		return false;
	p = s->next;
	e = p->data;
	s->next = p->next;
	free(p);
	return true;
}

/*GetTop:ȡջ��Ԫ��*/
bool GetTop(LiStack *s, ElemType &e)
{
	if(s->next == NULL)
		return false;
	e = s->next->data;
	return true;
}

/*CommonTest:ջͨ�ò���*/
void CommonTest(LiStack *s, ElemType &e)
{
	(GetTop(s,e))?(printf("ջ��Ԫ��Ϊ:%d\n",e)):(printf("��������޷�ȡ��ջ��Ԫ��\n"));
}

/*PopTest:���Գ�ջ*/
void PopTest(LiStack *&s, ElemType &e)
{
	(Pop(s,e))?(printf("��ջԪ��Ϊ%d\n",e)):(printf("��������޷���ջ\n"));
}

/*PushTest:���Խ�ջ*/
void PushTest(LiStack *&s, ElemType &e)
{
	Push(s,e);
	printf("��ջԪ��Ϊ%d\n",e);
}

/*����������*/
int main()
{
	ElemType e;
    LiStack *s;
	
	printf("��ʼ��ջ\n");
	InitStack(s);
	
	printf("\n���Կ�ջ��\n");
	CommonTest(s,e);
	e = 0;
	PopTest(s,e);
	PushTest(s,e);
	
	
	printf("\n���Էǿ�ջ��\n");
	CommonTest(s,e);
	e = 1;
	PushTest(s,e);
	PopTest(s,e);
	
	
	printf("\n����ջ\n");
	DestroyStack(s);
	
	system("pause");
	return 0;
}