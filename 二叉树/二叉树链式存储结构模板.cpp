#include <stdio.h>
#include <stdlib.h>

/********************/
/*��������ʽ�洢�ṹ*/
/********************/

#define MaxSize 50
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild, *rchild;
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

/*DestroyBT:���ٶ�����*/
void DestroyBT(BTNode *&b)
{
	if(b == NULL)
		return ;
	else
	{
		DestroyBT(b->lchild);
		DestroyBT(b->rchild);
		free(b);    //ʣ��һ���ڵ�*b��ֱ���ͷ�
	}
}

/*FindNode:���ҽڵ��ַ*/
BTNode *FindNode(BTNode *b, ElemType x)
{
	BTNode *p;
	if(b == NULL)
		return NULL;
	else if(b->data == x)
		return b;
	else
	{
		p = FindNode(b->lchild,x);  //�ȴ���������
		if(p != NULL)               //�ҵ���
			return p;
		else                        //�ٴ���������
			return FindNode(b->rchild,x);
	}
}

/*LchildNode:�������ӽڵ�*/
BTNode *LchildNode(BTNode *p)
{return p->lchild;}

/*RchildNode:�����Һ��ӽڵ�*/
BTNode *RchildNode(BTNode *p)
{return p->rchild;}

/*BTNodeDepth:��������߶�*/
int BTNodeDepth(BTNode *b)
{
	int lchilddep, rchilddep;
	if(b == NULL) return 0;  //�����߶�Ϊ0
	else
	{
		lchilddep = BTNodeDepth(b->lchild);
		                        //���������߶�
		rchilddep = BTNodeDepth(b->rchild);
		                        //���������߶�
		return (lchilddep > rchilddep)?(lchilddep+1):(rchilddep+1);
		                        //������������߶�+1
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

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))" , x;
	BTNode *b, *p, *a;
	CreateBTNode(b,str);
	
	printf("����һ���߶�Ϊ%d�Ķ�����\n",BTNodeDepth(b));
	printf("�����ݸö�������ӡԭ�ַ���Ϊ��\n");
	DispBTNode(b);
	printf("\n");
	
	printf("����Ԫ��x\n");
	for(int i = 0; i < 8; i++){
	scanf("%c",&x);
	getchar();
	if((p = FindNode(b,x)) != NULL)
	{
	    printf("Ԫ��%c�����Һ����ǣ�\n",x);
	    if((a = LchildNode(p)) != NULL)
		    printf("��%c\n",a->data);
	    else
		    printf("����Ϊ��\n");
	    if((a = RchildNode(p)) != NULL)
		    printf("�ң�%c\n",a->data);
	    else
		    printf("�Һ���Ϊ��\n");
	}
	else
		printf("�����ڸ�Ԫ��\n");
    }
	
	
	DestroyBT(b);
	system("pause");
	return 0;
}