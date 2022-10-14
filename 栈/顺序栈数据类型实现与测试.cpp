#include <stdio.h>
#include <stdlib.h>

/********************/
/*顺序栈数据类型尝试*/
/********************/

#define MaxSize 10

typedef int ElemType;
typedef struct  //顺序栈类型
{
	ElemType data[MaxSize];
	int top;  //栈顶指针
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

/*StackEmpty:判断栈是否为空*/
bool StackEmpty(SqStack *s)
{
	return (s->top == -1);
}

/*Push:进栈*/
bool Push(SqStack *&s, ElemType e)
{
	if(s->top == MaxSize-1)  //栈满
	    return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/*Pop:出栈*/
bool Pop(SqStack *&s, ElemType &e)
{
	if(s->top == -1)  //栈空
		return false;
    e = s->data[s->top];
	s->top--;
	return true;
}

/*GetTop:取栈顶元素*/
bool GetTop(SqStack *s, ElemType &e)
{
	if(s->top == -1)  //栈空
	    return false;
	e = s->data[s->top];
	return true;
}


/*CommonTest:栈通用测试*/
void CommonTest(SqStack *s, ElemType &e)
{
    (StackEmpty(s))?(printf("当前栈为空\n")):(printf("栈不为空，有%d个栈元素\n",(s->top+1)));
	(GetTop(s,e))?(printf("栈顶元素为:%d\n",e)):(printf("下溢出，无法取出栈顶元素\n"));
}

/*PopTest:测试出栈*/
void PopTest(SqStack *&s, ElemType &e)
{
	(Pop(s,e))?(printf("出栈元素为%d\n",e)):(printf("下溢出，无法出栈\n"));
}

/*PushTest:测试进栈*/
void PushTest(SqStack *&s, ElemType &e)
{
	(Push(s,e))?(printf("进栈元素为%d\n",e)):(printf("上溢出，无法进栈\n"));
}

/*测试主函数*/
int main()
{
	ElemType e;
    SqStack *s;
	
	printf("初始化栈\n");
	InitStack(s);
	
	printf("\n测试空栈：\n");
	CommonTest(s,e);
	e = 0;
	PopTest(s,e);
	PushTest(s,e);
	
	
	printf("\n测试非空非满栈：\n");
	CommonTest(s,e);
	e = 1;
	PushTest(s,e);
	PopTest(s,e);
	
	printf("\n测试满栈：\n");
	for(int i = 1; i < MaxSize; i++)
	{
		e = i;
		Push(s,e);
	}
	CommonTest(s,e);
	e = MaxSize;
	PushTest(s,e);
	PopTest(s,e);
	
	printf("\n销毁栈\n");
	DestroyStack(s);
	
	system("pause");
	return 0;
}