#include <stdio.h>
#include <stdlib.h>

/************************/
/*顺序串数据结构实现尝试*/
/************************/

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

/*StrCopy:串复制,将s2的值赋给s1*/
void StrCopy(SqString *&s1,SqString *s2)
{
	int i;
	for(i = 0; i <= s2->length; i++)
		s1->data[i] = s2->data[i];
	s1->length = s2->length;
}

/*StrEqual:判串相等，是则返回真*/
bool StrEqual(SqString *s1, SqString *s2)
{
	int i;
	if(s1->length != s2->length)
		return false;
	for(i = 0; i < s1->length; i++)
		if(s1->data[i] != s2->data[i])
			return false;
	return true;
}

/*StrLength:返回串s的长度*/
int StrLength(SqString *s)
{
	return s->length;
}

/*Concat:串连接操作，返回由串s1和s2连接而成的新串，并将新串储存在s1中*/
bool Concat(SqString *&s1, SqString *s2)
{
	int i;
	if(s1->length + s2->length > MaxSize-1)
		return false;
	for(i = 0; i < s2->length; i++)
		s1->data[s1->length+i] = s2->data[i];
	s1->length += s2->length;
	s1->data[s1->length] = '\0';
	return true;
}

/*SubStr:求字串，返回串s1中从第i个符开始的，由连续j个字符组成的字串并储存在串s2中*/
bool SubStr(SqString *s1, SqString *&s2, int i, int j)
{
	int k;
	if(i < 1 || i > s1->length || j < 0 || i+j-1 > s1->length)  //这里考虑空串是所有的串的一个字串
		return false;
	for(k = 0; k < j; k++)
		s2->data[k] = s1->data[i-1+k];
	s2->length = j;
	s2->data[s2->length] = '\0';
	return true;
}

/*InsStr:在字符串s1的第i个字符之前插入字符串s2*/
bool InsStr(SqString *&s1, SqString *s2, int i)
{
	int k,j;
	if(s1->length + s2->length > MaxSize-1 || i < 1 || i > s1->length)
		return false;
	for(k = s1->length-1; k >= i-1; k--)
		s1->data[k+s2->length] = s1->data[k];
	s1->length += s2->length;
	s1->data[s1->length] = '\0';
	//后移
	
	for(j = 0; j < s2->length; j++)
		s1->data[i-1+j] = s2->data[j];
	
	return true;
}

/*DelStr:删除操作，在字符串s中，删除从第i个字符开始的连续j个字符*/
bool DelStr(SqString *&s, int i, int j)
{
	int k;
	if(i < 1 || i > s->length || j < 0 || i-1+j > s->length)
		return false;
	for(k = i+j-1; k < s->length; k++)
		s->data[k-j] = s->data[k];
	s->length -= j;
	s->data[s->length] = '\0';
	//前移
	return true;
}

/*RepStr:串替换操作（把字符串s1的第i个字符开始的j个连续字符用字符串s2替换）*/
bool RepStr(SqString *&s1, SqString *s2, int i, int j)
{
	int k,m,n;
	if((s1->length+s2->length-j > MaxSize-1) || i < 1 || i > s1->length || j < 0 || i-1+j > s1->length)
		return false;
	if(j < s2->length){//替换字符长度大于原字符串长度
	                   //位置需要后移n个单位
	    n = s2->length - j;
		for(k = s1->length-1; k >= i-1; k--)
			s1->data[k+n] = s1->data[k];
		s1->length += n;
		s1->data[s1->length] = '\n';
		
	    for(m = 0; m < s2->length; m++)
		    s1->data[i-1+m] = s2->data[m];
	}
	else{//替换字符长度小于原字符串长度
	     //位置需要前移n个单位
	    n = j - s2->length;
		for(k = i-1+j; k < s1->length; k++)
			s1->data[k-n] = s1->data[k];
		s1->length -= n;
		s1->data[s1->length] = '\0';
		
		for(m = 0; m < s2->length; m++)
			s1->data[i-1+m] = s2->data[m];
	}
    return true;	
}

/*DispStr:串输出。打印s中所有元素*/
void DispStr(SqString *s)
{
	int i;
	for(i = 0; i < s->length; i++)
		printf("%c",s->data[i]);
	printf("\n");
}

