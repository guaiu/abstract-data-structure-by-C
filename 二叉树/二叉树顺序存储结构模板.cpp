#include <stdio.h>
#include <stdlib.h>

/********************/
/*二叉树顺序存储结构*/
/********************/

#define MaxSize 100
typedef char ElemType;
typedef struct
{
	ElemType data[MaxSize];
	//规定根节点为下标为1，0处元素设为'\0'
}BTNode;

/*CreateBTNode:顺序创建二叉树*/
void CreateBTNode(BTNode *&b, ElemType *str)
{//输入示例：A(B(D(,G)),C(E,F))
    int St[MaxSize], p = 1;           //St为指针栈，p为当前扫描元素指针，初始值为1
	int top = -1, j = 0;              //j用于遍历字符串
	ElemType ch;
	b = (BTNode*)malloc(sizeof(BTNode));
	b->data[1] = '#'; 
	b->data[0] = '\0';  //初始化
	ch = str[j];
	while(ch != '\0'){                 //循环扫描
		switch(ch)
		{
			case'(': top++; St[top] = p; p *= 2; break;   //可能有左孩子，进栈，p指向左孩子
			case')': p = St[top]; top--; break;           //处理完栈顶元素可能的左右孩子，退栈，p指针回退
			case',': p++; break;                          //p指向右孩子
			default:{//遇到节点值
			    b->data[p*2] = '#';        //p元素左孩子置空
				b->data[p*2+1] = '#';      //p元素右孩子置空
			    b->data[p] = ch;           //p元素接收ch的值
			}
		}
		j++; ch = str[j];    //继续扫描str
	}
}

/*DestroyBT:销毁二叉链*/
void DestroyBT(BTNode *&b)
{
	free(b);
}

/*FindNode:查找节点地址*/
int FindNode(BTNode *b, ElemType x, int p)  //p为当前查看元素地址
{
	int k;
	if(b->data[p] == '#')
		return 0;
	else if(b->data[p] == x)
		return p;
	else
	{
		k = FindNode(b,x,p*2);  //先从左子树找
		if(k != 0)                      //找到了
			return k;
		else                            //再从右子树找
			return FindNode(b,x,p*2+1);
	}
}

/*LchildNode:返回左孩子地址*/
int LchildNode(int p)
{return p*2;}

/*RchildNode:返回左孩子地址*/
int RchildNode(int p)
{return p*2+1;}

/*BTNodeDepth:求二叉树高度*/
int BTNodeDepth(BTNode *b,int p)  //p为当前查看元素地址
{
	int lchilddep, rchilddep;
	if(b->data[p] == '#') return 0;  //空树高度为0
	else
	{
		lchilddep = BTNodeDepth(b,p*2);
		                        //求左子树高度
		rchilddep = BTNodeDepth(b,p*2+1);
		                        //求右子树高度
		return (lchilddep > rchilddep)?(lchilddep+1):(rchilddep+1);
		                        //返回最大子树高度+1
	}
}

/*DispBTNode:输出二叉树*/
void DispBTNode(BTNode *b, int p)  //p为当前查看元素地址
{//输出示例：A(B(D(,G)),C(E,F))
	if(b->data[p] != '#')
	{
		printf("%c",b->data[p]);
		if(b->data[p*2] != '#' || b->data[p*2+1] != '#')
		{
			printf("(");
			DispBTNode(b, p*2);  //递归处理左子树
			if(b->data[p*2+1] != '#') printf(",");
			DispBTNode(b,p*2+1);  //递归处理右子树
			printf(")");
		}
	}
}

/*测试主函数*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))" , x;
	BTNode *b;
	int p,a;
	CreateBTNode(b,str);
	
	printf("创建一个高度为%d的二叉树\n",BTNodeDepth(b,1));
	printf("可依据该二叉树打印原字符串为：\n");
	DispBTNode(b,1);
	printf("\n");
	
	printf("输入元素x\n");
	for(int i = 0; i < 8; i++){
	scanf("%c",&x);
	getchar();
	if((p = FindNode(b,x,1)) != 0)
	{
	    printf("元素%c的左右孩子是：\n",x);
	    if((a = LchildNode(p)) != 0)
		    printf("左：%c\n",b->data[a]);
	    else
		    printf("左孩子为空\n");
	    if((a = RchildNode(p)) != 0)
		    printf("右：%c\n",b->data[a]);
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