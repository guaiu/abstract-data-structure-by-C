#include <stdio.h>
#include <stdlib.h>

/***************************************/
/*假设二叉树采用二叉链存储结构，设计一 *
 *个算法把二叉树b左右子树逆置，并讲将新*
 *生成子树放置于t中                    */
/***************************************/

#define MaxSize 50
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild,*rchild;
}BTNode;

/*CreateBTNode:创建二叉链*/
void CreateBTNode(BTNode *&b, char *str)
{//输入示例：A(B(D(,G)),C(E,F))
	BTNode *St[MaxSize], *p;   //St为指针栈
	int top = -1, k, j = 0;    //k用于标识状态，j用于遍历字符串
	char ch;
	b = NULL;                  //二叉链初始时为空
	ch = str[j];
	while(ch != '\0')          //循环扫描
	{
		switch(ch)
		{
			case'(': top++; St[top] = p; k = 1; break;   //可能有左孩子，进栈
			case')': top--; break;                       //处理完栈顶元素可能的左右孩子，退栈
			case',': k = 2; break;
			default:{//遇到节点值
			    p = (BTNode*)malloc(sizeof(BTNode));
				p->data = ch; p->lchild = p->rchild = NULL;
				if(b == NULL)     //p为二叉树根节点
				    b = p;
			    else{             //已建立二叉树根节点
					switch(k)     //扫描当前状态标识量k
					{
						case 1: St[top]->lchild = p; break;
						case 2: St[top]->rchild = p; break;
					}
				}
			}
		}
		j++; ch = str[j];    //继续扫描str
	}
}

/*DispBTNode:输出二叉树*/
void DispBTNode(BTNode *b)
{//输出示例：A(B(D(,G)),C(E,F))
	if(b != NULL)
	{
		printf("%c",b->data);
		if(b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTNode(b->lchild);  //递归处理左子树
			if(b->rchild != NULL) printf(",");
			DispBTNode(b->rchild);  //递归处理右子树
			printf(")");
		}
	}
}

/*Swap:逆置二叉树*/
void Swap(BTNode *b, BTNode *&t)
{
	if(b == NULL) t = NULL;
	else
	{
		t = (BTNode*)malloc(sizeof(BTNode));
		t->data = b->data;           //复制一个根节点*t
		Swap(b->lchild, t->rchild);  //递归交换左子树
		Swap(b->rchild, t->lchild);  //递归交换右子树
	}
}

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreateBTNode(b,str);
	printf("原二叉树已构造成二叉链，用括号表示法表示为：\n");
	DispBTNode(b); printf("\n\n");
	
	printf("左右子树互换后有一个二叉树t\n");
	BTNode *t;
	Swap(b,t);
	
	printf("t构造完毕，用括号表示法表示为：\n");
	DispBTNode(t); printf("\n\n");
	
	system("pause");
	return 0;
}