/*MakeEmpty:将字符串s置空*/
void MakeEmpty(SqString *&s)
{
	s->data[0] = '\0';
	s->length = 0;
}

/*DestroyStr:销毁串*/
void DestroyStr(SqString *&s)
{
	free(s);
}

/*提示函数*/
void Hint()
{
	printf("输入指令并执行：\n");
	printf("输入 1：StrAssign:将字符串常量cstr赋给串s1，即生成值等于cstr的串s1\n");
	printf("输入 2：StrAssign:将字符串常量cstr赋给串s2，即生成值等于cstr的串s2\n");
	printf("输入 3：StrLength:返回串s1的长度\n");
	printf("输入 4：StrLength:返回串s2的长度\n");
	printf("输入 5：MakeEmpty:将字符串s1置空\n");
	printf("输入 6：MakeEmpty:将字符串s2置空\n");
	printf("输入 7：StrCopy:串复制,将s2的值赋给s1\n");
	printf("输入 8：StrEqual:判串s1,s2相等，是则返回真\n");
	printf("输入 9：Concat:串连接操作，返回由串s1和s2连接而成的新串，并将新串储存在s1中\n");
	printf("输入10：SubStr:求字串，返回串s1中从第i个符开始的，由连续j个字符组成的字串并储存在串s2中\n");
	printf("输入11：InsStr:在字符串s1的第i个字符之前插入字符串s2\n");
	printf("输入12：DelStr:删除操作，在字符串s1中，删除从第i个字符开始的连续j个字符\n");
	printf("输入13：RepStr:串替换操作（把字符串s1的第i个字符开始的j个连续字符用字符串s2替换）\n");
	printf("输入14：重新打印提示信息\n");
	printf("输入15:查看当前s1与s2状态\n");
	printf("输入16：退出测试\n");
}

/*测试主函数*/
int main()
{
	SqString *s1, *s2;
	char cstr[MaxSize];
	InitString(s1);
	InitString(s2);
	
    int command = 0;
	int i,j;
	int flag = 1;
	Hint();
	while(flag == 1)
	{
		scanf("%d",&command);
		getchar();
		switch(command)
		{
			case 1:{
				for(int k = 0; k < MaxSize; k++)
					cstr[k] = '\0';
				gets(cstr);
				StrAssign(s1,cstr);
				break;
			}
			case 2:{
				for(int k = 0; k < MaxSize; k++)
					cstr[k] = '\0';
				gets(cstr);
				StrAssign(s2,cstr);
				break;
			}
			case 3:{
				printf("s1长度为%d\n",StrLength(s1));
				break;
			}
			case 4:{
				printf("s2长度为%d\n",StrLength(s2));
				break;
			}
			case 5:{
				MakeEmpty(s1);
				break;
			}
			case 6:{
				MakeEmpty(s2);
				break;
			}
			case 7:{
				StrCopy(s1,s2);
				break;
			}
			case 8:{
				(StrEqual(s1,s2))?(printf("串相同\n")):(printf("串不同\n"));
				break;
			}
			case 9:{
				if(!Concat(s1,s2))
					printf("连接失败！\n");
				break;
			}
			case 10:{
				printf("输入字符i和j：\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!SubStr(s1,s2,i,j))
					printf("提取失败！\n");
				break;
			}
			case 11:{
				printf("输入字符i：\n");
				scanf("%d",&i);
				getchar();
				if(!InsStr(s1,s2,i))
					printf("插入失败！\n");
				break;
			}
			case 12:{
				printf("输入字符i和j：\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!DelStr(s1,i,j))
					printf("删除失败！\n");
				break;
			}
			case 13:{
				printf("输入字符i和j：\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!RepStr(s1,s2,i,j))
					printf("替换失败！\n");
				break;
			}
			case 14:{
				Hint();
				break;
			}
			case 15:{
				printf("s1:");
				DispStr(s1);
				printf("s2:");
				DispStr(s2);
				break;
			}
			case 16:{
				flag = 0;
				DestroyStr(s1);
				DestroyStr(s2);
				break;
			}
			
			default:printf("无法识别，请重新输入指令\n");
		}
		printf("执行完毕,输入14重新查看指令提示信息\n");
	}
	
	system("pause");
	return 0;
}