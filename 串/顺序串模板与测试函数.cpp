#include <stdio.h>
#include <stdlib.h>

/************************/
/*˳�����ݽṹʵ�ֳ���*/
/************************/

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

/*StrCopy:������,��s2��ֵ����s1*/
void StrCopy(SqString *&s1,SqString *s2)
{
	int i;
	for(i = 0; i <= s2->length; i++)
		s1->data[i] = s2->data[i];
	s1->length = s2->length;
}

/*StrEqual:�д���ȣ����򷵻���*/
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

/*StrLength:���ش�s�ĳ���*/
int StrLength(SqString *s)
{
	return s->length;
}

/*Concat:�����Ӳ����������ɴ�s1��s2���Ӷ��ɵ��´��������´�������s1��*/
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

/*SubStr:���ִ������ش�s1�дӵ�i������ʼ�ģ�������j���ַ���ɵ��ִ��������ڴ�s2��*/
bool SubStr(SqString *s1, SqString *&s2, int i, int j)
{
	int k;
	if(i < 1 || i > s1->length || j < 0 || i+j-1 > s1->length)  //���￼�ǿմ������еĴ���һ���ִ�
		return false;
	for(k = 0; k < j; k++)
		s2->data[k] = s1->data[i-1+k];
	s2->length = j;
	s2->data[s2->length] = '\0';
	return true;
}

/*InsStr:���ַ���s1�ĵ�i���ַ�֮ǰ�����ַ���s2*/
bool InsStr(SqString *&s1, SqString *s2, int i)
{
	int k,j;
	if(s1->length + s2->length > MaxSize-1 || i < 1 || i > s1->length)
		return false;
	for(k = s1->length-1; k >= i-1; k--)
		s1->data[k+s2->length] = s1->data[k];
	s1->length += s2->length;
	s1->data[s1->length] = '\0';
	//����
	
	for(j = 0; j < s2->length; j++)
		s1->data[i-1+j] = s2->data[j];
	
	return true;
}

/*DelStr:ɾ�����������ַ���s�У�ɾ���ӵ�i���ַ���ʼ������j���ַ�*/
bool DelStr(SqString *&s, int i, int j)
{
	int k;
	if(i < 1 || i > s->length || j < 0 || i-1+j > s->length)
		return false;
	for(k = i+j-1; k < s->length; k++)
		s->data[k-j] = s->data[k];
	s->length -= j;
	s->data[s->length] = '\0';
	//ǰ��
	return true;
}

/*RepStr:���滻���������ַ���s1�ĵ�i���ַ���ʼ��j�������ַ����ַ���s2�滻��*/
bool RepStr(SqString *&s1, SqString *s2, int i, int j)
{
	int k,m,n;
	if((s1->length+s2->length-j > MaxSize-1) || i < 1 || i > s1->length || j < 0 || i-1+j > s1->length)
		return false;
	if(j < s2->length){//�滻�ַ����ȴ���ԭ�ַ�������
	                   //λ����Ҫ����n����λ
	    n = s2->length - j;
		for(k = s1->length-1; k >= i-1; k--)
			s1->data[k+n] = s1->data[k];
		s1->length += n;
		s1->data[s1->length] = '\n';
		
	    for(m = 0; m < s2->length; m++)
		    s1->data[i-1+m] = s2->data[m];
	}
	else{//�滻�ַ�����С��ԭ�ַ�������
	     //λ����Ҫǰ��n����λ
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

/*DispStr:���������ӡs������Ԫ��*/
void DispStr(SqString *s)
{
	int i;
	for(i = 0; i < s->length; i++)
		printf("%c",s->data[i]);
	printf("\n");
}

/*MakeEmpty:���ַ���s�ÿ�*/
void MakeEmpty(SqString *&s)
{
	s->data[0] = '\0';
	s->length = 0;
}

/*DestroyStr:���ٴ�*/
void DestroyStr(SqString *&s)
{
	free(s);
}

/*��ʾ����*/
void Hint()
{
	printf("����ָ�ִ�У�\n");
	printf("���� 1��StrAssign:���ַ�������cstr������s1��������ֵ����cstr�Ĵ�s1\n");
	printf("���� 2��StrAssign:���ַ�������cstr������s2��������ֵ����cstr�Ĵ�s2\n");
	printf("���� 3��StrLength:���ش�s1�ĳ���\n");
	printf("���� 4��StrLength:���ش�s2�ĳ���\n");
	printf("���� 5��MakeEmpty:���ַ���s1�ÿ�\n");
	printf("���� 6��MakeEmpty:���ַ���s2�ÿ�\n");
	printf("���� 7��StrCopy:������,��s2��ֵ����s1\n");
	printf("���� 8��StrEqual:�д�s1,s2��ȣ����򷵻���\n");
	printf("���� 9��Concat:�����Ӳ����������ɴ�s1��s2���Ӷ��ɵ��´��������´�������s1��\n");
	printf("����10��SubStr:���ִ������ش�s1�дӵ�i������ʼ�ģ�������j���ַ���ɵ��ִ��������ڴ�s2��\n");
	printf("����11��InsStr:���ַ���s1�ĵ�i���ַ�֮ǰ�����ַ���s2\n");
	printf("����12��DelStr:ɾ�����������ַ���s1�У�ɾ���ӵ�i���ַ���ʼ������j���ַ�\n");
	printf("����13��RepStr:���滻���������ַ���s1�ĵ�i���ַ���ʼ��j�������ַ����ַ���s2�滻��\n");
	printf("����14�����´�ӡ��ʾ��Ϣ\n");
	printf("����15:�鿴��ǰs1��s2״̬\n");
	printf("����16���˳�����\n");
}

/*����������*/
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
				printf("s1����Ϊ%d\n",StrLength(s1));
				break;
			}
			case 4:{
				printf("s2����Ϊ%d\n",StrLength(s2));
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
				(StrEqual(s1,s2))?(printf("����ͬ\n")):(printf("����ͬ\n"));
				break;
			}
			case 9:{
				if(!Concat(s1,s2))
					printf("����ʧ�ܣ�\n");
				break;
			}
			case 10:{
				printf("�����ַ�i��j��\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!SubStr(s1,s2,i,j))
					printf("��ȡʧ�ܣ�\n");
				break;
			}
			case 11:{
				printf("�����ַ�i��\n");
				scanf("%d",&i);
				getchar();
				if(!InsStr(s1,s2,i))
					printf("����ʧ�ܣ�\n");
				break;
			}
			case 12:{
				printf("�����ַ�i��j��\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!DelStr(s1,i,j))
					printf("ɾ��ʧ�ܣ�\n");
				break;
			}
			case 13:{
				printf("�����ַ�i��j��\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!RepStr(s1,s2,i,j))
					printf("�滻ʧ�ܣ�\n");
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
			
			default:printf("�޷�ʶ������������ָ��\n");
		}
		printf("ִ�����,����14���²鿴ָ����ʾ��Ϣ\n");
	}
	
	system("pause");
	return 0;
}