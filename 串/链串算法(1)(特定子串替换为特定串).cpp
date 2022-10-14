#include <stdio.h>
#include <stdlib.h>

/*******************************/
/*在链串中，设计一个算法把最先 *
 *出现的子串“ab” 改为“xyz”。   */
/*******************************/

#define MaxSize 100
typedef struct snode
{
	char data;    //本测试设置节点大小为1
	struct snode *next;
}LiString;

/*StrAssign:尾插法建立单链串*/
void StrAssign(LiString *&s, char cstr[])
{
	LiString *p, *r;    //s指向新建数据节点，r指向尾节点
	int i;
	s = (LiString*)malloc(sizeof(LiString));
	s->next = NULL;
	r = s;
	for(i = 0; cstr[i] != '\0'; i++)
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = cstr[i];
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

/*InitStr:建立空链串*/
void InitStr(LiString *&s)
{
	s = (LiString*)malloc(sizeof(LiString));
	s->next = NULL;
}

/*DispStr:输出链串*/
void DispStr(LiString *s)
{
	LiString *p = s->next;
	while(p != NULL)
	{
		printf("%c",p->data);
		p = p->next;
	}
	printf("\n");
}

void Repl(LiString *&s)
{
	LiString *p = s->next, *q;
	int find = 0;
	while(p->next != NULL && find == 0)    //查找ab字串
	{
		if(p->data == 'a' && p->next->data == 'b')
		{
			p->data = 'x'; p->next->data = 'z';
			q = (LiString*)malloc(sizeof(LiString));
			q->data = 'y';
			q->next = p->next; p->next = q;
			find = 1;
		}
		else
			p = p->next;
	}
}//简直就是最优算法

int main()
{
	LiString *s = NULL;
    char cstr[MaxSize] = {'\0'};
	gets(cstr);
	InitStr(s);
	StrAssign(s,cstr);
	
	printf("当前串为:\n");
	DispStr(s);
	
	Repl(s);
	printf("替换以后:\n");
	DispStr(s);
	
	system("pause");
	return 0;
}