#include <stdio.h>
#include <stdlib.h>

/******************/
/*�ڽӾ���DFS��BFS*/
/******************/

#define MAX_VEX_NUM 10
#define MAX_ARC_NUM MAX_VEX_NUM*MAX_VEX_NUM
typedef enum
{
	DG, DN, UDG, UDN  //�ֱ�Ϊ����ͼ��������������ͼ��������
}GraphType;
typedef char VexType;
typedef struct
{
	VexType vexs[MAX_VEX_NUM];       //������Ϣ���涨MAX_VEX_NUM-1λ�ò�ʹ�á�
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
					G->arcs[i][j] = -1;  //���������ʼ��Ϊ-1
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
			printf("\t%2d",MG->arcs[i][j]);
		}
		printf("\n");
	}
}

/*MDFS:�ڽӾ������ȱ���*/
int visited[MAX_VEX_NUM];   //ȫ�ֱ���������Ԫ���ó�ֵΪ0
void MDFS(MGraph *G, int v)
{
	int w;
	printf("%c ",G->vexs[v]);  //���ʶ���v
	visited[v] = 1;            //����ѷ���
	for(w = 0; w < G->vexnum; w++)
		if(G->arcs[v][w] != 0 && G->arcs[v][w] != -1 && visited[w] == 0)
			MDFS(G,w);         //�ݹ����
}

/*MBFS:�ڽӾ������ȱ���*/
void MBFS(MGraph *G, int v)
{//vΪ�����
    int i,w;
    int queue[MAX_VEX_NUM], front = 0, rear = 0;  //�������
    int visited[MAX_VEX_NUM];                     //����������	
    for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;
	printf("%c ",G->vexs[v]);   //��ӡ�׶�����Ϣ
	visited[v] = 1;             //���
	rear++;
	queue[rear] = v;            //���
	while(front != rear)        //�Ӳ���ѭ��
	{
		front++;
		w = queue[front];       //����
		for(i = 0; i < G->vexnum; i++)
			if(G->arcs[w][i] != 0 && G->arcs[w][i] != -1 && visited[i] == 0)
			{//����֮
				printf("%c ",G->vexs[i]);
				visited[i] = 1;  //���
				rear++;
				queue[rear] = i; //����
			}
	}
}

/*������*/
int main()
{
	int i;
	VexGroup vg[MAX_VEX_NUM] = "ABCDE";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',1},{'B','C',1},
	{'C','D',3},{'D','A',2},{'C','E',1},{'E','D',1}};
	int vexnum = 5, arcnum = 6;
	
	MGraph *G1;
	G1 = CreateMGraph(vg,ag,UDG,vexnum,arcnum);
	printf("G1:\n"); DispMGraph(G1); printf("\n");
	
	for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;  //��������ʼ��
	
	printf("DFS:");
	MDFS(G1,0); printf("\n");
	printf("BFS:");
	MBFS(G1,0); printf("\n");
	
	system("pause");
	return 0;
}