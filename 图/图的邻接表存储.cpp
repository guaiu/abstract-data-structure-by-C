#include <stdio.h>
#include <stdlib.h>

/********************/
/*ͼ���ڽӱ�洢����*/
/********************/

/*��ͨ�ñ������±�λ��0*/

#define MAX_VEX_NUM 20
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

/*GetIndexOfAdjlist:�������Ƶõ�ָ�������ڶ��㼯���е��±�*/
/*ע:Ϊ�˽�ȫ�Կ����±�0λ�ò�ʹ�ã������ڲ��Ҳ���Ŀ�궥
��ʱ������ֵ*/
int GetIndexOfAdjlist(char vex, ALGraph *G)
{
	int i;
	for(i = 1; i <= G->vexnum; i++)
	{
		if(G->adjlist[i].data == vex)
			return i;
			
	}
	return 0;
}

/*CreateALGraph:�����ڽӱ�*/
/*ע:Ϊ�˼�㣬���ｫֱ�Ӱ��������û��������ݵĴ��룬���������⽫
���㼯�Ϻͻ�������Ϊ��������*/
void CreateALGraph(ALGraph *&G)
{
	int i;
	int v1, v2, type, weight;
	char c1, c2;
	G = (ALGraph*)malloc(sizeof(ALGraph));  //�����ڴ�ռ�
	ArcNode *arc;
	printf("Please input grapg type DG(0) or DN(1) or UDG(2) or UDN(3):");
	scanf("%d",&type);
	switch(type)
	{
		case 0: G->type = DG; break;
		case 1: G->type = DN; break;
		case 2: G->type = UDG; break;
		case 3: G->type = UDN; break;
		default:{
		printf("Please input correct graph type DG(0) or DN(1) or UDG(2) or UDN(3)!\n");
        free(G); G = NULL;
		return ;
		}
	}
	printf("Please input vexnum:");
	scanf("%d",&G->vexnum);
	printf("Please input arcnum:");
	scanf("%d",&G->arcnum);
	getchar();
	//��ʼ������
	for(i = 1; i <= G->vexnum; i++){//��ʼ������
		G->adjlist[i].firstarc = NULL;
	}
	//���붥����Ϣ
	for(i = 1; i <= G->vexnum; i++)
	{//�±��1��ʼ
		printf("Please input %dth vex(char):",i);
		scanf("%c",&G->adjlist[i].data);
		getchar();
	}
	//����ߵ���Ϣ�������ڽӱ�
	for(i = 1; i <= G->arcnum; i++)
	{
		printf("Please input %dth arc v1(char) v2(char)",i);
		scanf("%c %c",&c1, &c2);
		getchar();
		v1 = GetIndexOfAdjlist(c1,G);
		v2 = GetIndexOfAdjlist(c2,G);
		if(v1 == 0 || v2 == 0 || v1 == v2)
		{//��������󶥵���Ϣ(���������ִ���)
			printf("Please input correct vex data!\n");
			free(G); G = NULL;
		    return ;
		}
		
		if(G->type == DN || G->type == UDN)
		{
			printf("Please input the weight:");
			scanf("%d",&weight);
			getchar();
		}
		else
		{//��Ȩ��ͳһ��Ϊ1
			weight = 1;
		}
		
		arc = (ArcNode*)malloc(sizeof(ArcNode));
		arc->adjvex = v2;
		arc->weight = weight;
		arc->nextarc = G->adjlist[v1].firstarc;
		G->adjlist[v1].firstarc = arc;
		if(G->type == UDG || G->type == UDN){//��Ϊ����ͼ
			arc = (ArcNode*)malloc(sizeof(ArcNode));
		    arc->adjvex = v1;
		    arc->weight = weight;
		    arc->nextarc = G->adjlist[v2].firstarc;
		    G->adjlist[v2].firstarc = arc;
		}
	}
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
	for(i = 1; i <= G->vexnum; i++){
		printf("%c",G->adjlist[i].data);
	}
	printf("\nAdjacency List:\n");
	for(i = 1; i <= G->vexnum; i++)
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

/*������*/
int main()
{
	ALGraph *G=NULL;
	CreateALGraph(G);
	DispALGraph(G);
	system("pause");
	return 0;
}