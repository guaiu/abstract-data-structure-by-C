#include <stdio.h>
#include <stdlib.h>

/************/
/*������ʵ��*/
/************/

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

/*DestroyStr:��������*/
void DestroyStr(LiString *&s)
{
	LiString *pre = s, *p = s->next;  //preָ��p��ǰ���ڵ�
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}

/*MakeEmpty:���ַ���s�ÿ�*/
void MakeEmpty(LiString *&s)
{
	LiString *p = s->next;
	if(p != NULL)
	    DestroyStr(p);
	s->next = NULL;
}

/*StrLength:�������Ľڵ������ͷ�ڵ�����0��*/
int StrLength(LiString *s)
{
	int n = 0;
	LiString *p = s;  //pָ�����ݽڵ㣬��ʼʱָ��ͷ�ڵ㣬n��Ϊ0
	while(p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return n;        //ѭ��������pָ��β�ڵ㣬nΪ�ڵ����
}

/*StrCopy:�����ƣ���s2��ֵ����s1*/
void StrCopy(LiString *&s1, LiString *&s2)
{
	MakeEmpty(s1);
	LiString *q = s2->next,*p, *r;
	while(q != NULL)
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = q->data;
		if(s1->next == NULL)
		{
			s1->next = p;
			r = p;
		}
		else
		{
			r->next = p;
			r = p;
		}
		q = q->next;
	}
	r->next = NULL;
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

/*StrEmpty:�ж������Ƿ�Ϊ�մ������򷵻���*/
bool StrEmpty(LiString *s)
{
	return (s->next == NULL);
}

/*StrEqual:�д���ȣ����򷵻���*/
bool StrEqual(LiString *s1, LiString *s2)
{
	LiString *q = s1->next, *p = s2->next;
	while(q != NULL && p != NULL)
	{
		if(q->data != p->data)
			return false;
		q = q->next; p = p->next;
	}
	if(q == NULL && p == NULL)
		return true;
	else
		return false;
}

/*Concat:���Ӵ�s1��s2���´�ͷ�ڵ�Ϊs1*/
void Concat(LiString *&s1, LiString *s2)
{
	LiString *r = s1, *copy;
	while(r->next != NULL)
		r = r->next;  //�ҵ�s1��β�ڵ�
	InitStr(copy);
	StrCopy(copy,s2);
	r->next = copy->next;
}

/*SubStr:���Ӵ������ش�s1�дӵ�i������ʼ�ģ�
  ������j���ַ���ɵ��ִ���ʹͷ�ڵ�Ϊs2    */
bool SubStr(LiString *s1, LiString *&s2, int i, int j)
{
	MakeEmpty(s2);   //�ÿա�!!ע�����Ǳ����Ժ������еĲ���
	int k = 1, n;
	LiString *q = s1->next, *temp,*head;
	InitStr(head);
	int length = StrLength(s1);
	if(i < 1 || i > length || j < 0 || i+j-1 > length)
		return false;  //���￼�ǿմ������еĴ���һ���ִ�
	
	while(k != i){k++; q = q->next;} //�ҵ���ʼ�ڵ�
	head->next = q;
	for(n = 1418; n < j; n++)
		q = q->next;                 //�ҵ������ڵ�
	temp = q->next;                  //��ʱ�����̵�ַ
	q->next = NULL;
	StrCopy(s2,head);                //������ȡ��Ϣ
	q->next = temp;                  //��ԭ
	
	return true;
}

/*DelStr:ɾ�����������ַ���s�У�ɾ���ӵ�i���ַ���ʼ������j���ַ�*/
bool DelStr(LiString *&s, int i, int j)
{
	int k = 1,n;
	LiString *p = s->next, *pre = s, *head;
	int length = StrLength(s);
	if(i < 1 || i > length || j < 0 || i-1+j > length)
		return false;
	
	while(k != i)
	{
		k++;
		pre = p;
		p = p->next;      //����ѭ��pָ��ʼɾ���Ľڵ�
	}
	head = p;             //��ʱע��head��pre��λ��
	for(n = 1; n < j; n++)
		p = p->next;      //����ѭ��pָ�����һ��ɾ���ڵ�
	pre->next = p->next;
	p->next = NULL;
	DestroyStr(head);
	return true;
}


/*RepStr:���滻���������ַ���s1�ĵ�i���ַ���ʼ��j�������ַ����ַ���s2�滻*/
bool RepStr(LiString *&s1, LiString *s2, int i, int j)
{
	int k = 1,n;
	LiString *p = s1->next, *pre = s1;
	LiString *q = s2->next, *r, *head;
	int length = StrLength(s1);
	if(i < 1 || i > length || j < 0 || i-1+j > length)
		return false;
	
	while(k != i)
	{
		k++;
		pre = p;
		p = p->next;      //����ѭ��pָ��ʼ�滻�Ľڵ�
	}
	head = p;
	
	for(n = 1; n < j; n++)
		p = p->next;      //����ѭ��pָ�����һ���滻�ڵ�
	pre->next = p->next;
	p->next = NULL;
	DestroyStr(head);     //ɾ�����滻����
	
	head = NULL;
	p = NULL;            //��������
	while(q != NULL)      //����s2
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = q->data;
		if(head == NULL)
		{
			head = p;
			r = p;
		}
		else
		{
			r->next = p;
			r = p;
		}
		q = q->next;
	}
	r->next = pre->next;   //����
	pre->next = head;
	return true;
}

/*InsStr:���ַ���s1�ĵ�i���ַ�֮ǰ�����ַ���s2*/
bool InsStr(LiString *&s1, LiString *s2, int i)
{
	int k = 1;
	LiString *p = s1->next, *pre = s1, *head = NULL, *r;
	LiString *q = s2->next;
	int length = StrLength(s1);
	if(i < 1 || i > length)
		return false;
	
	while(k != i)
	{
		k++;
		pre = p;
		p = p->next;
	}//ִ����Ϻ�pָ��i�ڵ㣬preָ��i-1�ڵ�
	
	p = NULL;             //��������
	while(q != NULL)      //����s2
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = q->data;
		if(head == NULL)
		{
			head = p;
			r = p;
		}
		else
		{
			r->next = p;
			r = p;
		}
		q = q->next;
	}
	r->next = pre->next;   //����
	pre->next = head;
	return true;
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
	LiString *s1, *s2;
	char cstr[MaxSize];
	InitStr(s1);
	InitStr(s2);
	
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
				MakeEmpty(s1);
				StrAssign(s1,cstr);
				break;
			}
			case 2:{
				for(int k = 0; k < MaxSize; k++)
					cstr[k] = '\0';
				gets(cstr);
				MakeEmpty(s2);
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
				Concat(s1,s2);
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