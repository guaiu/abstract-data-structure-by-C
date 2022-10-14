#include <stdio.h>
#include <stdlib.h>

/************************/
/*根据遍历序列构造二叉树*/
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
}SqList;  //用于存放遍历序列的表

/*CreatBTNode:创建二叉链*/
void CreatBTNode(BTNode *&b, char *str)
{//输入示例：A(B(D(,G)),C(E,F))
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


/*DispBTNode:按照原形式输出二叉树*/
void DispBTNode(BTNode *b)
{//输出示例：A(B(D(,G)),C(E,F))
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

/*DispList:打印表*/
void DispList(SqList *l)
{
	int k;
	for(k = 0; k < l->size; k++)
		printf("%c",l->data[k]);
	printf("\n");
}

/*PreOrder:先序遍历二叉树*/
void PreOrder(BTNode *b, SqList *pre)
{//递归算法
	if(b != NULL)
	{
		pre->data[pre->size++] = b->data;  //访问根节点
		PreOrder(b->lchild,pre); //递归访问左子树
		PreOrder(b->rchild,pre); //递归访问右子树
	}
}

/*InOrder:中序遍历二叉树*/
void InOrder(BTNode *b, SqList *in)
{//递归算法
	if(b != NULL)
	{
		InOrder(b->lchild,in);     //递归访问左子树
		in->data[in->size++] = b->data;      //访问根节点
		InOrder(b->rchild,in);     //递归访问右子树
	}
}


/*PostOrder:后序遍历二叉树*/
void PostOrder(BTNode *b, SqList *post)
{//递归算法
	if(b != NULL)
	{
		PostOrder(b->lchild,post); //递归访问左子树
		PostOrder(b->rchild,post); //递归访问右子树
		post->data[post->size++] = b->data;  //访问根节点
	}
}

/*CreatBT1:根据先序序列和中序序列构造二叉树*/
BTNode *CreatBT1(char *pre, char *in, int n)
{
	BTNode *s; char *p; int k;
	if(n <= 0) return NULL;
	s = (BTNode*)malloc(sizeof(BTNode));  //创建根节点
	s->data = *pre;                       //先序序列第一个元素为根节点
	for(p = in; p < in+n; p++)            //在in中找到值为*pre的位置
	    if(*p == *pre)
			break;
		k = p-in;                         //用k记录位移值
	
	s->lchild = CreatBT1(pre+1,in,k);         //递归构造左子树
	s->rchild = CreatBT1(pre+k+1,p+1,n-k-1);  //递归构造右子树
	return s;
}

/*CreatBT2:根据后序序列和中序序列构造二叉树*/
BTNode *CreatBT2(char *post, char *in, int n)
{
	BTNode *b; char r, *p; int k;
	if(n <= 0) return NULL;
	r = *(post+n-1);                     //后序序列最后一个元素为根节点
	b = (BTNode*)malloc(sizeof(BTNode)); //创立根节点b
	b->data = r;
	for(p = in; p < in+n; p++)           //查找根节点
	    if(*p == r) break;
		k = p-in;                        //k为根节点在in中的下标
		
	b->lchild = CreatBT2(post,in,k);          //递归构造左子树
	b->rchild = CreatBT2(post+k, p+1, n-k-1); //递归构造右子树
	return b;
}

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreatBTNode(b,str);
	printf("原二叉树已构造成二叉链，用括号表示法表示为：\n");
	DispBTNode(b); printf("\n\n");
	
	SqList pre, in, post;
	pre.size = in.size = post.size = 0;
	PreOrder(b,&pre); InOrder(b,&in); PostOrder(b,&post);  //建立遍历序列表
	printf("获得遍历序列:\n");
	printf("先序序列:"); DispList(&pre);                 //查看
	printf("中序序列:"); DispList(&in);
	printf("后序序列:"); DispList(&post);
	
	BTNode *t1, *t2;
	int n = pre.size;                    //记录大小(in.size, post.size亦等同)
	t1 = CreatBT1(pre.data,in.data,n); //重新构造二叉树
	t2 = CreatBT2(post.data,in.data,n);
	printf("根据先序和中序重构可得："); DispBTNode(t1); printf("\n");
	printf("根据后序和中序重构可得："); DispBTNode(t2); printf("\n");
	
	system("pause");
	return 0;
}