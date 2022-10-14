#include <stdio.h>
#include <stdlib.h>

/**********************/
/*图的邻接矩阵存储构造*/
/**********************/

/*注：本代码构建的邻接矩阵第0行和第0列弃用，因此并不是一个通用的邻接矩阵*/

#define MAX_VEX_NUM 50
typedef enum
{
	DG, DN, UDG, UDN  //分别为有向图、有向网、无向图、无向网
}GraphType;
typedef char VertexType;
typedef struct
{
	VertexType vexs[MAX_VEX_NUM];       //顶点信息。规定0位置不使用。
	int arcs[MAX_VEX_NUM][MAX_VEX_NUM]; //邻接矩阵
	int vexnum, arcnum;                 //图的顶点数和弧数
	GraphType type;                     //图的种类标志
}MGraph;

/*GetIndexOfVexs:根据名称得到指定顶点在顶点集合中的下标*/
/*注:为了健全性考虑下标0位置不使用，仅用于查找不到目标顶
点时作返回值*/
int GetIndexOfVexs(char vex, MGraph *MG)
{
	int i;
	for(i = 1; i <= MG->vexnum; i++)
	{
		if(MG->vexs[i] == vex)
			return i;
			
	}
	return 0;
}

/*CreateMGraph:创建邻接矩阵*/
/*注:为了简便，这里将直接包含接收用户输入数据的代码，而不是另外将
顶点集合和弧集合作为参数输入*/
void CreateMGraph(MGraph *&MG)
{
	int i, j, k;
	int v1, v2, type, weight;
	char c1, c2;
	MG = (MGraph*)malloc(sizeof(MGraph));  //分配内存空间
	printf("Please input grapg type DG(0) or DN(1) or UDG(2) or UDN(3):");
	scanf("%d",&type);
	switch(type)
	{
		case 0: MG->type = DG; break;
		case 1: MG->type = DN; break;
		case 2: MG->type = UDG; break;
		case 3: MG->type = UDN; break;
		default:{
		printf("Please input correct graph type DG(0) or DN(1) or UDG(2) or UDN(3)!\n");
		free(MG); MG = NULL;
		return ;
		}
	}
	printf("Please input vexnum:");
	scanf("%d",&MG->vexnum);
	printf("Please input arcnum:");
	scanf("%d",&MG->arcnum);
	getchar();
	for(i = 1; i <= MG->vexnum; i++)
	{//下标从1开始
		printf("Please input %dth vex(char):",i);
		scanf("%c",&MG->vexs[i]);
		getchar();
	}
	//初始化邻接矩阵
	for(i = 1; i <= MG->vexnum; i++)
	{
		for(j = 1; j <= MG->vexnum; j++)
		{
			if(MG->type == DN || MG->type == UDN)
			{//若为有权图，i==j时初始化为-1，其他情况初始化为0
		        if(i == j)
			        MG->arcs[i][j] = -1;
				else
					MG->arcs[i][j] = 0;
			}
			else
			{
				MG->arcs[i][j] = 0;
			}
		}
	}
	//输入边的信息，建立邻接矩阵
	for(k = 1; k <= MG->arcnum; k++)
	{
		printf("Please input %dth arc v1(char) v2(char)",k);
		scanf("%c %c",&c1, &c2);
		getchar();
		if(MG->type == DN || MG->type == UDN)
		{
			printf("Please input the weight:");
			scanf("%d",&weight);
			getchar();
		}
		else
		{
			weight = 1;
		}
		v1 = GetIndexOfVexs(c1,MG);
		v2 = GetIndexOfVexs(c2,MG);
		if(MG->type == UDG || MG->type == UDN)
		{//无向图或无向网具有对称性
			MG->arcs[v1][v2] = MG->arcs[v2][v1] = weight;
		}
		else
		{
			MG->arcs[v1][v2] = weight;
		}
	}
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
	for(i = 1; i <= MG->vexnum; i++)
	{
		printf("%c",MG->vexs[i]);
	}
	printf("\nAdjacency Matrix:\n");
	for(i = 1; i <= MG->vexnum; i++)
	{
		for(j = 1; j <= MG->vexnum; j++)
		{
			printf("\t%2d",MG->arcs[i][j]);
		}
		printf("\n");
	}
}

/*主函数*/
int main()
{
	MGraph *MG=NULL;
	CreateMGraph(MG);
	DispMGraph(MG);
	system("pause");
	return 0;
}