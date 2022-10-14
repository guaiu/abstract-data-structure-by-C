#include <stdio.h>
#include <stdlib.h>

/*********************************/
/*��С������Kruskal�㷨(�ڽӾ���)*/
/*********************************/

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

/*InsertSort:�Ա߼��ϰ�Ȩֵ��������*/
void InsertSort(ArcGroup *E, int k)
{
	int i,j;
	ArcGroup temp;
	for(i = 1; i < k; i++)//���±�1��ʼ
	{
		temp = E[i];
		for(j = i-1; j >= 0 && temp.weight < E[j].weight; j--)
		{
			E[j+1] = E[j];  //���ϴ�Ԫ�غ���
		}
		E[j+1] = temp;      //temp������ȷλ��
	}
}

/*Kruskal:��С�������Ŀ�³˹�����㷨(�ڽӾ���)*/
void Kruskal(MGraph *G)
{
	int i,j;
	int u1,v1,sn1,sn2,k;
	int vset[MAX_VEX_NUM];
	ArcGroup E[MAX_ARC_NUM];        //������б�
	k = 0;                          //��ǰ���ڱߵļ���(�±��0��ʼ)
	for(i = 0; i < G->vexnum; i++)  //��ʼ���߼���(ע�����ĶԳ���)
		for(j = 0; j < G->vexnum; j++)
			if(i >= j && G->arcs[i][j] != 0 && G->arcs[i][j] != INF)
			{//�жԳ��ԣ��ռ����������ǺͶԽ��߾Ϳ�����
				E[k].orinvex = i;
				E[k].adjvex = j;
				E[k].weight = G->arcs[i][j];
				k++;
			}
	InsertSort(E,G->arcnum);               //��ֱ�Ӳ��������E���鰴Ȩֵ��������
	for(i = 0; i < G->vexnum; i++) //��ʼ����������
		vset[i] = i;
	k = 1;    //��ǰ���ڼ��������������ı�
	j = 0;    //��ǰ���ڼ���E�бߵ��±�
	while(k < G->vexnum)//��С��������G->vexnum-1����
	{
		u1 = E[j].orinvex;
		v1 = E[j].adjvex;      //ȡ�ߵĶ���
		sn1 = vset[u1];       
		sn2 = vset[v1];        //ȡ������Ϣ
		if(sn1 != sn2)         //�����������ڲ�ͬ�ļ���
		{
			printf(" ��(%c,%c)ȨΪ:%d\n",G->vexs[u1],G->vexs[v1],E[j].weight);
			k++;  //������һ
			for(i = 0; i < G->vexnum; i++)  //��������ͳһ���
				if(vset[i] == sn2)          //���ϱ��Ϊsn2�ĸ�Ϊsn1
					vset[i] = sn1;
		}
		j++;  //ɨ����һ����
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
	
	Kruskal(G1);

	system("pause");
	return 0;
}