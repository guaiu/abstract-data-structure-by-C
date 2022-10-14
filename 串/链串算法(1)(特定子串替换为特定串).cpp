#include <stdio.h>
#include <stdlib.h>

/*******************************/
/*�������У����һ���㷨������ *
 *���ֵ��Ӵ���ab�� ��Ϊ��xyz����   */
/*******************************/

#define MaxSize 100
typedef struct snode
{
	char data;    //���������ýڵ��СΪ1
	struct snode *next;
}LiString;

/*StrAssign:β�巨����������*/
void StrAssign(LiString *&s, char cstr[])
{
	LiString *p, *r;    //sָ���½����ݽڵ㣬rָ��β�ڵ�
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

/*InitStr:����������*/
void InitStr(LiString *&s)
{
	s = (LiString*)malloc(sizeof(LiString));
	s->next = NULL;
}

/*DispStr:�������*/
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
	while(p->next != NULL && find == 0)    //����ab�ִ�
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
}//��ֱ���������㷨

int main()
{
	LiString *s = NULL;
    char cstr[MaxSize] = {'\0'};
	gets(cstr);
	InitStr(s);
	StrAssign(s,cstr);
	
	printf("��ǰ��Ϊ:\n");
	DispStr(s);
	
	Repl(s);
	printf("�滻�Ժ�:\n");
	DispStr(s);
	
	system("pause");
	return 0;
}