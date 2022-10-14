#include <stdio.h>
#include <stdlib.h>

/******************/
/*�����������ֱ���*/
/******************/

#define MaxSize 50
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild,*rchild;
}BTNode;

/*CreatBTNode:����������*/
void CreatBTNode(BTNode *&b, char *str)
{//����ʾ����A(B(D(,G)),C(E,F))
	BTNode *St[MaxSize], *p;
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
				p = (BTNode*)malloc(sizeof(BTNode));
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


/*DispBTNode:����ԭ��ʽ���������*/
void DispBTNode(BTNode *b)
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

/*PreOrder:�������������*/
void PreOrder(BTNode *b)
{//�ݹ��㷨
	if(b != NULL)
	{
		printf("%c",b->data);  //���ʸ��ڵ�
		PreOrder(b->lchild);   //�ݹ����������
		PreOrder(b->rchild);   //�ݹ����������
	}
}

/*InOrder:�������������*/
void InOrder(BTNode *b)
{//�ݹ��㷨
	if(b != NULL)
	{
		InOrder(b->lchild);   //�ݹ����������
		printf("%c",b->data);  //���ʸ��ڵ�
		InOrder(b->rchild);   //�ݹ����������
	}
}


/*PostOrder:�������������*/
void PostOrder(BTNode *b)
{//�ݹ��㷨
	if(b != NULL)
	{
		PostOrder(b->lchild);   //�ݹ����������
		PostOrder(b->rchild);   //�ݹ����������
		printf("%c",b->data);  //���ʸ��ڵ�
	}
}

/*LevelOrder:��α���������*/
void LevelOrder(BTNode *b)
{//�������й���
	BTNode *p;
	BTNode *qu[MaxSize];  //���廷�ζ��У���Žڵ�ָ��
	int front, rear;       //�����ͷ�Ͷ�βָ��
	front = rear = 0;     //�ö���Ϊ�ն���
	rear++;
	qu[rear] = b;         //���ڵ�ָ��������
	
	while(front != rear)  //�Ӳ���ѭ��
	{
		front = (front+1)%MaxSize;
		p = qu[front];           //��ͷ������
		printf("%c",p->data);    //���ʽڵ�
		if(p->lchild != NULL)    //�����������ӽ���
		{
			rear = (rear+1)%MaxSize;
			qu[rear] = p->lchild;
		}
		if(p->rchild != NULL)    //���Һ���ʱ�������
		{
			rear = (rear+1)%MaxSize;
			qu[rear] = p->rchild;
		}
	}
}

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreatBTNode(b,str);
	printf("ԭ�������ѹ���ɶ������������ű�ʾ����ʾΪ��\n");
	DispBTNode(b); printf("\n\n");

	printf("���ڶԸö���������������ʽ�ı���\n");
	printf("����"); PreOrder(b); printf("\n");
	printf("����"); InOrder(b); printf("\n");
	printf("����"); PostOrder(b); printf("\n");
	printf("��Σ�"); LevelOrder(b); printf("\n");
	
	system("pause");
	return 0;
}