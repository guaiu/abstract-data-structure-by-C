#include <stdio.h>
#include <stdlib.h>

/***************************************/
/*拓扑排序(仅输出一种可能,且不考率回路)*/
/***************************************/

/*注：使用下标位置0，不使用下标位置MAX_VEX_NUM-1*/
/*注：本算法对于邻接表的构建和基本操作有所修改*/

#define MAX_VEX_NUM 10
#define MAX_ARC_NUM 10
typedef char VexType;
typedef enum
{
	DG, DN, UDG, UDN  //分别为有向图、有向网、无向图、无向网
}GraphType;

typedef struct ANode
{
	int adjvex;            //该边的终点编号
	struct ANode *nextarc; //指向下一条边的指针
	int weight;            //权重(或其他信息，这里为了简便只记录权重)
}ArcNode;

typedef struct
{
	VexType data;         //顶点信息
	int count;            //存放顶点入度
	ArcNode *firstarc;    //指向第一条边
}VexNode;//拓扑排序专用

typedef struct
{
	VexNode adjlist[MAX_VEX_NUM];  //邻接表
	int vexnum, arcnum;            //定点数与边数
	GraphType type;                //邻接表类型。对特定构造的邻接表没有意义。
}ALGraph;

//顶点集合和边集合类型
typedef VexType VexGroup;
typedef struct
{
	VexType orinvex,adjvex;
	int weight;
}ArcGroup;

/*GetIndexOfAdjlist:根据名称得到指定顶点在顶点集合中的下标*/
/*注:为了健全性考虑下标MAX_VEX_NUM-1位置不使用，仅用于查找不到目标顶
点时作返回值*/
int GetIndexOfAdjlist(char vex, ALGraph *G)
{
	int i;
	for(i = 0; i < G->vexnum; i++)
	{
		if(G->adjlist[i].data == vex)
			return i;
			
	}
	return MAX_VEX_NUM;
}

/*DispALGraph:打印邻接表和顶点信息*/
void DispALGraph(ALGraph *G)
{
	int i;
	ArcNode *p;
	if(G == NULL)
		return ;
	switch(G->type)
	{
		case 0: printf("Graph type: Direct graph\n"); break;
		case 1: printf("Graph type: Direct net\n"); break;
		case 2: printf("Graph type: Undirect graph\n"); break;
		case 3: printf("Graph type: Undirect net\n"); break;
	}
	printf("Graph vertex number: %d\n",G->vexnum);
	printf("Graph arc number: %d\n",G->arcnum);
	printf("Vertex set:");
	for(i = 0; i < G->vexnum; i++){
		printf("%c",G->adjlist[i].data);
	}
	printf("\nAdjacency List:\n");
	for(i = 0; i < G->vexnum; i++)
	{
		printf("%c(vex)",G->adjlist[i].data);
		p = G->adjlist[i].firstarc;
		while(p != NULL)
		{
		    if(G->type == DN || G->type == UDN)
			    printf("-(%d)->%c",p->weight,G->adjlist[p->adjvex].data);
			else
				printf("-->%c",G->adjlist[p->adjvex].data);
			p = p->nextarc;
		}
		printf("\n");
		if(G->type == DN || G->type == DG)
			printf("附:该顶点入度为%d\n",G->adjlist[i].count);
	}
}

/*CreateALGraph:根据顶点集合和边集合构建邻接表*/
ALGraph *CreateALGraph(VexGroup vexs[], ArcGroup arcs[], GraphType type, int vexnum, int arcnum)
{
	int i;
	int v1, v2;
	ArcNode *q;
	ALGraph *G;                               //创建图指针
	G = (ALGraph*)malloc(sizeof(ALGraph));    //分配内存空间
	G->type = type;                           //开始创建
	G->vexnum = vexnum;
	G->arcnum = arcnum;
	for(i = 0; i < vexnum; i++){//顶点
		G->adjlist[i].data = vexs[i];
		G->adjlist[i].firstarc = NULL;
		G->adjlist[i].count = 0;
	}
	G->adjlist[MAX_VEX_NUM-1].firstarc = NULL; //不使用位置空
	G->adjlist[MAX_VEX_NUM-1].data = '#';
	
	for(i = 0; i < arcnum; i++){//边
	    v1 = GetIndexOfAdjlist(arcs[i].orinvex, G);
		v2 = GetIndexOfAdjlist(arcs[i].adjvex, G);
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = v2;
		q->nextarc = G->adjlist[v1].firstarc;
		G->adjlist[v1].firstarc = q;
		q->weight = arcs[i].weight;
		G->adjlist[v2].count++;//入度
		if(type == UDG || type == UDN)
		{//如果是无向图或无向网
			q = (ArcNode*)malloc(sizeof(ArcNode));
		    q->adjvex = v1;
		    q->nextarc = G->adjlist[v2].firstarc;
		    G->adjlist[v2].firstarc = q;
		    q->weight = arcs[i].weight;
		}
	}
	return G;
}

/*TopSort:拓扑排序算法*/
void TopSort(VexNode adjlist[], int vexnum)
{
	int i, j;
	int St[MAX_VEX_NUM], top = -1; //辅助栈
	ArcNode *p;
	for(i = 0; i < vexnum; i++)
		if(adjlist[i].count == 0)  //入度为0的顶点入栈
		{
			top++;
			St[top] = i;
		}
	printf("拓扑排序");
	while(top > -1)  //栈不为空循环
	{
		i = St[top]; //出栈
		top--;
		printf("%c ",adjlist[i].data);
		p = adjlist[i].firstarc;
		while(p != NULL)
		{
			j = p->adjvex;
			adjlist[j].count--;
			if(adjlist[j].count == 0)
			{
				top++;
				St[top] = j;
			}
			p = p->nextarc;  //找下一个相邻点
		}	
	}
	printf("\n");
}

/*主函数*/
int main()
{
	VexGroup vg[MAX_VEX_NUM] = "1234567";
	ArcGroup ag[MAX_ARC_NUM] = {{'1','3',1},{'3','4',1},
	{'2','4',1},{'2','7',1},{'2','5',1},{'7','6',1},
	{'4','6',1},{'4','5',1}};
	int vexnum = 7, arcnum = 8;
	
	ALGraph *G1;
	G1 = CreateALGraph(vg,ag,DG,vexnum,arcnum);
	printf("G1:\n"); DispALGraph(G1); printf("\n");

    TopSort(G1->adjlist, G1->vexnum);
	
	system("pause");
	return 0;
}
