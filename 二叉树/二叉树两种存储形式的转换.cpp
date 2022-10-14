#include <stdio.h>
#include <stdlib.h>

/**************************************/
/*��������ʽ�洢�ṹ��˳��洢�ṹת��*/
/**************************************/

#define MaxSize 30
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild, *rchild;
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

/*DispSqBTree:��ԭ��ʽ���˳�������*/
void DispBTree(ElemType *b, int p)  //pΪ��ǰ�鿴Ԫ�ص�ַ
{//���ʾ����A(B(D(,G)),C(E,F))
	if(b[p] != '#')
	{
		printf("%c",b[p]);
		if(b[p*2] != '#' || b[p*2+1] != '#')
		{
			printf("(");
			DispBTree(b, p*2);  //�ݹ鴦��������
			if(b[p*2+1] != '#') printf(",");
			DispBTree(b,p*2+1);  //�ݹ鴦��������
			printf(")");
		}
	}
}

/*trans1:˳��ת��ʽ*/
BTNode *trans1(ElemType *SqBTree, int i)
{
	BTNode *b;
	if(i > MaxSize) return NULL;
	if(SqBTree[i] == '#') return NULL;    //�ڵ㲻����ʱ����NULL
	b = (BTNode*)malloc(sizeof(BTNode));  //�����ڵ�
	b->data = SqBTree[i];
	b->lchild = trans1(SqBTree, 2*i);     //�ݹ鴴��������
	b->rchild = trans1(SqBTree, 2*i+1);   //�ݹ鴴��������
	return b;
}

/*trans2:��ʽת˳��*/
void trans2(BTNode *b, ElemType *SqBTree, int i)
{
	if(b != NULL)
	{
		SqBTree[i] = b->data;             //�������ڵ�
		trans2(b->lchild, SqBTree, 2*i);  //�ݹ鴴��������
		trans2(b->rchild,SqBTree, 2*i+1); //�ݹ鴴��������
	}
	else
		SqBTree[i] = '#';                 //��
}

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreatBTNode(b,str);
	printf("ԭ�������ѹ���ɶ������������ű�ʾ����ʾΪ��\n");
	DispBTNode(b); printf("\n\n");
	
	ElemType SqBTree[MaxSize];  //�涨��ʹ��λ���±�0
	SqBTree[1] = '#';           //���ڵ��ÿ�
	trans2(b,SqBTree,1);
	printf("��ʽת˳�򣬸���˳��洢��ԭ�Ķ�����Ϊ��\n");
	DispBTree(SqBTree,1); printf("\n");
	
	BTNode *t;
	t = trans1(SqBTree, 1);
	printf("˳��ת��ʽ��������ʽ�洢��ԭ�Ķ�����Ϊ:\n");
	DispBTNode(t); printf("\n");
	
	system("pause");
	return 0;
}