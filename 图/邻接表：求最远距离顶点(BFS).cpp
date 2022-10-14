#include <stdio.h>
#include <stdlib.h>

/***********************************/
/*��ȱ����㷨��Ӧ��:����Զ���붥��*/
/***********************************/

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

typedef struct
{
	int data;   //������
	int parent; //ǰһ�������λ��
}QUERE;  //��ѭ����������

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

/*BFS:�ڽӱ�Ĺ�ȱ����㷨*/
void BFS(ALGraph *G, int v)
{//vΪ�����
	ArcNode *p;
	int w, i;
	int queue[MAX_VEX_NUM], front = 0, rear = 0;  //�������
	int visited[MAX_VEX_NUM];                     //������飬��ȱ�������Ҫȫ������
    for(i = 0; i < MAX_VEX_NUM; i++)
		visited[i] = 0;
	printf("%c ",G->adjlist[v].data);             //��ӡ�׶�����Ϣ
	visited[v] = 1;
	rear++;
	queue[rear] = v;
	while(front != rear)  //���в�Ϊ��ʱѭ��
	{
		front++;
		w = queue[front];            //���� 
		p = G->adjlist[w].firstarc;  //��w�ĵ�һ���ڽӵ�
		while(p != NULL)
		{
			if(visited[p->adjvex] == 0)
			{
				printf("%c ",G->adjlist[p->adjvex].data);  //����֮
				visited[p->adjvex] = 1;
				rear++;                                    //���ڶ������
				queue[rear] = p->adjvex;
			}
			p = p->nextarc;                                //����һ���ڽӽڵ�
		}
	} 
}

/*Maxdist:��������ͨͼG���붥��v��Զ��һ������*/
int Maxdist(ALGraph *G, int v)
{
	ArcNode *p;
	int Qu[MAX_VEX_NUM], front = 0, rear = 0;  //���м���ͷ����βָ��
	int visited[MAX_VEX_NUM], i, j, k;
	for(i = 0; i < G->vexnum; i++)
		visited[i] = 0;
	rear++; Qu[rear] = v;       //����v����
	visited[v] = 1;             //���v�ѷ���
	while(rear != front)        //�Ӳ���ѭ��
	{
		front++;
		k = Qu[front];               //�������
		p = G->adjlist[k].firstarc;  //�ҵ�һ���ڽӵ�
		while(p != NULL)             //���η���
		{
			j = p->adjvex;
			if(visited[j] == 0)      //��jδ����
			{
				visited[j] = 1;      //j����
				rear++;
				Qu[rear] = j;
			}
			p = p->nextarc;             //����һ���ڽӵ�
		}
	}
	return k;
}

/*������*/
int main()
{
	//��ʼ��������
	VexGroup vg[MAX_VEX_NUM] = "ABCDEF";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',1},{'A','C',1},
	{'B','D',1},{'B','F',1},{'F','E',1}};
	int vexnum = 6, arcnum = 5;
	ALGraph *G1;
	G1 = CreateALGraph(vg,ag,UDG,vexnum,arcnum);
	printf("G1:\n"); DispALGraph(G1); printf("\n");
	printf("BFS:"); BFS(G1,0); printf("\n");
	
	printf("��A��Զ�ĵ���%c\n",G1->adjlist[Maxdist(G1,0)].data);
	
	system("pause");
	return 0;
}