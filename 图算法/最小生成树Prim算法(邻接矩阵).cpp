#include <stdio.h>
#include <stdlib.h>

/******************************/
/*最小生成树Prim算法(邻接矩阵)*/
/******************************/

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

/*Prim:最小生成树的普里姆算法*/
void Prim(MGraph *G, int v)
{
	int lowcost[MAX_VEX_NUM];      //存放V-U各顶点到U集合的最小边的权值
	int min;
	int closest[MAX_VEX_NUM];      //存放V-U各顶点到U集合的最小边,
	                               //位置标号表示该最小边在V-U中的顶点编号,
								   //closest[]表示该边在U中的顶点编号
	//例如,(G->vexs[j]，closest[j])是顶点j到集合U的最小边，权值为lowcost[j]
	int i,j,k;
	for(i = 0; i < G->vexnum; i++)
	{//给lowcost[]和closest[]置初值
        lowcost[i] = G->arcs[v][i];
		closest[i] = v;
	}
	for(i = 1; i < G->vexnum; i++)     //输出vexnum-1条边
	{
		min = INF;
		for(j = 0; j < G->vexnum; j++) //在(V-U)中找出离U最近的顶点k
		    if(lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;            //k记录最近顶点编号
			}
		printf(" 边(%c,%c)权为:%d\n",G->vexs[closest[k]],G->vexs[k],min);
		lowcost[k] = 0;    //标记k已经加入U,则k到达U的最小权值为0
		for(j = 0; j < G->vexnum; j++) //根据新U集合修改数组lowcost和closest
		    if(lowcost[j] != 0 && G->arcs[k][j] < lowcost[j])
			{
				lowcost[j] = G->arcs[k][j];
				closest[j] = k;
			}
	}
}

/*主函数*/
int main()
{
	VexGroup vg[MAX_VEX_NUM] = "0123456";
	ArcGroup ag[MAX_ARC_NUM] = {{'0','1',28},{'1','2',16},
	{'2','3',12},{'3','4',22},{'4','5',25},{'5','0',10},
	{'1','6',14},{'3','6',18},{'4','6',24}};
	int vexnum = 7, arcnum = 9;
	
	MGraph *G1;
	G1 = CreateMGraph(vg,ag,UDN,vexnum,arcnum);
	printf("G1:\n"); DispMGraph(G1); printf("\n");
	
	Prim(G1,0);

	system("pause");
	return 0;
}