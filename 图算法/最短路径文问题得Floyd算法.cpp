#include <stdio.h>
#include <stdlib.h>

/***************************/
/*���·���������Floyd�㷨*/
/***************************/

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

/*DispPath:��ӡ��Ԫ���·��*/
void DispPath(MGraph *G, int A[][MAX_VEX_NUM], int path[][MAX_VEX_NUM])
{
	int i,j;
	int u;
	int stack[MAX_VEX_NUM];
	int top  = -1; //����ջ
	for(i = 0; i < G->vexnum; i++)
	{
        for(j = 0; j < G->vexnum; j++)
		{
			if(path[i][j] == -1)
				printf("%c��%cû��·��\n",G->vexs[i],G->vexs[j]);
			else//path[i][j] != -1
			{
				printf("%c��%c�����·��Ϊ",G->vexs[i],G->vexs[j]);
				top++;
				stack[top] = path[i][j];
				while(stack[top] != i)
				{
					u = path[i][stack[top]];
					top++;
					stack[top] = u;
				}
				while(top > -1)
				{
					printf("%c->",G->vexs[stack[top]]);
					top--;
				}
				printf("%c",G->vexs[j]);
				printf(", ·������Ϊ%d\n",A[i][j]);
			}	
		}
	    printf("--------------------------------------------\n");
	}
}

/*Floyd:���·������ø��������㷨*/
void Floyd(MGraph *G)
{
	int A[MAX_VEX_NUM][MAX_VEX_NUM];     //����A����
	int path[MAX_VEX_NUM][MAX_VEX_NUM];  //����path����
	int i,j,k;
	for(i = 0; i < G->vexnum; i++)//��ʼ��A(-1)��path(-1)
	    for(j = 0; j < G->vexnum; j++)
		{
			A[i][j] = G->arcs[i][j];
			if(i != j && G->arcs[i][j] < INF)
				path[i][j] = i;    //i��j�����б�
			else
				path[i][j] = -1;   //i��j����û�б�
		}
	for(k = 0; k < G->vexnum; k++) //�����㷨��A(k)��path(k)
		for(i = 0; i < G->vexnum; i++)
			for(j = 0; j < G->vexnum; j++)
				if(A[i][j] > A[i][k] + A[k][j])  //���ҵ��˸��̵�·��
			    {
					A[i][j] = A[i][k] + A[k][j]; //�޸�·������
					path[i][j] = path[k][j];     //�޸����·��Ϊ��������k
				}
	DispPath(G,A,path);
}

/*������*/
int main()
{
	VexGroup vg[MAX_VEX_NUM] = "0123";
	ArcGroup ag[MAX_ARC_NUM] = {{'0','1',5},{'0','3',7},
	{'1','2',4},{'1','3',2},{'2','0',3},{'2','1',3},
	{'2','3',2},{'3','2',1}};
	int vexnum = 4, arcnum = 8;
	
	MGraph *G1;
	G1 = CreateMGraph(vg,ag,DN,vexnum,arcnum);
	printf("G1:\n"); DispMGraph(G1); printf("\n");
	
	Floyd(G1);
	
	system("pause");
	return 0;
}