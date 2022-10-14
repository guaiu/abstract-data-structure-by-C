#include <stdio.h>
#include <stdlib.h>

/*****************************/
/*AOE网求关键路径问题(邻接表)*/
/*****************************/

/*注：使用下标位置0，不使用下标位置MAX_VEX_NUM-1*/
//注：貌似哨兵一般是用位置0的，我这种使用MAX_VEX_NUM-1位置的不是太规范

#define MAX_VEX_NUM 10
#define MAX_ARC_NUM MAX_VEX_NUM*(MAX_VEX_NUM-1)
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

/*TopSort:获取拓扑序列并储存在数组S中，若无回路则返回1，否则返回0*/
int TopSort(ALGraph *G, int *S)
{
	int i,count,gettop,k;
	ArcNode *p;
	int *stack = (int*)malloc(sizeof(int)*G->vexnum); //辅助栈
	int top = -1;
	int *in = (int*)malloc(sizeof(int)*G->vexnum);    //存储各顶点入度信息,初始置0
	for(i = 0; i < G->vexnum; i++)
		in[i] = 0;
	
	for(i = 0; i < G->vexnum; i++)
	{
		p = G->adjlist[i].firstarc;   //指向第一个相邻顶点
		while(p != NULL)
		{
			in[p->adjvex]++;
			p = p->nextarc;
		}
	}
	for(i = 0; i < G->vexnum; i++)
		if(in[i] == 0)
		{
			top++;
			stack[top] = i;  //入度为0的顶点入栈
		}
	
	count = 0;       //计数初始化
	while(top > -1)  //栈不空循环
	{
		gettop = stack[top];  //出栈
		top--;
		S[count] = gettop;
		count++;
		p = G->adjlist[gettop].firstarc;
		while(p != NULL)
		{
			k = p->adjvex;
			in[k]--;
			if(in[k] == 0)
			{//满足条件则入栈
				top++;
				stack[top] = k;
			}
			p = p->nextarc;
		}
	}
	free(stack);           //释放内存空间
	free(in);
	
	if(count < G->vexnum)  //判断是否有环并返回结果
		return false;
	return true;
}
/*getweight:DFS1的辅助函数，返回两顶点组成的边的权值，无效则返回0*/
int getweight(int a, int b, ALGraph *G)
{
	int weight = 0;
	ArcNode *p;
	p = G->adjlist[a].firstarc;
	while(p != NULL)
	{
		if(p->adjvex == b){
			weight = p->weight;
			return weight;
		}
		p = p->nextarc;
	}
	return 0;
}

/*DFS1:深度遍历求关键路径*/
void DFS1(int a, int end, int *ee, int *le, ALGraph *G)
//这里默认至少有两个顶点组成路径
{
	static int pathnum = 0; //路径数量
	static int count = 0;   //当前路径长度
	static int *path = (int*)malloc(sizeof(int)*G->vexnum);
	/*以上为三个静态局部变量*/
	
	int i,temp;
	int ev, lv; //活动最早开始时间(early activity)和活动最晚开始时间(late activity)
    ArcNode *p;	
	
	if(a == end)  //当前节点编号为终点编号,打印
	{
		pathnum++;
		path[count++] = a;
		printf("THE %dTH PATH:\n",pathnum);
	    for(i = 0; i < count-1; i++)
		    printf("<%c - %c> length: %d\n", G->adjlist[path[i]].data, G->adjlist[path[i+1]].data, getweight(path[i],path[i+1],G));
	}
	
	p = G->adjlist[a].firstarc;
	while(p != NULL)
	{
		ev = ee[a];
		lv = le[p->adjvex] - p->weight;
		if(ev == lv)  //若不存在富余时间，则本活动为关键活动
		{
		    temp = count;       //备份
			path[count++] = a;  //记录一个顶点
		    DFS1(p->adjvex,end,ee,le,G);
		    count = temp;       //恢复
		}
		p = p->nextarc;
	}
}

/*CriticalPath:求关键路径，已知G是AOE网，输出G的关键活动*/
void CriticalPath(ALGraph *G)
{
	ArcNode *p;
	int i, j, k;
	int *ee, *le;  
	//分别为early event(事件最早开始时间)和late event(事件最迟开始事件)
	int *S = (int*)malloc(sizeof(int)*G->vexnum);  //拓扑排序序列
	
    TopSort(G,S);             //计算拓扑排序序列并储存在S中
	printf("the topological sort is...\n");
	for(i = 0; i < G->vexnum; i++)
		printf("%c->",G->adjlist[S[i]].data);
	printf("\n");
	
	//计算ee
	ee = (int*)malloc(sizeof(int)*G->vexnum); //用0(源点)初始化
	for(i = 0; i < G->vexnum; i++)
		ee[i] = 0;
	for(i = 0; i < G-> vexnum; i++)           //按照拓扑序列迭代算出每个顶点的ee
	{
		p = G->adjlist[S[i]].firstarc;
		while(p != NULL)
		{
			if((ee[S[i]]+p->weight) > ee[p->adjvex])
				ee[p->adjvex] = ee[S[i]]+p->weight;
			p = p->nextarc;
		}
	}
	
	//计算le
	le = (int*)malloc(sizeof(int)*G->vexnum); //用ee[G->vexnum-1](终点)初始化
	for(i = 0; i < G->vexnum; i++)
		le[i] = ee[G->vexnum-1];
	for(i = G->vexnum-1; i>= 0; i--)          //按照逆拓扑序列迭代算出每个顶点的le
	{
		p = G->adjlist[S[i]].firstarc;
		while(p != NULL)
		{
			if((le[p->adjvex]-p->weight) < le[S[i]])
				le[S[i]] = le[p->adjvex]-p->weight;
			p = p->nextarc;
		}
	}
	
	//如果仅输出输出一条路径
	int ev, lv; //活动最早开始时间(early activity)和活动最晚开始时间(late activity)
	j = S[0];
	p = G->adjlist[j].firstarc;
	printf("one of the Critical Path is:\n");
	while(p != NULL)
	{
		k = p->adjvex;
		ev = ee[j];
		lv = le[k] - p->weight;
		if(ev == lv){
			printf("<%c - %c> length: %d\n", G->adjlist[j].data, G->adjlist[k].data, p->weight);
			j = k;
			p = G->adjlist[j].firstarc;
			continue;
		}
		p = p->nextarc;
	}
		
	//如果用DFS输出所有的关键路径
	DFS1(S[0],S[G->vexnum-1],ee,le,G);
}


/*主函数*/
int main()
{
	VexGroup vg[MAX_VEX_NUM] = "ABCDEFGHI";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',6},{'A','C',4},
	{'A','D',5},{'B','E',1},{'C','E',1},{'D','H',2},
	{'E','F',9},{'E','G',7},{'F','I',2},{'G','I',4},
	{'H','I',4}};
	int vexnum = 9, arcnum = 11;
	
	ALGraph *G1;
	G1 = CreateALGraph(vg,ag,DN,vexnum,arcnum);
	printf("G1:\n"); DispALGraph(G1); printf("\n");
    
	CriticalPath(G1);
	
	system("pause");
	return 0;
}
