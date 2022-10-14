#include <stdio.h>
#include <stdlib.h>

/********************************/
/*��ȱ����㷨Ӧ�ã���·������*/
/********************************/

/*ע��ʹ���±�λ��0����ʹ���±�λ��MAX_VEX_NUM-1*/

#define MAX_VEX_NUM 10
#define MAX_ARC_NUM 10
typedef char VexType;
typedef enum
{
	DG, DN, UDG, UDN  //�ֱ�Ϊ����ͼ��������������ͼ��������
}GraphType;

typedef struct ANode
{
	int adjvex;            //�ñߵ��յ���
	struct ANode *nextarc; //ָ����һ���ߵ�ָ��
	int weight;            //Ȩ��(��������Ϣ������Ϊ�˼��ֻ��¼Ȩ��)
}ArcNode;

typedef struct
{
	VexType data;         //������Ϣ
	ArcNode *firstarc;    //ָ���һ����
}VexNode;

typedef struct
{
	VexNode adjlist[MAX_VEX_NUM];  //�ڽӱ�
	int vexnum, arcnum;            //�����������
	GraphType type;                //�ڽӱ����͡����ض�������ڽӱ�û�����塣
	
}ALGraph;

//���㼯�Ϻͱ߼�������
typedef VexType VexGroup;
typedef struct
{
	VexType orinvex,adjvex;
	int weight;
}ArcGroup;

/*GetIndexOfAdjlist:�������Ƶõ�ָ�������ڶ��㼯���е��±�*/
/*ע:Ϊ�˽�ȫ�Կ����±�MAX_VEX_NUM-1λ�ò�ʹ�ã������ڲ��Ҳ���Ŀ�궥
��ʱ������ֵ*/
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

/*DispALGraph:��ӡ�ڽӱ�Ͷ�����Ϣ*/
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

/*CreateALGraph:���ݶ��㼯�Ϻͱ߼��Ϲ����ڽӱ�*/
ALGraph *CreateALGraph(VexGroup vexs[], ArcGroup arcs[], GraphType type, int vexnum, int arcnum)
{
	int i;
	int v1, v2;
	ArcNode *q;
	ALGraph *G;                               //����ͼָ��
	G = (ALGraph*)malloc(sizeof(ALGraph));    //�����ڴ�ռ�
	G->type = type;                           //��ʼ����
	G->vexnum = vexnum;
	G->arcnum = arcnum;
	for(i = 0; i < vexnum; i++){//����
		G->adjlist[i].data = vexs[i];
		G->adjlist[i].firstarc = NULL;
	}
	G->adjlist[MAX_VEX_NUM-1].firstarc = NULL; //��ʹ��λ�ÿ�
	G->adjlist[MAX_VEX_NUM-1].data = '#';
	
	for(i = 0; i < arcnum; i++){//��
	    v1 = GetIndexOfAdjlist(arcs[i].orinvex, G);
		v2 = GetIndexOfAdjlist(arcs[i].adjvex, G);
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = v2;
		q->nextarc = G->adjlist[v1].firstarc;
		G->adjlist[v1].firstarc = q;
		q->weight = arcs[i].weight;
		if(type == UDG || type == UDN)
		{//���������ͼ��������
			q = (ArcNode*)malloc(sizeof(ArcNode));
		    q->adjvex = v1;
		    q->nextarc = G->adjlist[v2].firstarc;
		    G->adjlist[v2].firstarc = q;
		    q->weight = arcs[i].weight;
		}
	}
	return G;
}

/*DFS:�ڽӱ����ȱ����㷨*/
int visited[MAX_VEX_NUM];  //����ȫ�ֱ���
void DFS(ALGraph *G, int v)
{
	ArcNode *p; int w;
	visited[v] = 1;                    //���ѷ��ʱ��
	printf("%c ",G->adjlist[v].data);  //��������ʶ�����Ϣ
	p = G->adjlist[v].firstarc;        //pָ�򶥵�v�ĵ�һ���ߵ�ͷ�ڵ�
	while(p != NULL)
	{
		w = p->adjvex;
		if(visited[w] == 0)
			DFS(G,w);       //��w����δ���ʣ��ݹ������
		p = p->nextarc;     //pָ�򶥵�v����һ���ߵı�ͷ�ڵ�
	}
}

/*visited�������*/
void ReVisited()
{
	int i;
	for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;
}

/*ExisPath:�ж϶���u->v�Ƿ��м�·��*/
void  ExisPath(ALGraph *G, int u, int v, bool &has)
{//�漰���ݹ�,�����ô��ε���ʽ��¼���,
 //has��ʾu��v�Ƿ���·������ֵΪfalse
    int w; ArcNode *p;
	visited[u] = 1;            //���ѷ��ʱ��
	if(u == v)                 //�ҵ���һ��·��
	{
		has = true;            //��hasΪtrue�������㷨
		return ;
	}
	p = G->adjlist[u].firstarc;//pָ�򶥵�u�ĵ�һ�����ڵ�
    while(p != NULL)
	{
		w = p->adjvex;           //wΪ����u�����ڶ���
		if(visited[w] == 0)      //��w����δ���ʣ��ݹ������
		    ExisPath(G,w,v,has);
		p = p->nextarc;          //pָ�򶥵�u����һ�����ڵ�
	}
}

