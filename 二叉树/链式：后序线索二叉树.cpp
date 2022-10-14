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
	struct node *parent; //˫�׽ڵ�
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

/*InitParent:˫��ָ���ʼ��*/
void InitParent(TBTNode *&b)
{
	if(b != NULL)
	{
		if(b->lchild != NULL)
			b->lchild->parent = b;
		if(b->rchild != NULL)
			b->rchild->parent = b;
		InitParent(b->lchild);
		InitParent(b->rchild);
	}
}

/*PostOrderThread:����������������*/
TBTNode* pre;     //ȫ�ֱ���
void PostOrderThread(TBTNode *&p)
{
	if(p != NULL)
	{
		PostOrderThread(p->lchild);         //������������
		PostOrderThread(p->rchild);         //������������
		
		if(p->lchild == NULL)               //ǰ��������
		{ p->lchild = pre; p->ltag = 1;}    //������ǰ�ڵ��ǰ������
		else p->ltag = 0;
		if(pre->rchild == NULL)             //���������
		{ pre->rchild = p; pre->rtag = 1;}  //����ǰ���ڵ�ĺ������
		else pre->rtag = 0;
		pre = p;
	}
}

/*CreatPostOrderTBTNode:����������������*/
TBTNode *CreatPostOrderTBTNode(TBTNode *b)
{//�еݹ�˼��
    TBTNode *root;
	root = (TBTNode*)malloc(sizeof(TBTNode));  //����ͷ�ڵ�
	root->ltag = 0; root->rtag = 1; root->rchild = b;
	/*���ֳ�ʼ����ʽΪ�·����㷨����*/
	if(b == NULL) root->lchild = root;         //�ն�����
	else
	{
		b->parent = root;
		InitParent(b);        //��ʼ��˫��ָ��
		root->lchild = b;
		pre = root;           //pre��*p��ǰ���ڵ㣬����������
		PostOrderThread(b);    //�������������������
		root->rchild = pre;   //ͷ�ڵ���������
		root->rtag = 1;
		if(b->rchild == NULL) //���ڵ���������
		{
			b->rchild = root;
			b->rtag = 1;
		}
		else                  //���ڵ���������
			b->rtag = 0;
	}
	return root;
}

/*ThPostOrder:���������������ĺ������*/
void ThPostOrder(TBTNode *tb)
{
	TBTNode *pre = tb, *p = tb->lchild;    //pָ��ǰ�ڵ㣬pre������¼��һ�����ڵ�
	while(p != tb)
	{
		while(p->ltag == 0 && p->lchild != pre)  //�ҵ���ǰ��������ڵ�
	        p = p->lchild;
		while(p->rtag == 1 && p != tb)           //ѭ������������ȥ
		{
			printf("%c",p->data);
			pre = p;
			p = p->rchild;
		}
		while(p->rchild == pre && p != tb)
		{//��ǰ�ڵ���ҽڵ�Ϊ��һ�α����ڵ�
	        printf("%c",p->data);
			pre = p;
			p = p->parent;                 //����һ����
		}
		if(p != tb && p->rtag == 0)
			p = p->rchild;                 //����ǰ�ڵ�������
	}
}

/*���˲���*/
/*Text:���������������ĺ�������������ӡ*/
void Text(TBTNode *tb)
{
	TBTNode *p = tb->lchild;
	while(p != tb)
	{
		while(p->rtag == 0)
		{//�����ұ߷�����ȥ
			printf("%c",p->data);
			p = p->rchild;
		}
		printf("%c",p->data);  //�������ұߵĽڵ�
		while(p->ltag == 1 && p->lchild != tb)
		{//����������������ȥ
			p = p->lchild;
			printf("%c",p->data);
		}
		p = p->lchild;         //����������(��ʱ��Ϊ��ǰ�������ڵ�)
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
	tb = CreatPostOrderTBTNode(b);
	printf("�������������������������������Ϊ��");
	ThPostOrder(tb); printf("\n");
	
	printf("\n���ԣ������ӡ����������������");
	Text(tb); printf("\n");
	
	system("pause");
	return 0;
}