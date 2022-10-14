#include <stdio.h>
#include <stdlib.h>

/**************************************/
/*二叉树链式存储结构与顺序存储结构转换*/
/**************************************/

#define MaxSize 30
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild, *rchild;
}BTNode;

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

/*DispSqBTree:按原格式输出顺序二叉树*/
void DispBTree(ElemType *b, int p)  //p为当前查看元素地址
{//输出示例：A(B(D(,G)),C(E,F))
	if(b[p] != '#')
	{
		printf("%c",b[p]);
		if(b[p*2] != '#' || b[p*2+1] != '#')
		{
			printf("(");
			DispBTree(b, p*2);  //递归处理左子树
			if(b[p*2+1] != '#') printf(",");
			DispBTree(b,p*2+1);  //递归处理右子树
			printf(")");
		}
	}
}

/*trans1:顺序转链式*/
BTNode *trans1(ElemType *SqBTree, int i)
{
	BTNode *b;
	if(i > MaxSize) return NULL;
	if(SqBTree[i] == '#') return NULL;    //节点不存在时返回NULL
	b = (BTNode*)malloc(sizeof(BTNode));  //创建节点
	b->data = SqBTree[i];
	b->lchild = trans1(SqBTree, 2*i);     //递归创建左子树
	b->rchild = trans1(SqBTree, 2*i+1);   //递归创建右子树
	return b;
}

/*trans2:链式转顺序*/
void trans2(BTNode *b, ElemType *SqBTree, int i)
{
	if(b != NULL)
	{
		SqBTree[i] = b->data;             //创建根节点
		trans2(b->lchild, SqBTree, 2*i);  //递归创建右子树
		trans2(b->rchild,SqBTree, 2*i+1); //递归创建右子树
	}
	else
		SqBTree[i] = '#';                 //空
}

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreatBTNode(b,str);
	printf("原二叉树已构造成二叉链，用括号表示法表示为：\n");
	DispBTNode(b); printf("\n\n");
	
	ElemType SqBTree[MaxSize];  //规定不使用位置下标0
	SqBTree[1] = '#';           //根节点置空
	trans2(b,SqBTree,1);
	printf("链式转顺序，根据顺序存储还原的二叉树为：\n");
	DispBTree(SqBTree,1); printf("\n");
	
	BTNode *t;
	t = trans1(SqBTree, 1);
	printf("顺序转链式，根据链式存储还原的二叉树为:\n");
	DispBTNode(t); printf("\n");
	
	system("pause");
	return 0;
}