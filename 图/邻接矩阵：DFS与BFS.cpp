#include <stdio.h>
#include <stdlib.h>

/******************/
/*邻接矩阵DFS和BFS*/
/******************/

#define MAX_VEX_NUM 10
#define MAX_ARC_NUM MAX_VEX_NUM*MAX_VEX_NUM
typedef enum
{
	DG, DN, UDG, UDN  //分别为有向图、有向网、无向图、无向网
}GraphType;
typedef char VexType;
typedef struct
{
	VexType vexs[MAX_VEX_NUM];       //顶点信息。规定MAX_VEX_NUM-1位置不使用。
	int arcs[MAX_VEX_NUM][MAX_VEX_NUM]; //邻接矩阵
	int vexnum, arcnum;                 //图的顶点数和弧数
	GraphType type;                     //图的种类标志
}MGraph;

//顶点集合和边集合类型
typedef VexType VexGroup;
typedef struct
{
	VexType orinvex,adjvex;
	int weight;
}ArcGroup;

/*GetIndexOfVexs:根据名称得到指定顶点在顶点集合中的下标*/
/*注:为了健全性考虑下标MAX_VEX_NUM-1位置不使用，仅用于查找不到目标顶
点时作返回值*/
int GetIndexOfVexs(char vex, MGraph *MG)
{
	int i;
	for(i = 0; i < MG->vexnum; i++)
	{
		if(MG->vexs[i] == vex)
			return i;
			
	}
	return MAX_VEX_NUM;
}

/*CreateMGraph:根据顶点集合和边集合构建邻接矩阵*/
MGraph *CreateMGraph(VexGroup vexs[], ArcGroup arcs[], GraphType type, int vexnum, int arcnum)
{
	int i,j;
	int v1, v2;
	int weight;
	MGraph *G;                               //创建图指针
	G = (MGraph*)malloc(sizeof(MGraph));    //分配内存空间
	G->type = type;                           //开始创建
	G->vexnum = vexnum;
	G->arcnum = arcnum;
	//邻接矩阵初始化
	if(type == DN || type == UDN){//网类型
		for(i = 0; i < G->vexnum; i++)
			for(j = 0; j < G->vexnum; j++)
			{
				if(i != j)
					G->arcs[i][j] = -1;  //其他情况初始化为-1
				else
					G->arcs[i][j] = 0;   //本身初始化为0
			}
	}
	else{//图类型
		for(i = 0; i < G->vexnum; i++)
			for(j = 0; j < G->vexnum; j++)
				G->arcs[i][j] = 0;  //其他情况和本身初始化为0
	}
	for(i = 0; i < vexnum; i++){//处理顶点
		G->vexs[i] = vexs[i];
	}
	
	for(i = 0; i < arcnum; i++){//处理边
	    v1 = GetIndexOfVexs(arcs[i].orinvex,G);
		v2 = GetIndexOfVexs(arcs[i].adjvex,G);
	    if(type == DN || type == UDN)
		{//网类型
			weight = arcs[i].weight;
		}
		else{//图类型
			weight = 1;
		}
		G->arcs[v1][v2] = weight;
		if(type == UDG || type == UDN)
		{//如果是无向图或无向网
			G->arcs[v2][v1] = weight;
		}
	}
	return G;
}

/*DispMGraph:打印邻接矩阵和顶点信息*/
void DispMGraph(MGraph *MG)
{
	int i, j;
	if(MG == NULL)
		return ;
	switch(MG->type)
	{
		case 0: printf("Graph type: Direct graph\n"); break;
		case 1: printf("Graph type: Direct net\n"); break;
		case 2: printf("Graph type: Undirect graph\n"); break;
		case 3: printf("Graph type: Undirect net\n"); break;
	}
	printf("Graph vertex number: %d\n",MG->vexnum);
	printf("Graph arc number: %d\n",MG->arcnum);
	printf("Vertex set:");
	for(i = 0; i < MG->vexnum; i++)
	{
		printf("%c",MG->vexs[i]);
	}
	printf("\nAdjacency Matrix:\n");
	for(i = 0; i < MG->vexnum; i++)
	{
		for(j = 0; j < MG->vexnum; j++)
		{
			printf("\t%2d",MG->arcs[i][j]);
		}
		printf("\n");
	}
}

/*MDFS:邻接矩阵的深度遍历*/
int visited[MAX_VEX_NUM];   //全局变量，所有元素置初值为0
void MDFS(MGraph *G, int v)
{
	int w;
	printf("%c ",G->vexs[v]);  //访问顶点v
	visited[v] = 1;            //标记已访问
	for(w = 0; w < G->vexnum; w++)
		if(G->arcs[v][w] != 0 && G->arcs[v][w] != -1 && visited[w] == 0)
			MDFS(G,w);         //递归遍历
}

/*MBFS:邻接矩阵的深度遍历*/
void MBFS(MGraph *G, int v)
{//v为起点编号
    int i,w;
    int queue[MAX_VEX_NUM], front = 0, rear = 0;  //定义队列
    int visited[MAX_VEX_NUM];                     //定义标记数组	
    for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;
	printf("%c ",G->vexs[v]);   //打印首顶点信息
	visited[v] = 1;             //标记
	rear++;
	queue[rear] = v;            //入队
	while(front != rear)        //队不空循环
	{
		front++;
		w = queue[front];       //出队
		for(i = 0; i < G->vexnum; i++)
			if(G->arcs[w][i] != 0 && G->arcs[w][i] != -1 && visited[i] == 0)
			{//访问之
				printf("%c ",G->vexs[i]);
				visited[i] = 1;  //标记
				rear++;
				queue[rear] = i; //进队
			}
	}
}

/*主函数*/
int main()
{
	int i;
	VexGroup vg[MAX_VEX_NUM] = "ABCDE";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',1},{'B','C',1},
	{'C','D',3},{'D','A',2},{'C','E',1},{'E','D',1}};
	int vexnum = 5, arcnum = 6;
	
	MGraph *G1;
	G1 = CreateMGraph(vg,ag,UDG,vexnum,arcnum);
	printf("G1:\n"); DispMGraph(G1); printf("\n");
	
	for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;  //标记数组初始化
	
	printf("DFS:");
	MDFS(G1,0); printf("\n");
	printf("BFS:");
	MBFS(G1,0); printf("\n");
	
	system("pause");
	return 0;
}