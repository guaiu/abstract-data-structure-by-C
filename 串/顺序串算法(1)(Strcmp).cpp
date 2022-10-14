#include <stdio.h>
#include <stdlib.h>

/*******************************************/
/*顺序串上实现串比较运算Strcmp(s,t)的算法。*/
/*******************************************/

#define MaxSize 100
typedef struct
{
	char data[MaxSize];
    int length;	           //注意，length最大只能为MaxSize-1
}SqString;

/*InitString;初始化，创造空串s*/
void InitString(SqString *&s)
{
	s = (SqString*)malloc(sizeof(SqString));
	s->data[0] = '\0';
	s->length = 0;
}

/*StrAssign:将字符串常量cstr赋给串s，即生成值等于cstr的串s*/
void StrAssign(SqString *&s, char *cstr)
{
	int i;
	for(i = 0; cstr[i] != '\0'; i++)
		s->data[i] = cstr[i];
	s->data[i] = '\0';        //注意，s->data[s->length]恒等于'\0'
	s->length = i;
}

/*DestroyStr:销毁串*/
void DestroyStr(SqString *&s)
{
	free(s);
}

/*Strcmp:比较运算S*/
int Strcmp(SqString *s1, SqString *s2)
{
	int i, comlen;
	if(s1->length < s2->length)
		comlen = s1->length;   //求s1与s2的共同长度
	else
		comlen = s2->length;
	for(i = 0; i < comlen; i++)
		if(s1->data[i] > s2->data[i])
			return 1;
		else if(s1->data[i] < s2->data[i])
			return -1;
	
	if(s1->length == s2->length)
		return 0;
	else if(s1->length > s2->length)
		return 1;
	else
		return -1;
}

/*测试主函数*/
int main()
{
	SqString *s1, *s2;
	char cstr[MaxSize];
	
	InitString(s1);
	InitString(s2);
	for(int i = 0; i < MaxSize; i++)
		cstr[i] = '\0';
	gets(cstr);
	StrAssign(s1,cstr);
	for(int i = 0; i < MaxSize; i++)
		cstr[i] = '\0';
	gets(cstr);
	StrAssign(s2,cstr);
	
	printf("返回%d\n",Strcmp(s1,s2));
	
	DestroyStr(s1);
	DestroyStr(s2);
	system("pause");
	return 0;
}