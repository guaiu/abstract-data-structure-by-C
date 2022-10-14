#include <stdio.h>
#include <stdlib.h>

/************************/
/*���ݱ������й��������*/
/************************/

#define MaxSize 30
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild,*rchild;
}BTNode;

typedef struct
{
	ElemType data[MaxSize];
	int size;
}SqList;  //���ڴ�ű������еı�

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

/*DispList:��ӡ��*/
void DispList(SqList *l)
{
	int k;
	for(k = 0; k < l->size; k++)
		printf("%c",l->data[k]);
	printf("\n");
}

/*PreOrder:�������������*/
void PreOrder(BTNode *b, SqList *pre)
{//�ݹ��㷨
	if(b != NULL)
	{
		pre->data[pre->size++] = b->data;  //���ʸ��ڵ�
		PreOrder(b->lchild,pre); //�ݹ����������
		PreOrder(b->rchild,pre); //�ݹ����������
	}
}

/*InOrder:�������������*/
void InOrder(BTNode *b, SqList *in)
{//�ݹ��㷨
	if(b != NULL)
	{
		InOrder(b->lchild,in);     //�ݹ����������
		in->data[in->size++] = b->data;      //���ʸ��ڵ�
		InOrder(b->rchild,in);     //�ݹ����������
	}
}


/*PostOrder:�������������*/
void PostOrder(BTNode *b, SqList *post)
{//�ݹ��㷨
	if(b != NULL)
	{
		PostOrder(b->lchild,post); //�ݹ����������
		PostOrder(b->rchild,post); //�ݹ����������
		post->data[post->size++] = b->data;  //���ʸ��ڵ�
	}
}

/*CreatBT1:�����������к��������й��������*/
BTNode *CreatBT1(char *pre, char *in, int n)
{
	BTNode *s; char *p; int k;
	if(n <= 0) return NULL;
	s = (BTNode*)malloc(sizeof(BTNode));  //�������ڵ�
	s->data = *pre;                       //�������е�һ��Ԫ��Ϊ���ڵ�
	for(p = in; p < in+n; p++)            //��in���ҵ�ֵΪ*pre��λ��
	    if(*p == *pre)
			break;
		k = p-in;                         //��k��¼λ��ֵ
	
	s->lchild = CreatBT1(pre+1,in,k);         //�ݹ鹹��������
	s->rchild = CreatBT1(pre+k+1,p+1,n-k-1);  //�ݹ鹹��������
	return s;
}

/*CreatBT2:���ݺ������к��������й��������*/
BTNode *CreatBT2(char *post, char *in, int n)
{
	BTNode *b; char r, *p; int k;
	if(n <= 0) return NULL;
	r = *(post+n-1);                     //�����������һ��Ԫ��Ϊ���ڵ�
	b = (BTNode*)malloc(sizeof(BTNode)); //�������ڵ�b
	b->data = r;
	for(p = in; p < in+n; p++)           //���Ҹ��ڵ�
	    if(*p == r) break;
		k = p-in;                        //kΪ���ڵ���in�е��±�
		
	b->lchild = CreatBT2(post,in,k);          //�ݹ鹹��������
	b->rchild = CreatBT2(post+k, p+1, n-k-1); //�ݹ鹹��������
	return b;
}

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreatBTNode(b,str);
	printf("ԭ�������ѹ���ɶ������������ű�ʾ����ʾΪ��\n");
	DispBTNode(b); printf("\n\n");
	
	SqList pre, in, post;
	pre.size = in.size = post.size = 0;
	PreOrder(b,&pre); InOrder(b,&in); PostOrder(b,&post);  //�����������б�
	printf("��ñ�������:\n");
	printf("��������:"); DispList(&pre);                 //�鿴
	printf("��������:"); DispList(&in);
	printf("��������:"); DispList(&post);
	
	BTNode *t1, *t2;
	int n = pre.size;                    //��¼��С(in.size, post.size���ͬ)
	t1 = CreatBT1(pre.data,in.data,n); //���¹��������
	t2 = CreatBT2(post.data,in.data,n);
	printf("��������������ع��ɵã�"); DispBTNode(t1); printf("\n");
	printf("���ݺ���������ع��ɵã�"); DispBTNode(t2); printf("\n");
	
	system("pause");
	return 0;
}