#include <stdio.h>
#include <stdlib.h>

/****************/
/*后序线索二叉树*/
/****************/

#define MaxSize 30
typedef char ElemType;
typedef struct node
{
	ElemType data;       //节点数据域
	int ltag, rtag;      //增加的线索标记
	struct node *lchild; //左孩子或线索指针
	struct node *rchild; //右孩子或线索指针
	struct node *parent; //双亲节点
}TBTNode;                //线索树节点类型定义


/*CreatBTNode:创建二叉链(未线索化)*/
void CreatBTNode(TBTNode *&b, char *str)
{//输入示例：A(B(D(,G)),C(E,F))
	TBTNode *St[MaxSize], *p;
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
				p = (TBTNode*)malloc(sizeof(TBTNode));
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

/*DispBTNode:按照原形式输出二叉树(未线索化)*/
void DispBTNode(TBTNode *b)
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

/*InitParent:双亲指针初始化*/
void InitParent(TBTNode *&b)
{
	if(b != NULL)
	{
		if(b->lchild != NULL)
			b->lchild->parent = b;
		if(b->rchild != NULL)
			b->rchild->parent = b;
		InitParent(b->lchild);
		InitParent(b->rchild);
	}
}

/*PostOrderThread:后序线索化二叉树*/
TBTNode* pre;     //全局变量
void PostOrderThread(TBTNode *&p)
{
	if(p != NULL)
	{
		PostOrderThread(p->lchild);         //左子树线索化
		PostOrderThread(p->rchild);         //右子树线索化
		
		if(p->lchild == NULL)               //前驱线索化
		{ p->lchild = pre; p->ltag = 1;}    //建立当前节点的前驱线索
		else p->ltag = 0;
		if(pre->rchild == NULL)             //后继线索化
		{ pre->rchild = p; pre->rtag = 1;}  //建立前驱节点的后继线索
		else pre->rtag = 0;
		pre = p;
	}
}

/*CreatPostOrderTBTNode:构造线索化二叉树*/
TBTNode *CreatPostOrderTBTNode(TBTNode *b)
{//有递归思想
    TBTNode *root;
	root = (TBTNode*)malloc(sizeof(TBTNode));  //创建头节点
	root->ltag = 0; root->rtag = 1; root->rchild = b;
	/*这种初始化方式为下方的算法服务*/
	if(b == NULL) root->lchild = root;         //空二叉树
	else
	{
		b->parent = root;
		InitParent(b);        //初始化双亲指针
		root->lchild = b;
		pre = root;           //pre是*p的前驱节点，供作线索用
		PostOrderThread(b);    //先序遍历线索化二叉树
		root->rchild = pre;   //头节点右线索化
		root->rtag = 1;
		if(b->rchild == NULL) //根节点无右子树
		{
			b->rchild = root;
			b->rtag = 1;
		}
		else                  //根节点有右子树
			b->rtag = 0;
	}
	return root;
}

/*ThPostOrder:后序线索二叉树的后序遍历*/
void ThPostOrder(TBTNode *tb)
{
	TBTNode *pre = tb, *p = tb->lchild;    //p指向当前节点，pre用作记录上一遍历节点
	while(p != tb)
	{
		while(p->ltag == 0 && p->lchild != pre)  //找到当前子树最左节点
	        p = p->lchild;
		while(p->rtag == 1 && p != tb)           //循着线索访问下去
		{
			printf("%c",p->data);
			pre = p;
			p = p->rchild;
		}
		while(p->rchild == pre && p != tb)
		{//当前节点的右节点为上一次遍历节点
	        printf("%c",p->data);
			pre = p;
			p = p->parent;                 //往上一级走
		}
		if(p != tb && p->rtag == 0)
			p = p->rchild;                 //走向当前节点右子树
	}
}

/*个人测试*/
/*Text:后序线索二叉树的后序遍历，逆序打印*/
void Text(TBTNode *tb)
{
	TBTNode *p = tb->lchild;
	while(p != tb)
	{
		while(p->rtag == 0)
		{//沿着右边访问下去
			printf("%c",p->data);
			p = p->rchild;
		}
		printf("%c",p->data);  //访问最右边的节点
		while(p->ltag == 1 && p->lchild != tb)
		{//沿着左线索访问下去
			p = p->lchild;
			printf("%c",p->data);
		}
		p = p->lchild;         //访问左子树(此时必为当前子树根节点)
	}
}

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	TBTNode *b;
	CreatBTNode(b,str);
	printf("原二叉树已构造成二叉链，用括号表示法表示为：\n");
	DispBTNode(b); printf("\n\n");
	
	TBTNode *tb;
	tb = CreatPostOrderTBTNode(b);
	printf("后序线索化并后序遍历该线索二叉树为：");
	ThPostOrder(tb); printf("\n");
	
	printf("\n测试；逆序打印后序线索二叉树：");
	Text(tb); printf("\n");
	
	system("pause");
	return 0;
}