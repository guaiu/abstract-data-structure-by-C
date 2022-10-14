#include <stdio.h>
#include <stdlib.h>

/****************************/
/*���贮����˳��ṹ�洢��  *
 *���һ���㷨�� s�г��ֵ�*
 *��һ����ظ��Ӵ����±��*
 *���ȡ�                    */
/****************************/

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

/*DispStr:���������ӡs������Ԫ��*/
void DispStr(SqString *s)
{
	int i;
	for(i = 0; i < s->length; i++)
		printf("%c",s->data[i]);
	printf("\n");
}

/*maxsubstr:��s����ظ��Ӵ���������t��*/
void maxsubstr(SqString *s, SqString *t)
{
	int maxi = 0, maxlen = 0, len, i = 0, j, k;
	while(i < s->length)        //���赱ǰ�±�iΪĳ���Ӵ��Ŀ�ʼ
	{
		j = i+1;                //����һ��λ�ÿ�ʼѰ���ظ��Ӵ�
		while(j < s->length)
		{
			if(s->data[i] == s->data[j])  //�ҵ�һ���ظ��Ӵ�
			{
				len = 1;                  //����ظ�����Ϊ1
				for(k = 1; s->data[i+k] == s->data[j+k]; k++)
					len++;
				if(len > maxlen)          //���ϴ��ظ����ȸ���maxi��maxlen
				{
					maxi = i;
					maxlen = len;
				}
				j += len;
			}
			else j++;
		}
		i++;                    //����ɨ��i�ַ�֮����ַ�
	}
	t->length = maxlen;
	for(i = 0; i < maxlen; i++)
		t->data[i] = s->data[maxi+i];
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
	
	maxsubstr(s,t);
	printf("����ظ��Ӵ�Ϊ��");
	DispStr(t);
	
	return 0;
}