#include <stdio.h>
#include <stdlib.h>

/*********************************/
/*������������ö������洢�ṹ�� *
 *���һ���㷨����Ӹ��ڵ㵽ÿ�� *
 *Ҷ�ӽڵ����·����             */
/*********************************/

#define MaxSize 50
int count;  //·������
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

/*AllPath:���شӸ��ڵ㵽ÿ��Ҷ�ӽڵ����·��*/
void AllPath(BTNode *b)
{
	struct snode
	{
		BTNode *node;     //��ŵ�ǰ�ڵ�ָ��
		int parent;       //���˫�׽ڵ��ڶ����е�λ��
	}qu[MaxSize];         //����ǻ��ζ���
	BTNode *q;
	int front, rear, p;   //�����ͷ�Ͷ�βָ��
	front = rear = -1;    //�ö���β�ն���
	rear++;
	qu[rear].node = b;    //���ڵ�ָ��������
	qu[rear].parent = -1; //���ڵ�û��˫�׽ڵ�
	while(front != rear)      //���в�Ϊ��
	{
		front++;              //front�ǵ�ǰ�ڵ�*q��qu�е�λ��
		q = qu[front].node;   //��ͷ�����У��ýڵ�ָ������qu��
		if(q->lchild == NULL && q->rchild == NULL)//*qΪҶ�ӽڵ�
		{//���*q�����ڵ����·������
		    p = front;
			printf("��%d��·��Ϊ:",count++);
			while(qu[p].parent != -1)
			{
				printf("%c->",qu[p].node->data);
				p = qu[p].parent;
			}
			printf("%c\n",qu[p].node->data);
		}
		
		if(q->lchild != NULL)         //*q�ڵ�������ʱ�������
		{
			rear++;
			qu[rear].node = q->lchild;
			qu[rear].parent = front;  //*q���ӵ�˫��λ��Ϊfront
		}
		if(q->rchild != NULL)         //*q�ڵ����к���ʱ�������
		{
			rear++;
			qu[rear].node = q->rchild;
			qu[rear].parent =front;   //*q�Һ��ӵ�˫��λ��Ϊfront
		}
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
	
	printf("��ӡ�Ӹ��ڵ㵽ÿ��Ҷ�ӽڵ����·��:\n");
	AllPath(b);
	
	system("pause");
	return 0;
}