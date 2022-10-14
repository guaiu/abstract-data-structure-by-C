#include <stdio.h>
#include <stdlib.h>

/**********/
/*哈夫曼树*/
/**********/

#define MaxSize 27
typedef char ElemType;
typedef struct node
{
	ElemType data;
	int weight;    //权重
	struct node *lchild, *rchild;
}BTNode;

/*CreateHuffman:生成一颗哈夫曼树*/
BTNode *CreateHuffman(ElemType ch[], int a[], int n)
{
	int i, j;
	BTNode **b, *q;
	b = (BTNode**)malloc(n*sizeof(BTNode*));
	for(i = 0; i < n; i++)//初始化b指针数组，使每个指针元素指向ch数组中对应的元素节点
	{
		b[i] = (BTNode*)malloc(sizeof(BTNode));
		b[i]->data = ch[i];
		b[i]->weight = a[i];
		b[i]->lchild = b[i]->rchild = NULL;
	}
	for(i = 1; i < n; i++)//进行n-1次循环建立哈夫曼树
	{  //k1指向森林中最小权值树根结点下标，k2指向次小
		int k1 = -1, k2;
        for(j = 0; j < n; j++)//让k1初始指向森林第一棵非空树，k2指向第二棵非空树
        {
			if(b[j] != NULL && k1 == -1)
			{k1 = j; continue;}
		    if(b[j] != NULL)
			{k2 = j; break;}
		}	
	    //此时k2指向第二棵非空树，所以j从k2处开始遍历
	    for(j = k2; j < n; j++)//从森林中找出最小权值树和次小权值树
	    {
		    if(b[j] != NULL)
		    {
			    if(b[j]->weight < b[k1]->weight)
			    {k2 = k1; k1 = j;}
		        else if(b[j]->weight < b[k2]->weight)
			    {k2 = j;}
		    }
	    }
		//由最小权值树和次小权值树建立一棵新树，q指向树根结点
		//注：非叶子节点data域无意义，此处为了辨识设为"#"
		q = (BTNode*)malloc(sizeof(BTNode));
		q->data = '#';
		q->weight = b[k1]->weight + b[k2]->weight;
		q->lchild = b[k1];
		q->rchild = b[k2];
		
		b[k1] = q;    //将指向新树的指针赋给b指针数组中k1位置
		b[k2] = NULL; //k2位置置空
	}
	free(b);  //删除指针数组
	return q; //返回哈夫曼树的树根指针
}

/*DispBTNode:输出二叉树*/
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

/*DataInput:数据树、数据值、权值的输入*/
void DataInput(ElemType *ch, int *a, int &n)
{
	int i;
	printf("请连续输入不超过最大数量的字符数据:\n");
	scanf("%s",ch);
	for(n = 0; ch[n] != '\0'; n++) ;//检查输入字符数
	printf("检查到输入了%d个字符\n",n);
	printf("请依次输入对应字符数据权值:\n");
	for(i = 0; i < n; i++)
		scanf("%d",&a[i]);
}

/*WeightPathLength:求哈夫曼树的带权路径长度*/
int WeightPathLength(BTNode *b, int len)//len初始为0
{
	if(b == NULL)  //空树返回0
	return 0;
	else
	{
		if(b->lchild == NULL && b->rchild == NULL)//访问到叶子结点
		    return (b->weight * len);
		else  //访问到非叶子结点，进行递归调用，返回左右子树的带权路径长度
		    return WeightPathLength(b->lchild,len+1)+WeightPathLength(b->rchild,len+1);
	}
}

/*HuffManCoding:输出哈夫曼编码*/
void HuffManCoding(BTNode *b, int len)//len初始值为0
{
	static int a[10];//定义静态数组a，保存每个叶子的编码，数组长度至少是树深度减一
	if(b != NULL)  //访问到叶子结点时输出其保存在数组a中的0和1序列编码
	{
		if(b->lchild == NULL && b->rchild == NULL)
		{
			int i;
			printf("字符%c的权值为%d，编码为:",b->data, b->weight);
			for(i = 0; i < len; i++)
				printf("%d",a[i]);
			printf("\n");
		}
		else//访问到非叶子结点时分别向左右子树递归调用，并把分支上的0、1编码保存到数组a
		{    //的对应元素中，向下深入一层时len增1
			a[len] = 0;
			HuffManCoding(b->lchild, len+1);
			a[len] = 1;
			HuffManCoding(b->rchild, len+1);
		}
	}
}

/*主函数*/
int main()
{
	BTNode *b;
	ElemType ch[MaxSize];
	int a[MaxSize], n;
	DataInput(ch,a,n);
	b = CreateHuffman(ch,a,n);
	printf("建立了哈夫曼树为:\n");
	DispBTNode(b); printf("\n");
	printf("哈夫曼树带权路径长度为：%d\n",WeightPathLength(b,0));
	HuffManCoding(b,0);
	
	system("pause");
	return 0;
}