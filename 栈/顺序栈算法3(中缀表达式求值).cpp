#include <stdio.h>
#include <stdlib.h>

/***********************************************/
/*用户输入一个包含“+”、 “-”、“*”、“/”、正整数  *
 *和圆括号的合法算术表达式，计算该表达式的运算 *
 *结果。                                       */
/***********************************************/
#define MaxNumber 5  //单个最长数字为4位
#define MaxSize 30   //单个最长表达式
typedef struct
{
	int data[MaxSize];
	int top;
}NumStack;  //int数据类型栈

typedef struct
{
	char data[MaxSize];
	int top;
}CharStack;  //char数据类型栈

/*int数据类型栈操作*/
/******************************************************/
/*InitNum:初始化栈*/
void InitNum(NumStack *&s)
{
	s = (NumStack*)malloc(sizeof(NumStack));
	s->top = -1;
}

/*NumPush:进栈*/
bool NumPush(NumStack *&s, int e)
{
	if(s->top == MaxSize-1)  //栈满
	    return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/*NumPop:出栈*/
bool NumPop(NumStack *&s, int &e)
{
	if(s->top == -1)  //栈空
		return false;
    e = s->data[s->top];
	s->top--;
	return true;
}
/******************************************************/

/*char数据类型栈操作*/
/******************************************************/
/*InitChar:初始化栈*/
void InitChar(CharStack *&s)
{
	s = (CharStack*)malloc(sizeof(CharStack));
	s->top = -1;
}

/*CharPush:进栈*/
bool CharPush(CharStack *&s, char e)
{
	if(s->top == MaxSize-1)  //栈满
	    return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

/******************************************************/

/*getpriority:得到运算优先级*/
bool getpriority(char a, char b)
{
	if( (a == '*' || a == '/') && (b == '+' || b == '-') )
		return true;
	else
		return false;
}

/*getpostexp:后缀表达式转化为中缀表达式*/
void getpostexp(char exp[], char *postexp)
{
	int i = 0, j = 0;
	CharStack *s; InitChar(s);
	while(exp[i] != '\0')
	{
		if('0' < exp[i] && exp[i] < '9')  //数字进去后缀表达式数组,以#标识数字串结尾
		{
			while('0' < exp[i] && exp[i] < '9')
			    postexp[j++] = exp[i++];
			postexp[j++] = '#';
			continue;
		}
		else if(exp[i] == '(')            //左括号进栈
		    CharPush(s,exp[i]);
		else if(exp[i] == ')')
		{
			while(s->data[s->top] != '(')
				postexp[j++] = s->data[s->top--];
			s->top--;   //将遇到的首个左括号后方的符号和该左括号本身出栈
		}
		else
		{
			if(s->top == -1 || s->data[s->top] == '(')  //栈空或者栈顶为左括号直接进栈
				CharPush(s,exp[i]);
			else if(getpriority(exp[i],s->data[s->top]))//exp[i]优先级比栈顶元素高则进栈
				CharPush(s,exp[i]);
			else
			{
				postexp[j++] = s->data[s->top--];       //依次将栈顶元素出栈直到满足上述两个条件之一
                continue;
			}
		}
		i++;
	}
	//exp扫描完毕
	while(s->top != -1)
		postexp[j++] = s->data[s->top--];
	//将栈中剩下的算术符号输入postexp中
}

/*getresult:计算后缀表达式*/
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
			for(k = 0; k < MaxNumber; k++)  //初始化
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
				printf("除法出错！\n");
				return -99999;
			}
		}
		
	}
	return s->data[s->top];
}

/*测试主函数*/
int main()
{
	int result = 0;
	char exp[MaxSize] = {'\0'};
	char postexp[MaxSize] = {'\0'};
	gets(exp);
	getpostexp(exp,postexp);
	result = getresult(postexp);
	printf("计算得结果为：%d\n",result);
	
	system("pause");
	return 0;
}