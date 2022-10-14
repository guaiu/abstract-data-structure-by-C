#include <stdio.h>
#include <stdlib.h>

/*******************************************/
/*˳����ʵ�ִ��Ƚ�����Strcmp(s,t)���㷨��*/
/*******************************************/

#define MaxSize 100
typedef struct
{
	char data[MaxSize];
    int length;	           //ע�⣬length���ֻ��ΪMaxSize-1
}SqString;

/*InitString;��ʼ��������մ�s*/
void InitString(SqString *&s)
{
	s = (SqString*)malloc(sizeof(SqString));
	s->data[0] = '\0';
	s->length = 0;
}

/*StrAssign:���ַ�������cstr������s��������ֵ����cstr�Ĵ�s*/
void StrAssign(SqString *&s, char *cstr)
{
	int i;
	for(i = 0; cstr[i] != '\0'; i++)
		s->data[i] = cstr[i];
	s->data[i] = '\0';        //ע�⣬s->data[s->length]�����'\0'
	s->length = i;
}

/*DestroyStr:���ٴ�*/
void DestroyStr(SqString *&s)
{
	free(s);
}

/*Strcmp:�Ƚ�����S*/
int Strcmp(SqString *s1, SqString *s2)
{
	int i, comlen;
	if(s1->length < s2->length)
		comlen = s1->length;   //��s1��s2�Ĺ�ͬ����
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

/*����������*/
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
	
	printf("����%d\n",Strcmp(s1,s2));
	
	DestroyStr(s1);
	DestroyStr(s2);
	system("pause");
	return 0;
}