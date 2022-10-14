#include <stdio.h>
#include <stdlib.h>

/*********************************/
/*假设二叉树采用二叉链存储结构， *
 *设计一个算法输出从根节点到每个 *
 *叶子节点的逆路径。             */
/*********************************/

#define MaxSize 50
int count;  //路径计数
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

/*AllPath:返回从根节点到每个叶子节点的逆路径*/
void AllPath(BTNode *b)
{
	struct snode
	{
		BTNode *node;     //存放当前节点指针
		int parent;       //存放双亲节点在队列中的位置
	}qu[MaxSize];         //定义非环形队列
	BTNode *q;
	int front, rear, p;   //定义队头和队尾指针
	front = rear = -1;    //置队列尾空队列
	rear++;
	qu[rear].node = b;    //根节点指针进入队列
	qu[rear].parent = -1; //根节点没有双亲节点
	while(front != rear)      //队列不为空
	{
		front++;              //front是当前节点*q在qu中的位置
		q = qu[front].node;   //队头出队列，该节点指针仍在qu中
		if(q->lchild == NULL && q->rchild == NULL)//*q为叶子节点
		{//输出*q到根节点的逆路径序列
		    p = front;
			printf("第%d条路径为:",count++);
			while(qu[p].parent != -1)
			{
				printf("%c->",qu[p].node->data);
				p = qu[p].parent;
			}
			printf("%c\n",qu[p].node->data);
		}
		
		if(q->lchild != NULL)         //*q节点有左孩子时将其进队
		{
			rear++;
			qu[rear].node = q->lchild;
			qu[rear].parent = front;  //*q左孩子的双亲位置为front
		}
		if(q->rchild != NULL)         //*q节点有有孩子时将其进队
		{
			rear++;
			qu[rear].node = q->rchild;
			qu[rear].parent =front;   //*q右孩子的双亲位置为front
		}
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
	
	printf("打印从根节点到每个叶子节点的逆路径:\n");
	AllPath(b);
	
	system("pause");
	return 0;
}