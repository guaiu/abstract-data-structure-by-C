#include <stdio.h>
#include <stdlib.h>

/********************/
/*二叉树链式存储结构*/
/********************/

#define MaxSize 50
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild, *rchild;
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

/*DestroyBT:销毁二叉链*/
void DestroyBT(BTNode *&b)
{
	if(b == NULL)
		return ;
	else
	{
		DestroyBT(b->lchild);
		DestroyBT(b->rchild);
		free(b);    //剩下一个节点*b，直接释放
	}
}

/*FindNode:查找节点地址*/
BTNode *FindNode(BTNode *b, ElemType x)
{
	BTNode *p;
	if(b == NULL)
		return NULL;
	else if(b->data == x)
		return b;
	else
	{
		p = FindNode(b->lchild,x);  //先从左子树找
		if(p != NULL)               //找到了
			return p;
		else                        //再从右子树找
			return FindNode(b->rchild,x);
	}
}

/*LchildNode:返回左孩子节点*/
BTNode *LchildNode(BTNode *p)
{return p->lchild;}

/*RchildNode:返回右孩子节点*/
BTNode *RchildNode(BTNode *p)
{return p->rchild;}

/*BTNodeDepth:求二叉树高度*/
int BTNodeDepth(BTNode *b)
{
	int lchilddep, rchilddep;
	if(b == NULL) return 0;  //空树高度为0
	else
	{
		lchilddep = BTNodeDepth(b->lchild);
		                        //求左子树高度
		rchilddep = BTNodeDepth(b->rchild);
		                        //求右子树高度
		return (lchilddep > rchilddep)?(lchilddep+1):(rchilddep+1);
		                        //返回最大子树高度+1
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

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))" , x;
	BTNode *b, *p, *a;
	CreateBTNode(b,str);
	
	printf("创建一个高度为%d的二叉树\n",BTNodeDepth(b));
	printf("可依据该二叉树打印原字符串为：\n");
	DispBTNode(b);
	printf("\n");
	
	printf("输入元素x\n");
	for(int i = 0; i < 8; i++){
	scanf("%c",&x);
	getchar();
	if((p = FindNode(b,x)) != NULL)
	{
	    printf("元素%c的左右孩子是：\n",x);
	    if((a = LchildNode(p)) != NULL)
		    printf("左：%c\n",a->data);
	    else
		    printf("左孩子为空\n");
	    if((a = RchildNode(p)) != NULL)
		    printf("右：%c\n",a->data);
	    else
		    printf("右孩子为空\n");
	}
	else
		printf("不存在该元素\n");
    }
	
	
	DestroyBT(b);
	system("pause");
	return 0;
}