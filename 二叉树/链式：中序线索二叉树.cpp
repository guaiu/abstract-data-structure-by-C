#include <stdio.h>
#include <stdlib.h>

/****************/
/*中序线索二叉树*/
/****************/

#define MaxSize 30
typedef char ElemType;
typedef struct node
{
	ElemType data;       //节点数据域
	int ltag, rtag;      //增加的线索标记
	struct node *lchild; //左孩子或线索指针
	struct node *rchild; //右孩子或线索指针
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

/*InOrderThread:中序线索化二叉树*/
TBTNode *pre;   //全局变量
void InOrderThread(TBTNode *&p)
{
	if(p != NULL)
	{
		InOrderThread(p->lchild);         //左子树线索化
		if(p->lchild == NULL)             //前驱线索化
		{ p->lchild = pre; p->ltag = 1;}  //建立当前节点的前驱线索
		else p->ltag = 0;
		if(pre->rchild == NULL)           //后继线索化
		{ pre->rchild = p; pre->rtag = 1;}//建立前驱节点的后继线索
	    else pre->rtag = 0;
		pre = p;
		InOrderThread(p->rchild);         //递归调用右子树线索化
	}
}

/*CreatInOrderTBTNode:构造线索化二叉树*/
TBTNode *CreatInOrderTBTNode(TBTNode *b)
{
	TBTNode *root;
	root = (TBTNode*)malloc(sizeof(TBTNode));        //创建头节点
	root->ltag = 0; root->rtag = 1; root->rchild = b;
	/*这种初始化方式为下方的算法服务*/
	if(b == NULL) root->lchild = root;               //空二叉树
	else
	{
		root->lchild = b;
		pre = root;            //pre是*p的前驱节点，供作线索用
		InOrderThread(b);      //中序遍历线索化二叉树
		pre->rchild = root;    //最后处理，加入指向头节点的线索
		pre->rtag = 1;
		root->rchild = pre;    //头节点右线索化
		root->rtag = 1;
	}
	return root;
}

/*ThInOrder:中序线索二叉树的中序遍历*/
void ThInOrder(TBTNode *tb)
{//有递归思想
	TBTNode *p = tb->lchild;   //p指向根节点
	while(p != tb)             //线索二叉树不为空树
	{
		while(p->ltag == 0) p = p->lchild;  //找当前子树开始节点
		printf("%c",p->data);               //访问当前子树开始节点
		while(p->rtag == 1 && p->rchild != tb)
		{//如果是线索就一直访问下去
			p = p->rchild;
			printf("%c",p->data);
		}
		p = p->rchild;         //访问当前子树根节点的右子树
	}
}

/*个人测试*/
/*Text:中序线索二叉树的中序遍历，逆序打印*/
void Text(TBTNode *tb)
{//归根到底运用了递归思想
	TBTNode *p = tb->rchild;   //p指向根节点
	if(p == NULL)
		return ;               //空树退出
	while(p != tb)
	{
	    while(p->rtag == 0) p = p->rchild;   //找当前子树开始节点
		printf("%c",p->data);                //访问当前子树开始节点
	    while(p->ltag == 1 && p->lchild != tb)
		{//顺着线索访问下去
			p = p->lchild;
			printf("%c",p->data);
		}
		p = p->lchild;        //访问当前子树根节点的左子树
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
	tb = CreatInOrderTBTNode(b);
	printf("中序线索化并中序遍历该线索二叉树为：");
	ThInOrder(tb);
	
	printf("\n测试；逆序打印中序线索二叉树：");
	Text(tb); printf("\n");
	
	system("pause");
	return 0;
}