#include <stdio.h>
#include <stdlib.h>

/****************/
/*先序线索二叉树*/
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

/*PreOrderThread:中序线索化二叉树*/
TBTNode* pre;     //全局变量
void PreOrderThread(TBTNode *&p)
{
	if(p != NULL)
	{
		if(p->lchild == NULL)               //前驱线索化
		{ p->lchild = pre; p->ltag = 1;}    //建立当前节点的前驱线索
		else p->ltag = 0;
		if(pre->rchild == NULL)             //后继线索化
		{ pre->rchild = p; pre->rtag = 1;}  //建立前驱节点的后继线索
		else pre->rtag = 0;
		pre = p;
		
		//不能用NULL判断，要用tag判断是否有左右孩子
		if(p->ltag != 1)
		    PreOrderThread(p->lchild);          //左子树线索化
		if(p->rtag != 1)
		    PreOrderThread(p->rchild);          //右子树线索化
	}//PS:这种写法是不健全的，保不定什么时候就出错了。。。
}

/*CreatPreOrderTBTNode:构造线索化二叉树*/
TBTNode *CreatPreOrderTBTNode(TBTNode *b)
{//有递归思想
    TBTNode *root;
	root = (TBTNode*)malloc(sizeof(TBTNode));  //创建头节点
	root->ltag = 0; root->rtag = 1; root->rchild = b;
	/*这种初始化方式为下方的算法服务*/
	if(b == NULL) root->lchild = root;         //空二叉树
	else
	{
		root->lchild = b;
		pre = root;           //pre是*p的前驱节点，供作线索用
		PreOrderThread(b);    //先序遍历线索化二叉树
		pre->rchild = root;   //最后处理，加入指向头节点的线索
		pre->rtag = 1;
		root->rchild = pre;   //头节点右线索化
		root->rtag = 1;
	}
	return root;
}

/*ThPreOrder:先序线索二叉树的先序遍历*/
void ThPreOrder(TBTNode *tb)
{
	TBTNode *p = tb->lchild;     //p指向根节点
	while(p != tb)               //线索二叉树不为空树
	{
		while(p->ltag == 0)
		{//一直往当前子树的左子树方向访问下去
			printf("%c",p->data);
			p = p->lchild;
		}
		printf("%c",p->data);    //访问最左边的节点
        p = p->rchild;           //访问右子树或者循着线索访问
	}
}


/*个人测试*/
/*Text:先序线索二叉树的先序遍历，逆序打印*/
/*结论：当前结构无法做到*/

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	TBTNode *b;
	CreatBTNode(b,str);
	printf("原二叉树已构造成二叉链，用括号表示法表示为：\n");
	DispBTNode(b); printf("\n\n");
	
	TBTNode *tb;
	tb = CreatPreOrderTBTNode(b);
	printf("先序线索化并先序遍历该线索二叉树为：");
	ThPreOrder(tb); printf("\n");
	
	system("pause");
	return 0;
}