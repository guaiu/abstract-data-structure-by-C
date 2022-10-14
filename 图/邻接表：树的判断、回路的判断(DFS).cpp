#include <stdio.h>
#include <stdlib.h>

/****************************************/
/*��ȱ����㷨Ӧ�ã������жϡ���·���ж�*/
/****************************************/

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

/*DFS2:�õ���������ͨͼ�Ķ������ͱ���*/
void DFS2(ALGraph *G, int v, int &vn, int &en)
{
	ArcNode *p;
	visited[v] = 1; vn++;    //�������Ķ�������1
	p = G->adjlist[v].firstarc;
	while(p != NULL)
	{
		en++;                //��̽���ı�����1
		if(visited[p->adjvex] == 0)
			DFS2(G,p->adjvex,vn,en);
		p = p->nextarc;
	}
}

/*GIsTree:�ж�����ͼG�Ƿ���һ����*/
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

/*Cycle:�ж���ͨͼ���Ƿ���ڻ�·*/
void Cycle(ALGraph *G, int v, bool &has)
{//����ʱhas�ó�ֵΪfalse
    ArcNode *p; int w;
	visited[v] = 1;              //���ѷ��ʱ��
	p = G->adjlist[v].firstarc;  //pָ�򶥵�v�ĵ�һ���ڽӵ�
	while(p != NULL)
	{
		w = p->adjvex;
		if(visited[w] == 0)      //������wδ���ʣ��ݹ������
		    Cycle(G,w,has);
		else
		    has = true;
		p = p->nextarc;		
	}
}

/*������*/
int main()
{
	bool has = false;
	//��ʼ��������
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
	
	(GIsTree(G1))?(printf("G����\n")):(printf("G������\n"));
	ReVisited();
	Cycle(G1,0,has);
	(has)?(printf("�л�·\n")):(printf("�޻�·\n"));
	
	printf("------------------------\n");
	//����2
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
	
	(GIsTree(G2))?(printf("����\n")):(printf("������\n"));
	ReVisited();
	Cycle(G2,0,has);
	(has)?(printf("�л�·\n")):(printf("�޻�·\n"));
	
	
	system("pause");
	return 0;
}