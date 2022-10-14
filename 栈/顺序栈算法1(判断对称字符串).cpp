#include <stdio.h>
#include <stdlib.h>

/****************************************************/
/*设计一个算法利用顺序栈判断一个字符串是否是对称串。*
 *所谓对称串是指从左向右读和从右向左读的序列相同    */
/****************************************************/

#define MaxSize 11

typedef char ElemType;
typedef struct  //顺序栈数据类型
{
	ElemType data[MaxSize];
	int top;
}SqStack;

/*InitStack:初始化栈*/
void InitStack(SqStack *&s)
{
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
}

/*DestroyStack:销毁栈*/
void DestroyStack(SqStack *&s)
{
	free(s);
}

/*Pop:出栈*/
bool Pop(SqStack *&s, ElemType &e)
{
	if(s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

/*Push:进栈*/
bool Push(SqStack *&s, ElemType &e)
{
	if(s->top == MaxSize-1)
		return false;
    s->top++;
	s->data[s->top] = e;
	return true;
}

/*symmetry:判断字符串是否对称*/
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

/*测试主程序*/
int main()
{
	ElemType str[MaxSize] = {'\0'};
	for(int i = 0; i < MaxSize-1; i++)
		scanf("%c",&str[i]);
	
	if(symmetry(str))
		printf("这是对称字符串");
	else
		printf("这不是对称字符串");
}