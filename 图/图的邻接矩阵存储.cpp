#include <stdio.h>
#include <stdlib.h>

/**********************/
/*ͼ���ڽӾ���洢����*/
/**********************/

/*ע�������빹�����ڽӾ����0�к͵�0�����ã���˲�����һ��ͨ�õ��ڽӾ���*/

#define MAX_VEX_NUM 50
typedef enum
{
	DG, DN, UDG, UDN  //�ֱ�Ϊ����ͼ��������������ͼ��������
}GraphType;
typedef char VertexType;
typedef struct
{
	VertexType vexs[MAX_VEX_NUM];       //������Ϣ���涨0λ�ò�ʹ�á�
	int arcs[MAX_VEX_NUM][MAX_VEX_NUM]; //�ڽӾ���
	int vexnum, arcnum;                 //ͼ�Ķ������ͻ���
	GraphType type;                     //ͼ�������־
}MGraph;

/*GetIndexOfVexs:�������Ƶõ�ָ�������ڶ��㼯���е��±�*/
/*ע:Ϊ�˽�ȫ�Կ����±�0λ�ò�ʹ�ã������ڲ��Ҳ���Ŀ�궥
��ʱ������ֵ*/
int GetIndexOfVexs(char vex, MGraph *MG)
{
	int i;
	for(i = 1; i <= MG->vexnum; i++)
	{
		if(MG->vexs[i] == vex)
			return i;
			
	}
	return 0;
}

/*CreateMGraph:�����ڽӾ���*/
/*ע:Ϊ�˼�㣬���ｫֱ�Ӱ��������û��������ݵĴ��룬���������⽫
���㼯�Ϻͻ�������Ϊ��������*/
void CreateMGraph(MGraph *&MG)
{
	int i, j, k;
	int v1, v2, type, weight;
	char c1, c2;
	MG = (MGraph*)malloc(sizeof(MGraph));  //�����ڴ�ռ�
	printf("Please input grapg type DG(0) or DN(1) or UDG(2) or UDN(3):");
	scanf("%d",&type);
	switch(type)
	{
		case 0: MG->type = DG; break;
		case 1: MG->type = DN; break;
		case 2: MG->type = UDG; break;
		case 3: MG->type = UDN; break;
		default:{
		printf("Please input correct graph type DG(0) or DN(1) or UDG(2) or UDN(3)!\n");
		free(MG); MG = NULL;
		return ;
		}
	}
	printf("Please input vexnum:");
	scanf("%d",&MG->vexnum);
	printf("Please input arcnum:");
	scanf("%d",&MG->arcnum);
	getchar();
	for(i = 1; i <= MG->vexnum; i++)
	{//�±��1��ʼ
		printf("Please input %dth vex(char):",i);
		scanf("%c",&MG->vexs[i]);
		getchar();
	}
	//��ʼ���ڽӾ���
	for(i = 1; i <= MG->vexnum; i++)
	{
		for(j = 1; j <= MG->vexnum; j++)
		{
			if(MG->type == DN || MG->type == UDN)
			{//��Ϊ��Ȩͼ��i==jʱ��ʼ��Ϊ-1�����������ʼ��Ϊ0
		        if(i == j)
			        MG->arcs[i][j] = -1;
				else
					MG->arcs[i][j] = 0;
			}
			else
			{
				MG->arcs[i][j] = 0;
			}
		}
	}
	//����ߵ���Ϣ�������ڽӾ���
	for(k = 1; k <= MG->arcnum; k++)
	{
		printf("Please input %dth arc v1(char) v2(char)",k);
		scanf("%c %c",&c1, &c2);
		getchar();
		if(MG->type == DN || MG->type == UDN)
		{
			printf("Please input the weight:");
			scanf("%d",&weight);
			getchar();
		}
		else
		{
			weight = 1;
		}
		v1 = GetIndexOfVexs(c1,MG);
		v2 = GetIndexOfVexs(c2,MG);
		if(MG->type == UDG || MG->type == UDN)
		{//����ͼ�����������жԳ���
			MG->arcs[v1][v2] = MG->arcs[v2][v1] = weight;
		}
		else
		{
			MG->arcs[v1][v2] = weight;
		}
	}
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
	for(i = 1; i <= MG->vexnum; i++)
	{
		printf("%c",MG->vexs[i]);
	}
	printf("\nAdjacency Matrix:\n");
	for(i = 1; i <= MG->vexnum; i++)
	{
		for(j = 1; j <= MG->vexnum; j++)
		{
			printf("\t%2d",MG->arcs[i][j]);
		}
		printf("\n");
	}
}

/*������*/
int main()
{
	MGraph *MG=NULL;
	CreateMGraph(MG);
	DispMGraph(MG);
	system("pause");
	return 0;
}