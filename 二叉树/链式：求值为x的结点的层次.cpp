#include <stdio.h>
#include <stdlib.h>

/*****************************************/
/*������������ö������洢�ṹ�����һ�� *
 *�㷨Level()�������b��ֵΪx�Ľڵ�Ĳ��*
 *���������нڵ�ֵΨһ��                 */
/*****************************************/

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

/*Level:���ض�������dataֵΪx�Ľڵ㲢���ز�Σ���û�ҵ��򷵻�0*/
int Level(BTNode *b, ElemType x, int h)
{//�ҵ�*p�ڵ��hΪ���Σ�����Ϊ0
    int l;
	if(b == NULL) return 0;           //����ʱ����0
	else if(b->data == x) return h;   //�ҵ��ڵ�ʱ
	else
	{
		l = Level(b->lchild, x, h+1); //���������в���
		if(l == 0)                    //��������δ�ҵ�ʱ���������в���
			return Level(b->rchild,x,h+1);
		else return l;
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
	
	ElemType x;
	printf("����ڵ�ֵx:");
	scanf("%c",&x);
	printf("%c�ڶ�������%d��\n",x,Level(b,x,1)); 
	
	system("pause");
	return 0;
}