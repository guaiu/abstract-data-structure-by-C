#include <stdio.h>
#include <stdlib.h>

/*********/
/*KMP�㷨*/
/*********/

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


/*GetNext_1:��next���鱩���㷨*/
void GetNext_1(SqString *s, int next[])
{
	next[0] = -1;   //next[0]��Ϊ-1
	next[1] = 0;    //next[1]��Ϊ1������ζ������㷨ֻ���㳤�ȴ���1�Ĵ�
	for(int i = 2; i < s->length; i++)       //���±�2��ʼ����
	{
		int max_len = i-1;                   //���Ϊi-1
		int len,j;
		for(len = max_len; len >= 1; len--)  //��������ʼ����
		{
			for(j = 0; j < len; j++)
			{
				if(s->data[j] != s->data[j+i-len])  //�κ�һλ����Ӧ��
					break;                          //����ִ����Ȳ�Ϊ��ǰlen
			}
			//�������ѭ�������˳�������ǰlen�������Ӧ��j��
			//��ô��ǰlen��next[i]�Ķ�Ӧֵ
			if(j == len)
			{
				next[i] = len;
				break;
			}
		}
		if(len < 1)   //����len==1�������������ônext[i]��ֵΪ0
		    next[i] = 0;
	}
}

/*GetNext_2:��next�����Ż��㷨*/
void GetNext_2(SqString *s, int next[])
{
	int j,k;
	j = 0; k = -1; next[0] = -1;  //��ʼ��
	while(j < s->length-1)
	{
		if(k == -1 || s->data[j] == s->data[k])
		{
			j++; k++;
			next[j] = k;
		}
		else
			k = next[k];         //��һ�����ڵݹ����
		                         //Ŀ���Ƕ�λ��ǰj�Ĵγ���Ӧ�ִ�
	}
}

/*GetNextval:��һ���Ż������nextval����*/
//����͵ݹ鷽����next�����㷨��ͬ
void GetNextval(SqString *s, int nextval[])
{
	int j,k;
	j = 0; k = -1; nextval[0] = -1;  //��ʼ��
	while(j < s->length-1)
	{
		if(k == -1 || s->data[j] == s->data[k])
		{
			j++; k++;
			if(s->data[j] == s->data[nextval[k]])  //���������ֵ��ͬ��
				nextval[j] = nextval[k];              //ƥ���л�ʱ���������ظ�
			else                                //������Ӧ��ʡ���ظ�����  
				nextval[j] = k;
		}
		else
			k = nextval[k];        //�ݹ����
	}
}

/*KMPIndex:KMP�ַ���ƥ���㷨*/
int KMPIndex(SqString *s, SqString *t)
{
	int next[MaxSize], i = 0, j = 0;
	GetNextval(t,next);    //ѡȡ�����㷨
	while(i < s->length && j < t->length)
	{
		if(j == -1 || s->data[i] == t->data[j])  //ƥ��ʧ�ܣ�j������
		{                                        //���ߵ�ǰ�ַ�ƥ��ɹ�
			i++; j++;
		}
		else
			j = next[j];      //i���䣬j����
	}
	if(j >= t->length)        //��ȫ����ƥ��
		return (i-t->length); //����λ���±�
	else
		return -1;            //ƥ��ʧ��
}

/*arrprint:��ӡ����*/
void arrprint(int arr[], int length)
{
	for(int i = 0; i < length; i++)
		printf("%d",arr[i]);
	printf("\n");
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
	
	printf("����λ���±�%d",KMPIndex(s,t));
	
	return 0;
}










