#include <stdio.h>
#include <stdlib.h>

/******************************/
/*��С������Prim�㷨(�ڽӾ���)*/
/******************************/

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

/*Prim:��С������������ķ�㷨*/
void Prim(MGraph *G, int v)
{
	int lowcost[MAX_VEX_NUM];      //���V-U�����㵽U���ϵ���С�ߵ�Ȩֵ
	int min;
	int closest[MAX_VEX_NUM];      //���V-U�����㵽U���ϵ���С��,
	                               //λ�ñ�ű�ʾ����С����V-U�еĶ�����,
								   //closest[]��ʾ�ñ���U�еĶ�����
	//����,(G->vexs[j]��closest[j])�Ƕ���j������U����С�ߣ�ȨֵΪlowcost[j]
	int i,j,k;
	for(i = 0; i < G->vexnum; i++)
	{//��lowcost[]��closest[]�ó�ֵ
        lowcost[i] = G->arcs[v][i];
		closest[i] = v;
	}
	for(i = 1; i < G->vexnum; i++)     //���vexnum-1����
	{
		min = INF;
		for(j = 0; j < G->vexnum; j++) //��(V-U)���ҳ���U����Ķ���k
		    if(lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;            //k��¼���������
			}
		printf(" ��(%c,%c)ȨΪ:%d\n",G->vexs[closest[k]],G->vexs[k],min);
		lowcost[k] = 0;    //���k�Ѿ�����U,��k����U����СȨֵΪ0
		for(j = 0; j < G->vexnum; j++) //������U�����޸�����lowcost��closest
		    if(lowcost[j] != 0 && G->arcs[k][j] < lowcost[j])
			{
				lowcost[j] = G->arcs[k][j];
				closest[j] = k;
			}
	}
}

/*������*/
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
	
	Prim(G1,0);

	system("pause");
	return 0;
}