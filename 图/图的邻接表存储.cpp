#include <stdio.h>
#include <stdlib.h>

/********************/
/*图的邻接表存储构造*/
/********************/

/*非通用表，弃用下标位置0*/

#define MAX_VEX_NUM 20
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

/*GetIndexOfAdjlist:根据名称得到指定顶点在顶点集合中的下标*/
/*注:为了健全性考虑下标0位置不使用，仅用于查找不到目标顶
点时作返回值*/
int GetIndexOfAdjlist(char vex, ALGraph *G)
{
	int i;
	for(i = 1; i <= G->vexnum; i++)
	{
		if(G->adjlist[i].data == vex)
			return i;
			
	}
	return 0;
}

/*CreateALGraph:创建邻接表*/
/*注:为了简便，这里将直接包含接收用户输入数据的代码，而不是另外将
顶点集合和弧集合作为参数输入*/
void CreateALGraph(ALGraph *&G)
{
	int i;
	int v1, v2, type, weight;
	char c1, c2;
	G = (ALGraph*)malloc(sizeof(ALGraph));  //分配内存空间
	ArcNode *arc;
	printf("Please input grapg type DG(0) or DN(1) or UDG(2) or UDN(3):");
	scanf("%d",&type);
	switch(type)
	{
		case 0: G->type = DG; break;
		case 1: G->type = DN; break;
		case 2: G->type = UDG; break;
		case 3: G->type = UDN; break;
		default:{
		printf("Please input correct graph type DG(0) or DN(1) or UDG(2) or UDN(3)!\n");
        free(G); G = NULL;
		return ;
		}
	}
	printf("Please input vexnum:");
	scanf("%d",&G->vexnum);
	printf("Please input arcnum:");
	scanf("%d",&G->arcnum);
	getchar();
	//初始化顶点
	for(i = 1; i <= G->vexnum; i++){//初始化顶点
		G->adjlist[i].firstarc = NULL;
	}
	//输入顶点信息
	for(i = 1; i <= G->vexnum; i++)
	{//下标从1开始
		printf("Please input %dth vex(char):",i);
		scanf("%c",&G->adjlist[i].data);
		getchar();
	}
	//输入边的信息，建立邻接表
	for(i = 1; i <= G->arcnum; i++)
	{
		printf("Please input %dth arc v1(char) v2(char)",i);
		scanf("%c %c",&c1, &c2);
		getchar();
		v1 = GetIndexOfAdjlist(c1,G);
		v2 = GetIndexOfAdjlist(c2,G);
		if(v1 == 0 || v2 == 0 || v1 == v2)
		{//若输入错误顶点信息(仅包含部分错误)
			printf("Please input correct vex data!\n");
			free(G); G = NULL;
		    return ;
		}
		
		if(G->type == DN || G->type == UDN)
		{
			printf("Please input the weight:");
			scanf("%d",&weight);
			getchar();
		}
		else
		{//无权则统一设为1
			weight = 1;
		}
		
		arc = (ArcNode*)malloc(sizeof(ArcNode));
		arc->adjvex = v2;
		arc->weight = weight;
		arc->nextarc = G->adjlist[v1].firstarc;
		G->adjlist[v1].firstarc = arc;
		if(G->type == UDG || G->type == UDN){//若为无向图
			arc = (ArcNode*)malloc(sizeof(ArcNode));
		    arc->adjvex = v1;
		    arc->weight = weight;
		    arc->nextarc = G->adjlist[v2].firstarc;
		    G->adjlist[v2].firstarc = arc;
		}
	}
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
	for(i = 1; i <= G->vexnum; i++){
		printf("%c",G->adjlist[i].data);
	}
	printf("\nAdjacency List:\n");
	for(i = 1; i <= G->vexnum; i++)
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

/*主函数*/
int main()
{
	ALGraph *G=NULL;
	CreateALGraph(G);
	DispALGraph(G);
	system("pause");
	return 0;
}