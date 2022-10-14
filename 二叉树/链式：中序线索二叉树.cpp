#include <stdio.h>
#include <stdlib.h>

/****************/
/*��������������*/
/****************/

#define MaxSize 30
typedef char ElemType;
typedef struct node
{
	ElemType data;       //�ڵ�������
	int ltag, rtag;      //���ӵ��������
	struct node *lchild; //���ӻ�����ָ��
	struct node *rchild; //�Һ��ӻ�����ָ��
}TBTNode;                //�������ڵ����Ͷ���


/*CreatBTNode:����������(δ������)*/
void CreatBTNode(TBTNode *&b, char *str)
{//����ʾ����A(B(D(,G)),C(E,F))
	TBTNode *St[MaxSize], *p;
	int top = -1, k, j = 0;
	char ch;
	b = NULL;
	ch = str[j];
	while(ch != '\0')
	{
		switch(ch)
		{
			case'(': top++; St[top] = p; k = 1; break;
			case')': top--; break;
			case',': k = 2; break;
			default:{
				p = (TBTNode*)malloc(sizeof(TBTNode));
				p->data = ch; p->lchild = p->rchild = NULL;
				if(b == NULL)
					b = p;
				else
					switch(k)
					{
						case 1: St[top]->lchild = p; break;
						case 2: St[top]->rchild = p; break;
					}
			}
		}
		j++; ch = str[j];
	}
}

/*DispBTNode:����ԭ��ʽ���������(δ������)*/
void DispBTNode(TBTNode *b)
{//���ʾ����A(B(D(,G)),C(E,F))
    if(b != NULL)
	{
		printf("%c",b->data);
		if(b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTNode(b->lchild);
			if(b->rchild != NULL) printf(",");
			DispBTNode(b->rchild);
			printf(")");
		}
	}
}

/*InOrderThread:����������������*/
TBTNode *pre;   //ȫ�ֱ���
void InOrderThread(TBTNode *&p)
{
	if(p != NULL)
	{
		InOrderThread(p->lchild);         //������������
		if(p->lchild == NULL)             //ǰ��������
		{ p->lchild = pre; p->ltag = 1;}  //������ǰ�ڵ��ǰ������
		else p->ltag = 0;
		if(pre->rchild == NULL)           //���������
		{ pre->rchild = p; pre->rtag = 1;}//����ǰ���ڵ�ĺ������
	    else pre->rtag = 0;
		pre = p;
		InOrderThread(p->rchild);         //�ݹ����������������
	}
}

/*CreatInOrderTBTNode:����������������*/
TBTNode *CreatInOrderTBTNode(TBTNode *b)
{
	TBTNode *root;
	root = (TBTNode*)malloc(sizeof(TBTNode));        //����ͷ�ڵ�
	root->ltag = 0; root->rtag = 1; root->rchild = b;
	/*���ֳ�ʼ����ʽΪ�·����㷨����*/
	if(b == NULL) root->lchild = root;               //�ն�����
	else
	{
		root->lchild = b;
		pre = root;            //pre��*p��ǰ���ڵ㣬����������
		InOrderThread(b);      //�������������������
		pre->rchild = root;    //���������ָ��ͷ�ڵ������
		pre->rtag = 1;
		root->rchild = pre;    //ͷ�ڵ���������
		root->rtag = 1;
	}
	return root;
}

/*ThInOrder:�����������������������*/
void ThInOrder(TBTNode *tb)
{//�еݹ�˼��
	TBTNode *p = tb->lchild;   //pָ����ڵ�
	while(p != tb)             //������������Ϊ����
	{
		while(p->ltag == 0) p = p->lchild;  //�ҵ�ǰ������ʼ�ڵ�
		printf("%c",p->data);               //���ʵ�ǰ������ʼ�ڵ�
		while(p->rtag == 1 && p->rchild != tb)
		{//�����������һֱ������ȥ
			p = p->rchild;
			printf("%c",p->data);
		}
		p = p->rchild;         //���ʵ�ǰ�������ڵ��������
	}
}

/*���˲���*/
/*Text:������������������������������ӡ*/
void Text(TBTNode *tb)
{//������������˵ݹ�˼��
	TBTNode *p = tb->rchild;   //pָ����ڵ�
	if(p == NULL)
		return ;               //�����˳�
	while(p != tb)
	{
	    while(p->rtag == 0) p = p->rchild;   //�ҵ�ǰ������ʼ�ڵ�
		printf("%c",p->data);                //���ʵ�ǰ������ʼ�ڵ�
	    while(p->ltag == 1 && p->lchild != tb)
		{//˳������������ȥ
			p = p->lchild;
			printf("%c",p->data);
		}
		p = p->lchild;        //���ʵ�ǰ�������ڵ��������
	}
}

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	TBTNode *b;
	CreatBTNode(b,str);
	printf("ԭ�������ѹ���ɶ������������ű�ʾ����ʾΪ��\n");
	DispBTNode(b); printf("\n\n");
	
	TBTNode *tb;
	tb = CreatInOrderTBTNode(b);
	printf("�������������������������������Ϊ��");
	ThInOrder(tb);
	
	printf("\n���ԣ������ӡ����������������");
	Text(tb); printf("\n");
	
	system("pause");
	return 0;
}