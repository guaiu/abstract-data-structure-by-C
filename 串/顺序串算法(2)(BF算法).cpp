#include <stdio.h>
#include <stdlib.h>

/********/
/*BF�㷨*/
/********/

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

/*index:BF��ƥ���㷨*/
int index(SqString *s, SqString *t)
{
	int i = 0, j = 0;    //i����s��j����t
	while(i < s->length && j < t->length)
	{
		if(s->data[i] == t->data[j]){j++; i++;}
		else {i = i-j+1; j = 0;}    //i�����Ҽ�1��j����Ϊ��
	}
	if(j >= t->length)
		return (i-t->length);       //����ƥ��ɹ��ĵ�һ���ַ����±�
	else
		return -1;                  //ƥ��ʧ��
}

/*����������*/
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
	
	printf("����λ���±�%d\n",index(s,t));
	
	DestroyStr(s);
	DestroyStr(t);
	system("pause");
	return 0;
}