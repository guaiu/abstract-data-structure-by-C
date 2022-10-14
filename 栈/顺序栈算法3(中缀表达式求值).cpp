#include <stdio.h>
#include <stdlib.h>

/***********************************************/
/*�û�����һ��������+���� ��-������*������/����������  *
 *��Բ���ŵĺϷ��������ʽ������ñ��ʽ������ *
 *�����                                       */
/***********************************************/
#define MaxNumber 5  //���������Ϊ4λ
#define MaxSize 30   //��������ʽ
typedef struct
{
	int data[MaxSize];
	int top;
}NumStack;  //int��������ջ

typedef struct
{
	char data[MaxSize];
	int top;
}CharStack;  //char��������ջ

/*int��������ջ����*/
/******************************************************/
/*InitNum:��ʼ��ջ*/
void InitNum(NumStack *&s)
{
	s = (NumStack*)malloc(sizeof(NumStack));
	s->top = -1;
}

/*NumPush:��ջ*/
bool NumPush(NumStack *&s, int e)
{
	if(s->top == MaxSize-1)  //ջ��
	    return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/*NumPop:��ջ*/
bool NumPop(NumStack *&s, int &e)
{
	if(s->top == -1)  //ջ��
		return false;
    e = s->data[s->top];
	s->top--;
	return true;
}
/******************************************************/

/*char��������ջ����*/
/******************************************************/
/*InitChar:��ʼ��ջ*/
void InitChar(CharStack *&s)
{
	s = (CharStack*)malloc(sizeof(CharStack));
	s->top = -1;
}

/*CharPush:��ջ*/
bool CharPush(CharStack *&s, char e)
{
	if(s->top == MaxSize-1)  //ջ��
	    return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/******************************************************/

/*getpriority:�õ��������ȼ�*/
bool getpriority(char a, char b)
{
	if( (a == '*' || a == '/') && (b == '+' || b == '-') )
		return true;
	else
		return false;
}

/*getpostexp:��׺���ʽת��Ϊ��׺���ʽ*/
void getpostexp(char exp[], char *postexp)
{
	int i = 0, j = 0;
	CharStack *s; InitChar(s);
	while(exp[i] != '\0')
	{
		if('0' < exp[i] && exp[i] < '9')  //���ֽ�ȥ��׺���ʽ����,��#��ʶ���ִ���β
		{
			while('0' < exp[i] && exp[i] < '9')
			    postexp[j++] = exp[i++];
			postexp[j++] = '#';
			continue;
		}
		else if(exp[i] == '(')            //�����Ž�ջ
		    CharPush(s,exp[i]);
		else if(exp[i] == ')')
		{
			while(s->data[s->top] != '(')
				postexp[j++] = s->data[s->top--];
			s->top--;   //���������׸������ź󷽵ķ��ź͸������ű����ջ
		}
		else
		{
			if(s->top == -1 || s->data[s->top] == '(')  //ջ�ջ���ջ��Ϊ������ֱ�ӽ�ջ
				CharPush(s,exp[i]);
			else if(getpriority(exp[i],s->data[s->top]))//exp[i]���ȼ���ջ��Ԫ�ظ����ջ
				CharPush(s,exp[i]);
			else
			{
				postexp[j++] = s->data[s->top--];       //���ν�ջ��Ԫ�س�ջֱ������������������֮һ
                continue;
			}
		}
		i++;
	}
	//expɨ�����
	while(s->top != -1)
		postexp[j++] = s->data[s->top--];
	//��ջ��ʣ�µ�������������postexp��
}

/*getresult:�����׺���ʽ*/
int getresult(char postexp[])
{
	int i, j = 0, k;
	NumStack *s; InitNum(s);
	int e1,e2,e3;
	char number[MaxNumber];
	for(i = 0; postexp[i] != '\0'; i++)
	{
		if('0' < postexp[i] && postexp[i] < '9')
		{
			for(k = 0; k < MaxNumber; k++)  //��ʼ��
				number[k] = '\0';
			j = 0;
			while('0' < postexp[i] && postexp[i] < '9')
				number[j++] = postexp[i++];
			e1 = atoi(number);
			NumPush(s,e1);
		}
		else if(postexp[i] == '+')
		{
			NumPop(s,e1);
			NumPop(s,e2);
			e3 = e1 + e2;
			NumPush(s,e3);
		}
		else if(postexp[i] == '-')
		{
			NumPop(s,e1);
			NumPop(s,e2);
			e3 = e2 - e1;
			NumPush(s,e3);
		}
		else if(postexp[i] == '*')
		{
			NumPop(s,e1);
			NumPop(s,e2);
			e3 = e1 * e2;
			NumPush(s,e3);
		}
		else if(postexp[i] == '/')
		{
			NumPop(s,e1);
			NumPop(s,e2);
			if(e1 != 0)
			{   
		        e3 = e2 / e1;
			    NumPush(s,e3);
			}
			else
			{
				printf("��������\n");
				return -99999;
			}
		}
		
	}
	return s->data[s->top];
}

/*����������*/
int main()
{
	int result = 0;
	char exp[MaxSize] = {'\0'};
	char postexp[MaxSize] = {'\0'};
	gets(exp);
	getpostexp(exp,postexp);
	result = getresult(postexp);
	printf("����ý��Ϊ��%d\n",result);
	
	system("pause");
	return 0;
}