#include <stdio.h>
#include <stdlib.h>

/******************/
/*链栈数据类型尝试*/
/******************/

typedef int ElemType;
typedef struct linknode
{
	ElemType data;
	struct linknode *next;
}LiStack;

/*InitStack:初始化栈*/
void InitStack(LiStack *&s)
{
	s = (LiStack*)malloc(sizeof(LiStack));
	s->next = NULL;
}

/*DestroyStack:销毁栈*/
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

/*StackEmpty:判断栈是否为空*/
bool StackEmpty(LiStack *s)
{
	return (s->next == NULL);
}

/*Push:进栈*/
void Push(LiStack *&s, ElemType e)
{
	LiStack *p;
	p = (LiStack*)malloc(sizeof(LiStack));  //头插法建表
	p->data = e;
	p->next = s->next;
	s->next = p;
}

/*Pop:出栈*/
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

/*GetTop:取栈顶元素*/
bool GetTop(LiStack *s, ElemType &e)
{
	if(s->next == NULL)
		return false;
	e = s->next->data;
	return true;
}

/*CommonTest:栈通用测试*/
void CommonTest(LiStack *s, ElemType &e)
{
	(GetTop(s,e))?(printf("栈顶元素为:%d\n",e)):(printf("下溢出，无法取出栈顶元素\n"));
}

/*PopTest:测试出栈*/
void PopTest(LiStack *&s, ElemType &e)
{
	(Pop(s,e))?(printf("出栈元素为%d\n",e)):(printf("下溢出，无法出栈\n"));
}

/*PushTest:测试进栈*/
void PushTest(LiStack *&s, ElemType &e)
{
	Push(s,e);
	printf("进栈元素为%d\n",e);
}

/*测试主函数*/
int main()
{
	ElemType e;
    LiStack *s;
	
	printf("初始化栈\n");
	InitStack(s);
	
	printf("\n测试空栈：\n");
	CommonTest(s,e);
	e = 0;
	PopTest(s,e);
	PushTest(s,e);
	
	
	printf("\n测试非空栈：\n");
	CommonTest(s,e);
	e = 1;
	PushTest(s,e);
	PopTest(s,e);
	
	
	printf("\n销毁栈\n");
	DestroyStack(s);
	
	system("pause");
	return 0;
}