#include <stdio.h>
#include <stdlib.h>

/***********************************/
/*广度遍历算法的应用:求最远距离顶点*/
/***********************************/

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
	ArcNode *firstarc;    //指向第一条边
}VexNode;

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

typedef struct
{
	int data;   //顶点编号
	int parent; //前一个顶点的位置
}QUERE;  //非循环队列类型

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

/*BFS:邻接表的广度遍历算法*/
void BFS(ALGraph *G, int v)
{//v为起点编号
	ArcNode *p;
	int w, i;
	int queue[MAX_VEX_NUM], front = 0, rear = 0;  //定义队列
	int visited[MAX_VEX_NUM];                     //标记数组，广度遍历不需要全局数组
    for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;
	printf("%c ",G->adjlist[v].data);             //打印首顶点信息
	visited[v] = 1;
	rear++;
	queue[rear] = v;
	while(front != rear)  //队列不为空时循环
	{
		front++;
		w = queue[front];            //出队 
		p = G->adjlist[w].firstarc;  //找w的第一个邻接点
		while(p != NULL)
		{
			if(visited[p->adjvex] == 0)
			{
				printf("%c ",G->adjlist[p->adjvex].data);  //访问之
				visited[p->adjvex] = 1;
				rear++;                                    //相邻顶点进队
				queue[rear] = p->adjvex;
			}
			p = p->nextarc;                                //找下一个邻接节点
		}
	} 
}

/*Maxdist:求无向连通图G中离顶点v最远的一个顶点*/
int Maxdist(ALGraph *G, int v)
{
	ArcNode *p;
	int Qu[MAX_VEX_NUM], front = 0, rear = 0;  //队列及队头、队尾指针
	int visited[MAX_VEX_NUM], i, j, k;
	for(i = 0; i < G->vexnum; i++)
		visited[i] = 0;
	rear++; Qu[rear] = v;       //顶点v进队
	visited[v] = 1;             //标记v已访问
	while(rear != front)        //队不空循环
	{
		front++;
		k = Qu[front];               //顶点出队
		p = G->adjlist[k].firstarc;  //找第一个邻接点
		while(p != NULL)             //依次访问
		{
			j = p->adjvex;
			if(visited[j] == 0)      //若j未访问
			{
				visited[j] = 1;      //j进队
				rear++;
				Qu[rear] = j;
			}
			p = p->nextarc;             //找下一个邻接点
		}
	}
	return k;
}

/*主函数*/
int main()
{
	//初始化并测试
	VexGroup vg[MAX_VEX_NUM] = "ABCDEF";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',1},{'A','C',1},
	{'B','D',1},{'B','F',1},{'F','E',1}};
	int vexnum = 6, arcnum = 5;
	ALGraph *G1;
	G1 = CreateALGraph(vg,ag,UDG,vexnum,arcnum);
	printf("G1:\n"); DispALGraph(G1); printf("\n");
	printf("BFS:"); BFS(G1,0); printf("\n");
	
	printf("离A最远的点是%c\n",G1->adjlist[Maxdist(G1,0)].data);
	
	system("pause");
	return 0;
}