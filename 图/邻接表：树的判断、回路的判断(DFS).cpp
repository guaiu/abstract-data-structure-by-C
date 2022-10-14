#include <stdio.h>
#include <stdlib.h>

/****************************************/
/*深度遍历算法应用：树的判断、回路的判断*/
/****************************************/

/*注：使用下标位置0，不使用下标位置MAX_VEX_NUM-1*/

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

/*DFS:邻接表的深度遍历算法*/
int visited[MAX_VEX_NUM];  //声明全局变量
void DFS(ALGraph *G, int v)
{
	ArcNode *p; int w;
	visited[v] = 1;                    //置已访问标记
	printf("%c ",G->adjlist[v].data);  //输出被访问顶点信息
	p = G->adjlist[v].firstarc;        //p指向顶点v的第一条边的头节点
	while(p != NULL)
	{
		w = p->adjvex;
		if(visited[w] == 0)
			DFS(G,w);       //若w顶点未访问，递归访问它
		p = p->nextarc;     //p指向顶点v的下一条边的边头节点
	}
}

/*visited数组归零*/
void ReVisited()
{
	int i;
	for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;
}

/*DFS2:得到该无向连通图的顶点数和边数*/
void DFS2(ALGraph *G, int v, int &vn, int &en)
{
	ArcNode *p;
	visited[v] = 1; vn++;    //遍历过的顶点数增1
	p = G->adjlist[v].firstarc;
	while(p != NULL)
	{
		en++;                //试探过的边数增1
		if(visited[p->adjvex] == 0)
			DFS2(G,p->adjvex,vn,en);
		p = p->nextarc;
	}
}

/*GIsTree:判断无向图G是否是一棵树*/
bool GIsTree(ALGraph *G)
{
	int vn = 0, en = 0;
	ReVisited();
	DFS2(G,0,vn,en);
	if(en == 2*(vn-1))
		return true;
	else
		return false;
}

/*Cycle:判断连通图中是否存在回路*/
void Cycle(ALGraph *G, int v, bool &has)
{//调用时has置初值为false
    ArcNode *p; int w;
	visited[v] = 1;              //置已访问标记
	p = G->adjlist[v].firstarc;  //p指向顶点v的第一个邻接点
	while(p != NULL)
	{
		w = p->adjvex;
		if(visited[w] == 0)      //若顶点w未访问，递归访问它
		    Cycle(G,w,has);
		else
		    has = true;
		p = p->nextarc;		
	}
}

/*主函数*/
int main()
{
	bool has = false;
	//初始化并测试
	VexGroup vg[MAX_VEX_NUM] = "ABCDE";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',1},{'B','C',1},
	{'C','D',3},{'D','A',2},{'C','E',1},{'E','D',1}};
	int vexnum = 5, arcnum = 6;
	ALGraph *G1;
	G1 = CreateALGraph(vg,ag,DG,vexnum,arcnum);
	printf("G1:\n"); DispALGraph(G1); printf("\n");
	ReVisited();
	printf("DFS:");
	DFS(G1,0); printf("\n");
	ReVisited();
	
	(GIsTree(G1))?(printf("G是树\n")):(printf("G不是树\n"));
	ReVisited();
	Cycle(G1,0,has);
	(has)?(printf("有回路\n")):(printf("无回路\n"));
	
	printf("------------------------\n");
	//测试2
	has = false;
	VexGroup vg2[MAX_VEX_NUM] = "ABCDE";
	ArcGroup ag2[MAX_ARC_NUM] = {{'A','B',1},{'B','C',1},
	{'B','D',1},{'A','E',1}};
	int vexnum2 = 5, arcnum2 = 4;
	ALGraph *G2;
	G2 = CreateALGraph(vg2,ag2,DG,vexnum2,arcnum2);
	printf("G2:\n"); DispALGraph(G2); printf("\n");
	ReVisited();
	printf("DFS:");
	DFS(G2,0); printf("\n");
	ReVisited();
	
	(GIsTree(G2))?(printf("是树\n")):(printf("不是树\n"));
	ReVisited();
	Cycle(G2,0,has);
	(has)?(printf("有回路\n")):(printf("无回路\n"));
	
	
	system("pause");
	return 0;
}