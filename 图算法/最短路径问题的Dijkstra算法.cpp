#include <stdio.h>
#include <stdlib.h>

/****************************/
/*���·�������Dijkstra�㷨*/
/****************************/

#define INF 32767
#define MAX_VEX_NUM 10
#define MAX_ARC_NUM MAX_VEX_NUM*MAX_VEX_NUM
typedef enum
{
	DG, DN, UDG, UDN  //�ֱ�Ϊ����ͼ��������������ͼ��������
}GraphType;
typedef char VexType;
typedef struct
{
	VexType vexs[MAX_VEX_NUM];          //������Ϣ���涨MAX_VEX_NUM-1λ�ò�ʹ�á�
	int arcs[MAX_VEX_NUM][MAX_VEX_NUM]; //�ڽӾ���
	int vexnum, arcnum;                 //ͼ�Ķ������ͻ���
	GraphType type;                     //ͼ�������־
}MGraph;

//���㼯�Ϻͱ߼�������
typedef VexType VexGroup;
typedef struct
{
	VexType orinvex,adjvex;
	int weight;
}ArcGroup;

/*GetIndexOfVexs:�������Ƶõ�ָ�������ڶ��㼯���е��±�*/
/*ע:Ϊ�˽�ȫ�Կ����±�MAX_VEX_NUM-1λ�ò�ʹ�ã������ڲ��Ҳ���Ŀ�궥
��ʱ������ֵ*/
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

/*CreateMGraph:���ݶ��㼯�Ϻͱ߼��Ϲ����ڽӾ���*/
MGraph *CreateMGraph(VexGroup vexs[], ArcGroup arcs[], GraphType type, int vexnum, int arcnum)
{
	int i,j;
	int v1, v2;
	int weight;
	MGraph *G;                               //����ͼָ��
	G = (MGraph*)malloc(sizeof(MGraph));    //�����ڴ�ռ�
	G->type = type;                           //��ʼ����
	G->vexnum = vexnum;
	G->arcnum = arcnum;
	//�ڽӾ����ʼ��
	if(type == DN || type == UDN){//������
		for(i = 0; i < G->vexnum; i++)
			for(j = 0; j < G->vexnum; j++)
			{
				if(i != j)
					G->arcs[i][j] = INF;  //���������ʼ��ΪINF
				else
					G->arcs[i][j] = 0;   //�����ʼ��Ϊ0
			}
	}
	else{//ͼ����
		for(i = 0; i < G->vexnum; i++)
			for(j = 0; j < G->vexnum; j++)
				G->arcs[i][j] = 0;  //��������ͱ����ʼ��Ϊ0
	}
	for(i = 0; i < vexnum; i++){//������
		G->vexs[i] = vexs[i];
	}
	
	for(i = 0; i < arcnum; i++){//�����
	    v1 = GetIndexOfVexs(arcs[i].orinvex,G);
		v2 = GetIndexOfVexs(arcs[i].adjvex,G);
	    if(type == DN || type == UDN)
		{//������
			weight = arcs[i].weight;
		}
		else{//ͼ����
			weight = 1;
		}
		G->arcs[v1][v2] = weight;
		if(type == UDG || type == UDN)
		{//���������ͼ��������
			G->arcs[v2][v1] = weight;
		}
	}
	return G;
}

/*DispMGraph:��ӡ�ڽӾ���Ͷ�����Ϣ*/
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
				printf("\t��");
			else
			    printf("\t%2d",MG->arcs[i][j]);
		}
		printf("\n");
	}
}

/*DispPath:���ݲ�����ӡ���v������������·��*/
void DispPath(MGraph *G,int dist[], int path[], int s[], int v)
{
	int i;
	int u;
	int stack[MAX_VEX_NUM];
	int top = -1; //����ջ
	for(i = 0; i < G->vexnum; i++)
	{
		if(s[i] == 0)
		    printf("%c��%cû�����·��, ·������Ϊ��\n",G->vexs[v],G->vexs[i]);
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
			printf("%c��%c�����·��Ϊ",G->vexs[v],G->vexs[i]);
			while(top > -1)
			{
				printf("%c->",G->vexs[stack[top]]);
				top--;
			}
			printf("%c",G->vexs[i]);
			printf(", ·������Ϊ%d\n",dist[i]);
		}
	}
}

/*Dijkstra:���·������ĵҿ�˹�����㷨*/
void Dijkstra(MGraph *G, int v)//vΪ��ʼ����±�
{//�輯��S�뼯��U����ʼʱS�����н���v��U����������������
	int dist[MAX_VEX_NUM];
	//��¼���·������
	int path[MAX_VEX_NUM]; 
	//��¼���·��,path[k]��ֵ��ʾ����v������k�����·���ж���k��ǰһ������
	int s[MAX_VEX_NUM];    
	//��Ǹ������Ƿ��ڼ���S��
	int mindis,u;
	int i,j;
	for(i = 0; i < G->vexnum; i++)
	{
		dist[i] = G->arcs[v][i];  //dist�����ʼ����
		s[i] = 0;                 //s[]�ÿ�
		if(G->arcs[v][i] < INF)   //·����ʼ��
		    path[i] = v;
		else
			path[i] = -1;
	}
	s[v] = 1;                     //ԭ��v����S��
	for(i = 0; i < G->vexnum; i++)
	{
		mindis = INF;
		u = v; //��ʼ��Ϊv.
		for(j = 0; j < G->vexnum; j++)
			if(s[j] == 0 && dist[j] < mindis) 
			{//�ҵ�ǰU���ϵ�S���ϵ���С·�����ȶ���u
				u = j;
				mindis = dist[j];
			}
		s[u] = 1;                      //����u����S
		for(j = 0; j < G->vexnum; j++) //�����¼���S���е���
			if(s[j] == 0)
				if(G->arcs[u][j] < INF && dist[u]+G->arcs[u][j] < dist[j])
				{
					dist[j] = dist[u]+G->arcs[u][j];
					path[j] = u;
				}
	}
	DispPath(G,dist,path,s,v);   //���ݲ���������·��
}//���㷨�����Ըĸģ��㷨��s[]�����úܼ��ߣ�s[]��ȫ����ȥ���������������������

/*������*/
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
	printf("��������ʼ���±�:");
	scanf("%d",&v);
	Dijkstra(G1,v);
	
	system("pause");
	return 0;
}