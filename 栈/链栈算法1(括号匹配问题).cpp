#include <stdio.h>
#include <stdlib.h>

/********************************************/
/*��дһ���㷨�ж�����ı��ʽ�������Ƿ����*
 *������ֻ��������Բ���ţ�                */
/********************************************/


#define MaxSize 21
typedef char ElemType;
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

/*Match:����ƥ���㷨*/
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
			    if(e != '(')        //**����˵�����˴����Զ��࣬��Ϊֻ�������ŲŽ�ջ
				    match = false;  //ջ��Ԫ�ز�Ϊ'('ʱ��ʾ��ƥ��
			    else
				    Pop(st,e);
		    }
			else
				match = false;  //�޷�ȡջ��Ԫ��ʱ��ʾ��ƥ��
	    }
	    i++;
	}
	
	if(!StackEmpty(st))
		match = false;  //ֻ���ڱ��ʽɨ�������ջ��ʱ����true
	
	DestroyStack(st);
	return match;
}

/*����������*/
int main()
{
	ElemType exp[MaxSize] = {'\0'};
	gets(exp);
	int i;
	for(i = 0; exp[i] != '\0'; i++) ;
	if(Match(exp, i))
		printf("����ƥ��\n");
	else
		printf("���Ų�ƥ��\n");
	
	system("pause");
	return 0;
}