#include <stdio.h>
#include <stdlib.h>

/****************************/
/*最短路径问题的Dijkstra算法*/
/****************************/

#define INF 32767
#define MAX_VEX_NUM 10
#define MAX_ARC_NUM MAX_VEX_NUM*MAX_VEX_NUM
typedef enum
{
	DG, DN, UDG, UDN  //分别为有向图、有向网、无向图、无向网
}GraphType;
typedef char VexType;
typedef struct
{
	VexType vexs[MAX_VEX_NUM];          //顶点信息。规定MAX_VEX_NUM-1位置不使用。
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
					G->arcs[i][j] = INF;  //其他情况初始化为INF
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
			if(MG->arcs[i][j] == INF)
				printf("\t∞");
			else
			    printf("\t%2d",MG->arcs[i][j]);
		}
		printf("\n");
	}
}

/*DispPath:根据参数打印最短v到各顶点的最短路径*/
void DispPath(MGraph *G,int dist[], int path[], int s[], int v)
{
	int i;
	int u;
	int stack[MAX_VEX_NUM];
	int top = -1; //辅助栈
	for(i = 0; i < G->vexnum; i++)
	{
		if(s[i] == 0)
		    printf("%c到%c没有最短路径, 路径长度为∞\n",G->vexs[v],G->vexs[i]);
		else//s[i] == 1
		{
			u = path[i];
			top++;
		    stack[top] = u;
			while(stack[top] != v)
			{
				u = path[stack[top]];
				top++;
				stack[top] = u;
			}
			printf("%c到%c的最短路径为",G->vexs[v],G->vexs[i]);
			while(top > -1)
			{
				printf("%c->",G->vexs[stack[top]]);
				top--;
			}
			printf("%c",G->vexs[i]);
			printf(", 路径长度为%d\n",dist[i]);
		}
	}
}

/*Dijkstra:最短路径问题的狄克斯特拉算法*/
void Dijkstra(MGraph *G, int v)//v为起始点的下标
{//设集合S与集合U，初始时S集合中仅有v，U集合有其他各顶点
	int dist[MAX_VEX_NUM];
	//记录最短路径长度
	int path[MAX_VEX_NUM]; 
	//记录最短路径,path[k]的值表示顶点v到顶点k的最短路径中顶点k的前一个顶点
	int s[MAX_VEX_NUM];    
	//标记各顶点是否在集合S中
	int mindis,u;
	int i,j;
	for(i = 0; i < G->vexnum; i++)
	{
		dist[i] = G->arcs[v][i];  //dist数组初始化，
		s[i] = 0;                 //s[]置空
		if(G->arcs[v][i] < INF)   //路径初始化
		    path[i] = v;
		else
			path[i] = -1;
	}
	s[v] = 1;                     //原点v放入S中
	for(i = 0; i < G->vexnum; i++)
	{
		mindis = INF;
		u = v; //初始化为v.
		for(j = 0; j < G->vexnum; j++)
			if(s[j] == 0 && dist[j] < mindis) 
			{//找当前U集合到S集合的最小路径长度顶点u
				u = j;
				mindis = dist[j];
			}
		s[u] = 1;                      //顶点u加入S
		for(j = 0; j < G->vexnum; j++) //根据新集合S进行调整
			if(s[j] == 0)
				if(G->arcs[u][j] < INF && dist[u]+G->arcs[u][j] < dist[j])
				{
					dist[j] = dist[u]+G->arcs[u][j];
					path[j] = u;
				}
	}
	DispPath(G,dist,path,s,v);   //根据参数输出最短路径
}//本算法还可以改改，算法中s[]的利用很鸡肋，s[]完全可以去掉或者做更有意义的事情

/*主函数*/
int main()
{
	VexGroup vg[MAX_VEX_NUM] = "0123456";
	ArcGroup ag[MAX_ARC_NUM] = {{'0','1',4},{'0','2',6},
	{'0','3',6},{'1','2',1},{'1','4',7},{'2','4',6},
	{'2','5',4},{'3','2',2},{'3','5',5},{'4','6',6},
	{'5','4',1},{'5','6',8}};
	int vexnum = 7, arcnum = 12;
	
	MGraph *G1;
	G1 = CreateMGraph(vg,ag,DN,vexnum,arcnum);
	printf("G1:\n"); DispMGraph(G1); printf("\n");
	
	int v;
	printf("请输入起始点下标:");
	scanf("%d",&v);
	Dijkstra(G1,v);
	
	system("pause");
	return 0;
}