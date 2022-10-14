#include <stdio.h>
#include <stdlib.h>

/**********/
/*��������*/
/**********/

#define MaxSize 27
typedef char ElemType;
typedef struct node
{
	ElemType data;
	int weight;    //Ȩ��
	struct node *lchild, *rchild;
}BTNode;

/*CreateHuffman:����һ�Ź�������*/
BTNode *CreateHuffman(ElemType ch[], int a[], int n)
{
	int i, j;
	BTNode **b, *q;
	b = (BTNode**)malloc(n*sizeof(BTNode*));
	for(i = 0; i < n; i++)//��ʼ��bָ�����飬ʹÿ��ָ��Ԫ��ָ��ch�����ж�Ӧ��Ԫ�ؽڵ�
	{
		b[i] = (BTNode*)malloc(sizeof(BTNode));
		b[i]->data = ch[i];
		b[i]->weight = a[i];
		b[i]->lchild = b[i]->rchild = NULL;
	}
	for(i = 1; i < n; i++)//����n-1��ѭ��������������
	{  //k1ָ��ɭ������СȨֵ��������±꣬k2ָ���С
		int k1 = -1, k2;
        for(j = 0; j < n; j++)//��k1��ʼָ��ɭ�ֵ�һ�÷ǿ�����k2ָ��ڶ��÷ǿ���
        {
			if(b[j] != NULL && k1 == -1)
			{k1 = j; continue;}
		    if(b[j] != NULL)
			{k2 = j; break;}
		}	
	    //��ʱk2ָ��ڶ��÷ǿ���������j��k2����ʼ����
	    for(j = k2; j < n; j++)//��ɭ�����ҳ���СȨֵ���ʹ�СȨֵ��
	    {
		    if(b[j] != NULL)
		    {
			    if(b[j]->weight < b[k1]->weight)
			    {k2 = k1; k1 = j;}
		        else if(b[j]->weight < b[k2]->weight)
			    {k2 = j;}
		    }
	    }
		//����СȨֵ���ʹ�СȨֵ������һ��������qָ���������
		//ע����Ҷ�ӽڵ�data�������壬�˴�Ϊ�˱�ʶ��Ϊ"#"
		q = (BTNode*)malloc(sizeof(BTNode));
		q->data = '#';
		q->weight = b[k1]->weight + b[k2]->weight;
		q->lchild = b[k1];
		q->rchild = b[k2];
		
		b[k1] = q;    //��ָ��������ָ�븳��bָ��������k1λ��
		b[k2] = NULL; //k2λ���ÿ�
	}
	free(b);  //ɾ��ָ������
	return q; //���ع�������������ָ��
}

/*DispBTNode:���������*/
void DispBTNode(BTNode *b)
{
	if(b != NULL)
	{
		printf("%c",b->data);
		if(b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTNode(b->lchild);
			if(b->rchild != NULL)
				printf(",");
			DispBTNode(b->rchild);
			printf(")");
		}
	}
}

/*DataInput:������������ֵ��Ȩֵ������*/
void DataInput(ElemType *ch, int *a, int &n)
{
	int i;
	printf("���������벻��������������ַ�����:\n");
	scanf("%s",ch);
	for(n = 0; ch[n] != '\0'; n++) ;//��������ַ���
	printf("��鵽������%d���ַ�\n",n);
	printf("�����������Ӧ�ַ�����Ȩֵ:\n");
	for(i = 0; i < n; i++)
		scanf("%d",&a[i]);
}

/*WeightPathLength:����������Ĵ�Ȩ·������*/
int WeightPathLength(BTNode *b, int len)//len��ʼΪ0
{
	if(b == NULL)  //��������0
	return 0;
	else
	{
		if(b->lchild == NULL && b->rchild == NULL)//���ʵ�Ҷ�ӽ��
		    return (b->weight * len);
		else  //���ʵ���Ҷ�ӽ�㣬���еݹ���ã��������������Ĵ�Ȩ·������
		    return WeightPathLength(b->lchild,len+1)+WeightPathLength(b->rchild,len+1);
	}
}

/*HuffManCoding:�������������*/
void HuffManCoding(BTNode *b, int len)//len��ʼֵΪ0
{
	static int a[10];//���徲̬����a������ÿ��Ҷ�ӵı��룬���鳤������������ȼ�һ
	if(b != NULL)  //���ʵ�Ҷ�ӽ��ʱ����䱣��������a�е�0��1���б���
	{
		if(b->lchild == NULL && b->rchild == NULL)
		{
			int i;
			printf("�ַ�%c��ȨֵΪ%d������Ϊ:",b->data, b->weight);
			for(i = 0; i < len; i++)
				printf("%d",a[i]);
			printf("\n");
		}
		else//���ʵ���Ҷ�ӽ��ʱ�ֱ������������ݹ���ã����ѷ�֧�ϵ�0��1���뱣�浽����a
		{    //�Ķ�ӦԪ���У���������һ��ʱlen��1
			a[len] = 0;
			HuffManCoding(b->lchild, len+1);
			a[len] = 1;
			HuffManCoding(b->rchild, len+1);
		}
	}
}

/*������*/
int main()
{
	BTNode *b;
	ElemType ch[MaxSize];
	int a[MaxSize], n;
	DataInput(ch,a,n);
	b = CreateHuffman(ch,a,n);
	printf("�����˹�������Ϊ:\n");
	DispBTNode(b); printf("\n");
	printf("����������Ȩ·������Ϊ��%d\n",WeightPathLength(b,0));
	HuffManCoding(b,0);
	
	system("pause");
	return 0;
}