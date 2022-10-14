#include <stdio.h>
#include <stdlib.h>

/****************************/
/*假设串采用顺序结构存储。  *
 *设计一个算法求串 s中出现的*
 *第一个最长重复子串的下标和*
 *长度。                    */
/****************************/

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

/*DispStr:串输出。打印s中所有元素*/
void DispStr(SqString *s)
{
	int i;
	for(i = 0; i < s->length; i++)
		printf("%c",s->data[i]);
	printf("\n");
}

/*maxsubstr:求s中最长重复子串并储存在t中*/
void maxsubstr(SqString *s, SqString *t)
{
	int maxi = 0, maxlen = 0, len, i = 0, j, k;
	while(i < s->length)        //假设当前下标i为某个子串的开始
	{
		j = i+1;                //从下一个位置开始寻找重复子串
		while(j < s->length)
		{
			if(s->data[i] == s->data[j])  //找到一个重复子串
			{
				len = 1;                  //最短重复长度为1
				for(k = 1; s->data[i+k] == s->data[j+k]; k++)
					len++;
				if(len > maxlen)          //将较大重复长度赋给maxi与maxlen
				{
					maxi = i;
					maxlen = len;
				}
				j += len;
			}
			else j++;
		}
		i++;                    //继续扫描i字符之后的字符
	}
	t->length = maxlen;
	for(i = 0; i < maxlen; i++)
		t->data[i] = s->data[maxi+i];
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
	
	maxsubstr(s,t);
	printf("最大重复子串为；");
	DispStr(t);
	
	return 0;
}