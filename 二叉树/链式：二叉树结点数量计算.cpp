#include <stdio.h>
#include <stdlib.h>

/**************************************/
/*������������ö������洢�ṹ�洢��  *
 *���һ���㷨������һ�ø�����������  *
 *���нڵ������                      */ 
/**************************************/

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

/*Nodes:ͳ�ƶ������ڵ��㷨*/
int Nodes(BTNode *b)
{//�ݹ��㷨
	if(b == NULL)
		return 0;
	else
		return Nodes(b->lchild)+Nodes(b->rchild)+1;
}

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreateBTNode(b,str);
	printf("ԭ�������ѹ���ɶ������������ű�ʾ����ʾΪ��\n");
	DispBTNode(b); printf("\n\n");
	
	printf("�ö��������ܽڵ����ǣ�");
	printf("%d\n",Nodes(b));
	
	system("pause");
	return 0;
}