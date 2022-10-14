#include <stdio.h>
#include <stdlib.h>

/****************************************************/
/*���һ���㷨����˳��ջ�ж�һ���ַ����Ƿ��ǶԳƴ���*
 *��ν�Գƴ���ָ�������Ҷ��ʹ����������������ͬ    */
/****************************************************/

#define MaxSize 11

typedef char ElemType;
typedef struct  //˳��ջ��������
{
	ElemType data[MaxSize];
	int top;
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

/*Pop:��ջ*/
bool Pop(SqStack *&s, ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

/*Push:��ջ*/
bool Push(SqStack *&s, ElemType &e)
{
	if(s->top == MaxSize-1)
		return false;
    s->top++;
	s->data[s->top] = e;
	return true;
}

/*symmetry:�ж��ַ����Ƿ�Գ�*/
bool symmetry(ElemType str[])
{
	int i; ElemType e; SqStack *st;
	InitStack(st);
	for(i = 0; str[i] != '\0'; i++)
		Push(st,str[i]);
	for(i = 0; str[i] != '\0'; i++)
	{
		Pop(st,e);
		if(str[i] != e)
		{
			DestroyStack(st);
			return false;
		}
	}
	DestroyStack(st);
	return true;
}

/*����������*/
int main()
{
	ElemType str[MaxSize] = {'\0'};
	for(int i = 0; i < MaxSize-1; i++)
		scanf("%c",&str[i]);
	
	if(symmetry(str))
		printf("���ǶԳ��ַ���");
	else
		printf("�ⲻ�ǶԳ��ַ���");
}