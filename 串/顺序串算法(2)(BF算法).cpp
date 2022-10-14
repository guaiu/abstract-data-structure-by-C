#include <stdio.h>
#include <stdlib.h>

/********/
/*BF算法*/
/********/

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

/*index:BF串匹配算法*/
int index(SqString *s, SqString *t)
{
	int i = 0, j = 0;    //i遍历s，j遍历t
	while(i < s->length && j < t->length)
	{
		if(s->data[i] == t->data[j]){j++; i++;}
		else {i = i-j+1; j = 0;}    //i回退且加1，j回退为零
	}
	if(j >= t->length)
		return (i-t->length);       //返回匹配成功的第一个字符的下标
	else
		return -1;                  //匹配失败
}

/*测试主函数*/
int main()
{
	SqString *s, *t;
	char cstr[MaxSize];
	
	InitString(s);
	InitString(t);
	for(int i = 0; i < MaxSize; i++)
		cstr[i] = '\0';
	gets(cstr);
	StrAssign(s,cstr);
	for(int i = 0; i < MaxSize; i++)
		cstr[i] = '\0';
	gets(cstr);
	StrAssign(t,cstr);
	
	printf("返回位置下标%d\n",index(s,t));
	
	DestroyStr(s);
	DestroyStr(t);
	system("pause");
	return 0;
}