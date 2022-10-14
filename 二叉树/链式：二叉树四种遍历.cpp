#include <stdio.h>
#include <stdlib.h>

/******************/
/*二叉树的四种遍历*/
/******************/

#define MaxSize 50
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild,*rchild;
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

/*PreOrder:先序遍历二叉树*/
void PreOrder(BTNode *b)
{//递归算法
	if(b != NULL)
	{
		printf("%c",b->data);  //访问根节点
		PreOrder(b->lchild);   //递归访问左子树
		PreOrder(b->rchild);   //递归访问右子树
	}
}

/*InOrder:中序遍历二叉树*/
void InOrder(BTNode *b)
{//递归算法
	if(b != NULL)
	{
		InOrder(b->lchild);   //递归访问左子树
		printf("%c",b->data);  //访问根节点
		InOrder(b->rchild);   //递归访问右子树
	}
}


/*PostOrder:后序遍历二叉树*/
void PostOrder(BTNode *b)
{//递归算法
	if(b != NULL)
	{
		PostOrder(b->lchild);   //递归访问左子树
		PostOrder(b->rchild);   //递归访问右子树
		printf("%c",b->data);  //访问根节点
	}
}

/*LevelOrder:层次遍历二叉树*/
void LevelOrder(BTNode *b)
{//借助队列工具
	BTNode *p;
	BTNode *qu[MaxSize];  //定义环形队列，存放节点指针
	int front, rear;       //定义对头和队尾指针
	front = rear = 0;     //置队列为空队列
	rear++;
	qu[rear] = b;         //根节点指针进入队列
	
	while(front != rear)  //队不空循环
	{
		front = (front+1)%MaxSize;
		p = qu[front];           //队头出队列
		printf("%c",p->data);    //访问节点
		if(p->lchild != NULL)    //有左孩子则左孩子进队
		{
			rear = (rear+1)%MaxSize;
			qu[rear] = p->lchild;
		}
		if(p->rchild != NULL)    //有右孩子时将其进队
		{
			rear = (rear+1)%MaxSize;
			qu[rear] = p->rchild;
		}
	}
}

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))";
	BTNode *b;
	CreatBTNode(b,str);
	printf("原二叉树已构造成二叉链，用括号表示法表示为：\n");
	DispBTNode(b); printf("\n\n");

	printf("现在对该二叉树进行四种形式的遍历\n");
	printf("先序："); PreOrder(b); printf("\n");
	printf("中序："); InOrder(b); printf("\n");
	printf("后序："); PostOrder(b); printf("\n");
	printf("层次："); LevelOrder(b); printf("\n");
	
	system("pause");
	return 0;
}