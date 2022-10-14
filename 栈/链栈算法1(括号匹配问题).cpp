#include <stdio.h>
#include <stdlib.h>

/********************************************/
/*编写一个算法判断输入的表达式中括号是否配对*
 *（假设只含有左、右圆括号）                */
/********************************************/


#define MaxSize 21
typedef char ElemType;
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

/*Match:括号匹配算法*/
bool Match(char exp[], int n)
{
	int i = 0;
	ElemType e;
	bool match = true;
	LiStack *st;
	
	InitStack(st);
	while(i < n && match)
	{
		if(exp[i] == '(')
			Push(st,exp[i]);
		else if(exp[i] == ')')
	    {
		    if(GetTop(st,e) == true)
		    {
			    if(e != '(')        //**个人说明：此处略显多余，因为只有左括号才进栈
				    match = false;  //栈顶元素不为'('时表示不匹配
			    else
				    Pop(st,e);
		    }
			else
				match = false;  //无法取栈顶元素时表示不匹配
	    }
	    i++;
	}
	
	if(!StackEmpty(st))
		match = false;  //只有在表达式扫描完毕且栈空时返回true
	
	DestroyStack(st);
	return match;
}

/*测试主函数*/
int main()
{
	ElemType exp[MaxSize] = {'\0'};
	gets(exp);
	int i;
	for(i = 0; exp[i] != '\0'; i++) ;
	if(Match(exp, i))
		printf("括号匹配\n");
	else
		printf("括号不匹配\n");
	
	system("pause");
	return 0;
}