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

/*PreOrderThread:����������������*/
TBTNode* pre;     //ȫ�ֱ���
void PreOrderThread(TBTNode *&p)
{
	if(p != NULL)
	{
		if(p->lchild == NULL)               //ǰ��������
		{ p->lchild = pre; p->ltag = 1;}    //������ǰ�ڵ��ǰ������
		else p->ltag = 0;
		if(pre->rchild == NULL)             //���������
		{ pre->rchild = p; pre->rtag = 1;}  //����ǰ���ڵ�ĺ������
		else pre->rtag = 0;
		pre = p;
		
		//������NULL�жϣ�Ҫ��tag�ж��Ƿ������Һ���
		if(p->ltag != 1)
		    PreOrderThread(p->lchild);          //������������
		if(p->rtag != 1)
		    PreOrderThread(p->rchild);          //������������
	}//PS:����д���ǲ���ȫ�ģ�������ʲôʱ��ͳ����ˡ�����
}

/*CreatPreOrderTBTNode:����������������*/
TBTNode *CreatPreOrderTBTNode(TBTNode *b)
{//�еݹ�˼��
    TBTNode *root;
	root = (TBTNode*)malloc(sizeof(TBTNode));  //����ͷ�ڵ�
	root->ltag = 0; root->rtag = 1; root->rchild = b;
	/*���ֳ�ʼ����ʽΪ�·����㷨����*/
	if(b == NULL) root->lchild = root;         //�ն�����
	else
	{
		root->lchild = b;
		pre = root;           //pre��*p��ǰ���ڵ㣬����������
		PreOrderThread(b);    //�������������������
		pre->rchild = root;   //���������ָ��ͷ�ڵ������
		pre->rtag = 1;
		root->rchild = pre;   //ͷ�ڵ���������
		root->rtag = 1;
	}
	return root;
}

/*ThPreOrder:�����������������������*/
void ThPreOrder(TBTNode *tb)
{
	TBTNode *p = tb->lchild;     //pָ����ڵ�
	while(p != tb)               //������������Ϊ����
	{
		while(p->ltag == 0)
		{//һֱ����ǰ���������������������ȥ
			printf("%c",p->data);
			p = p->lchild;
		}
		printf("%c",p->data);    //��������ߵĽڵ�
        p = p->rchild;           //��������������ѭ����������
	}
}


/*���˲���*/
/*Text:������������������������������ӡ*/
/*���ۣ���ǰ�ṹ�޷�����*/

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	TBTNode *b;
	CreatBTNode(b,str);
	printf("ԭ�������ѹ���ɶ������������ű�ʾ����ʾΪ��\n");
	DispBTNode(b); printf("\n\n");
	
	TBTNode *tb;
	tb = CreatPreOrderTBTNode(b);
	printf("�������������������������������Ϊ��");
	ThPreOrder(tb); printf("\n");
	
	system("pause");
	return 0;
}