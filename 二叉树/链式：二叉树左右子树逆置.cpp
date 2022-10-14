#include <stdio.h>
#include <stdlib.h>

/***************************************/
/*������������ö������洢�ṹ�����һ *
 *���㷨�Ѷ�����b�����������ã���������*
 *��������������t��                    */
/***************************************/

#define MaxSize 50
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild,*rchild;
}BTNode;

/*CreateBTNode:����������*/
void CreateBTNode(BTNode *&b, char *str)
{//����ʾ����A(B(D(,G)),C(E,F))
	BTNode *St[MaxSize], *p;   //StΪָ��ջ
	int top = -1, k, j = 0;    //k���ڱ�ʶ״̬��j���ڱ����ַ���
	char ch;
	b = NULL;                  //��������ʼʱΪ��
	ch = str[j];
	while(ch != '\0')          //ѭ��ɨ��
	{
		switch(ch)
		{
			case'(': top++; St[top] = p; k = 1; break;   //���������ӣ���ջ
			case')': top--; break;                       //������ջ��Ԫ�ؿ��ܵ����Һ��ӣ���ջ
			case',': k = 2; break;
			default:{//�����ڵ�ֵ
			    p = (BTNode*)malloc(sizeof(BTNode));
				p->data = ch; p->lchild = p->rchild = NULL;
				if(b == NULL)     //pΪ���������ڵ�
				    b = p;
			    else{             //�ѽ������������ڵ�
					switch(k)     //ɨ�赱ǰ״̬��ʶ��k
					{
						case 1: St[top]->lchild = p; break;
						case 2: St[top]->rchild = p; break;
					}
				}
			}
		}
		j++; ch = str[j];    //����ɨ��str
	}
}

/*DispBTNode:���������*/
void DispBTNode(BTNode *b)
{//���ʾ����A(B(D(,G)),C(E,F))
	if(b != NULL)
	{
		printf("%c",b->data);
		if(b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTNode(b->lchild);  //�ݹ鴦��������
			if(b->rchild != NULL) printf(",");
			DispBTNode(b->rchild);  //�ݹ鴦��������
			printf(")");
		}
	}
}

/*Swap:���ö�����*/
void Swap(BTNode *b, BTNode *&t)
{
	if(b == NULL) t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		t->data = b->data;           //����һ�����ڵ�*t
		Swap(b->lchild, t->rchild);  //�ݹ齻��������
		Swap(b->rchild, t->lchild);  //�ݹ齻��������
	}
}

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreateBTNode(b,str);
	printf("ԭ�������ѹ���ɶ������������ű�ʾ����ʾΪ��\n");
	DispBTNode(b); printf("\n\n");
	
	printf("����������������һ��������t\n");
	BTNode *t;
	Swap(b,t);
	
	printf("t������ϣ������ű�ʾ����ʾΪ��\n");
	DispBTNode(t); printf("\n\n");
	
	system("pause");
	return 0;
}