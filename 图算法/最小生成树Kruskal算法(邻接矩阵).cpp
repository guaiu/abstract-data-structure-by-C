#include <stdio.h>
#include <stdlib.h>

/*********************************/
/*最小生成树Kruskal算法(邻接矩阵)*/
/*********************************/

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

/*InsertSort:对边集合按权值递增排序*/
void InsertSort(ArcGroup *E, int k)
{
	int i,j;
	ArcGroup temp;
	for(i = 1; i < k; i++)//从下标1开始
	{
		temp = E[i];
		for(j = i-1; j >= 0 && temp.weight < E[j].weight; j--)
		{
			E[j+1] = E[j];  //将较大元素后移
		}
		E[j+1] = temp;      //temp插入正确位置
	}
}

/*Kruskal:最小生成树的克鲁斯卡尔算法(邻接矩阵)*/
void Kruskal(MGraph *G)
{
	int i,j;
	int u1,v1,sn1,sn2,k;
	int vset[MAX_VEX_NUM];
	ArcGroup E[MAX_ARC_NUM];        //存放所有边
	k = 0;                          //当前用于边的计数(下标从0开始)
	for(i = 0; i < G->vexnum; i++)  //初始化边集合(注意矩阵的对称性)
		for(j = 0; j < G->vexnum; j++)
			if(i >= j && G->arcs[i][j] != 0 && G->arcs[i][j] != INF)
			{//有对称性，收集矩阵下三角和对角线就可以了
				E[k].orinvex = i;
				E[k].adjvex = j;
				E[k].weight = G->arcs[i][j];
				k++;
			}
	InsertSort(E,G->arcnum);               //用直接插入排序对E数组按权值递增排序
	for(i = 0; i < G->vexnum; i++) //初始化辅助数组
		vset[i] = i;
	k = 1;    //当前用于计数构造生成树的边
	j = 0;    //当前用于计数E中边的下标
	while(k < G->vexnum)//最小生成树有G->vexnum-1条边
	{
		u1 = E[j].orinvex;
		v1 = E[j].adjvex;      //取边的顶点
		sn1 = vset[u1];       
		sn2 = vset[v1];        //取辅助信息
		if(sn1 != sn2)         //若两顶点属于不同的集合
		{
			printf(" 边(%c,%c)权为:%d\n",G->vexs[u1],G->vexs[v1],E[j].weight);
			k++;  //边数加一
			for(i = 0; i < G->vexnum; i++)  //两个集合统一编号
				if(vset[i] == sn2)          //集合编号为sn2的改为sn1
					vset[i] = sn1;
		}
		j++;  //扫描下一条边
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
	
	Kruskal(G1);

	system("pause");
	return 0;
}