/*FindaPath:���һ����·��*/
void FindaPath(ALGraph *G, int u, int v, int path[], int d)
{//d��ʾpath�е�·�������ȣ���ʼδ-1
    int w,i; ArcNode *p;
	visited[u] = 1;
	d++; path[d] = u;  //·������d��1������u���뵽·����
	if(u == v)
	{
		printf("һ����·��Ϊ:");
		for(i = 0; i <= d; i++)
		    printf("%c ",G->adjlist[path[i]].data);
		printf("\n");
		return ;
	}
	p = G->adjlist[u].firstarc;    //pָ�򶥵�u�ĵ�һ�����ڵ�
	while(p != NULL)
	{
		w = p->adjvex;
		if(visited[w] == 0)
			FindaPath(G,w,v,path,d);
		p = p->nextarc;            //pָ�򶥵�u����һ�����ڵ�
	}
}

/*FindPath:���u->v�����м�·��*/
void FindPath(ALGraph *G, int u, int v, int path[], int d)
{//d��ʾpath�е�·�����ȣ���ʼΪ-1
	int w, i;
	ArcNode *p;
	d++; path[d] = u;        //·������d��1,����u���뵽·����
	visited[u] = 1;          //���ѷ��ʱ��
	if(u == v && d >= 1)     //�ҵ�·�������
	{
		for(i = 0; i <= d; i++)
			printf("%c ", G->adjlist[path[i]].data);
		printf("\n");
	}
	p = G->adjlist[u].firstarc;   //pָ�򶥵�u�ĵ�һ�����ڵ�
	while(p != NULL)
	{
		w = p->adjvex;            //wΪ����u�����ڶ���
		if(visited[w] == 0)       //��w����δ���ʣ��ݹ������
		    FindPath(G,w,v,path,d);
		p = p->nextarc;
	}
	visited[u] = 0;  //�ָ�������ʹ�ö��������ʹ��
}

/*PathAll:���u->v�����г���δl�ļ�·��*/
void PathAll(ALGraph *G, int u, int v, int l, int path[], int d)
{//d��ʾpath�е�·�����ȣ���ʼΪ-1
	int w, i;
	ArcNode *p;
	d++; path[d] = u;        //·������d��1,����u���뵽·����
	visited[u] = 1;          //���ѷ��ʱ��
	if(u == v && d == l)     //�ҵ�����������·�������
	{
		for(i = 0; i <= d; i++)
			printf("%c ", G->adjlist[path[i]].data);
		printf("\n");
	}
	p = G->adjlist[u].firstarc;   //pָ�򶥵�u�ĵ�һ�����ڵ�
	while(p != NULL)
	{
		w = p->adjvex;            //wΪ����u�����ڶ���
		if(visited[w] == 0)       //��w����δ���ʣ��ݹ������
		    PathAll(G,w,v,l,path,d);
		p = p->nextarc;
	}
	visited[u] = 0;  //�ָ�������ʹ�ö��������ʹ��
}

/*������*/
int main()
{
	bool has = false;
	int path[MAX_VEX_NUM];
	//��ʼ��������
	VexGroup vg[MAX_VEX_NUM] = "ABCDE";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',1},{'B','C',1},
	{'C','D',3},{'D','A',2},{'C','E',1},{'E','D',1}};
	int vexnum = 5, arcnum = 6;
	ALGraph *G1;
	G1 = CreateALGraph(vg,ag,UDG,vexnum,arcnum);
	printf("G1:\n"); DispALGraph(G1); printf("\n");
	ReVisited();
	printf("DFS:");
	DFS(G1,0); printf("\n");
	ReVisited();
	
	ExisPath(G1,GetIndexOfAdjlist('B',G1),GetIndexOfAdjlist('E',G1),has);
	if(has)
	{
		ReVisited();
		printf("�ҳ�һ��·��:\n");
		FindaPath(G1,GetIndexOfAdjlist('B',G1),GetIndexOfAdjlist('E',G1),path,-1);
		printf("------------------------------\n");
		ReVisited();
		printf("�ҳ�����·��:\n");
		FindPath(G1,GetIndexOfAdjlist('B',G1),GetIndexOfAdjlist('E',G1),path,-1);
		printf("------------------------------\n");
		ReVisited();
		printf("�ҳ����г�Ϊl��·��\n");
		PathAll(G1,GetIndexOfAdjlist('B',G1),GetIndexOfAdjlist('E',G1),3,path,-1);
		printf("-----------finish-------------\n");
	}
	else
		printf("û�м�·��\n");
	
	
	
	system("pause");
	return 0;
}
