#include <stdio.h>
#include <stdlib.h>

/********************/
/*�ڽӾ���ļ��׹���*/
/********************/

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

/*������*/
int main()
{
	VexGroup vg[MAX_VEX_NUM] = "ABCDE";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',1},{'B','C',1},
	{'C','D',3},{'D','A',2},{'C','E',1},{'E','D',1}};
	int vexnum = 5, arcnum = 6;
	
	MGraph *G1,*G2, *G3, *G4;
	G1 = CreateMGraph(vg,ag,DG,vexnum,arcnum);
	G2 = CreateMGraph(vg,ag,DN,vexnum,arcnum);
	G3 = CreateMGraph(vg,ag,UDG,vexnum,arcnum);
	G4 = CreateMGraph(vg,ag,UDN,vexnum,arcnum);
	
	printf("G1:\n"); DispMGraph(G1); printf("\n");
	printf("G2:\n"); DispMGraph(G2); printf("\n");
	printf("G3:\n"); DispMGraph(G3); printf("\n");
	printf("G4:\n"); DispMGraph(G4); printf("\n");
	
	system("pause");
	return 0;
}
