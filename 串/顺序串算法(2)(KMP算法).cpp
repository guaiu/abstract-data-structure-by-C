#include <stdio.h>
#include <stdlib.h>

/*********/
/*KMP算法*/
/*********/

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


/*GetNext_1:求next数组暴力算法*/
void GetNext_1(SqString *s, int next[])
{
	next[0] = -1;   //next[0]必为-1
	next[1] = 0;    //next[1]必为1。这意味着这个算法只能算长度大于1的串
	for(int i = 2; i < s->length; i++)       //从下标2开始计算
	{
		int max_len = i-1;                   //最长设为i-1
		int len,j;
		for(len = max_len; len >= 1; len--)  //从最长情况开始搜索
		{
			for(j = 0; j < len; j++)
			{
				if(s->data[j] != s->data[j+i-len])  //任何一位不对应，
					break;                          //则最长字串长度不为当前len
			}
			//如果上述循环正常退出，即当前len等于最长对应数j，
			//那么当前len是next[i]的对应值
			if(j == len)
			{
				next[i] = len;
				break;
			}
		}
		if(len < 1)   //尝试len==1情况不成立，那么next[i]的值为0
		    next[i] = 0;
	}
}

/*GetNext_2:求next数组优化算法*/
void GetNext_2(SqString *s, int next[])
{
	int j,k;
	j = 0; k = -1; next[0] = -1;  //初始化
	while(j < s->length-1)
	{
		if(k == -1 || s->data[j] == s->data[k])
		{
			j++; k++;
			next[j] = k;
		}
		else
			k = next[k];         //这一步属于递归回退
		                         //目的是定位当前j的次长对应字串
	}
}

/*GetNextval:进一步优化，求的nextval数组*/
//大体和递归方法求next数组算法相同
void GetNextval(SqString *s, int nextval[])
{
	int j,k;
	j = 0; k = -1; nextval[0] = -1;  //初始化
	while(j < s->length-1)
	{
		if(k == -1 || s->data[j] == s->data[k])
		{
			j++; k++;
			if(s->data[j] == s->data[nextval[k]])  //如果这两个值相同，
				nextval[j] = nextval[k];              //匹配切换时等于做了重复
			else                                //工作，应该省略重复过程  
				nextval[j] = k;
		}
		else
			k = nextval[k];        //递归回退
	}
}

/*KMPIndex:KMP字符串匹配算法*/
int KMPIndex(SqString *s, SqString *t)
{
	int next[MaxSize], i = 0, j = 0;
	GetNextval(t,next);    //选取最优算法
	while(i < s->length && j < t->length)
	{
		if(j == -1 || s->data[i] == t->data[j])  //匹配失败，j已重置
		{                                        //或者当前字符匹配成功
			i++; j++;
		}
		else
			j = next[j];      //i不变，j回退
	}
	if(j >= t->length)        //完全长度匹配
		return (i-t->length); //返回位置下标
	else
		return -1;            //匹配失败
}

/*arrprint:打印数组*/
void arrprint(int arr[], int length)
{
	for(int i = 0; i < length; i++)
		printf("%d",arr[i]);
	printf("\n");
}

/*测试主程序*/
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
	
	int next_1[MaxSize];
	int next_2[MaxSize];
	int nextval[MaxSize];
	GetNext_1(t,next_1);
	GetNext_2(t,next_2);
	GetNextval(t,nextval);
	printf("next_1:");
	arrprint(next_1,t->length);
	printf("next_2:");
	arrprint(next_2,t->length);
	printf("nextval:");
	arrprint(nextval,t->length);
	
	printf("返回位置下标%d",KMPIndex(s,t));
	
	return 0;
}










