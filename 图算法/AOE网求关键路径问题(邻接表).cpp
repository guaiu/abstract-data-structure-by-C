#include <stdio.h>
#include <stdlib.h>

/*****************************/
/*AOE����ؼ�·������(�ڽӱ�)*/
/*****************************/

/*ע��ʹ���±�λ��0����ʹ���±�λ��MAX_VEX_NUM-1*/
//ע��ò���ڱ�һ������λ��0�ģ�������ʹ��MAX_VEX_NUM-1λ�õĲ���̫�淶

#define MAX_VEX_NUM 10
#define MAX_ARC_NUM MAX_VEX_NUM*(MAX_VEX_NUM-1)
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

/*TopSort:��ȡ�������в�����������S�У����޻�·�򷵻�1�����򷵻�0*/
int TopSort(ALGraph *G, int *S)
{
	int i,count,gettop,k;
	ArcNode *p;
	int *stack = (int*)malloc(sizeof(int)*G->vexnum); //����ջ
	int top = -1;
	int *in = (int*)malloc(sizeof(int)*G->vexnum);    //�洢�����������Ϣ,��ʼ��0
	for(i = 0; i < G->vexnum; i++)
		in[i] = 0;
	
	for(i = 0; i < G->vexnum; i++)
	{
		p = G->adjlist[i].firstarc;   //ָ���һ�����ڶ���
		while(p != NULL)
		{
			in[p->adjvex]++;
			p = p->nextarc;
		}
	}
	for(i = 0; i < G->vexnum; i++)
		if(in[i] == 0)
		{
			top++;
			stack[top] = i;  //���Ϊ0�Ķ�����ջ
		}
	
	count = 0;       //������ʼ��
	while(top > -1)  //ջ����ѭ��
	{
		gettop = stack[top];  //��ջ
		top--;
		S[count] = gettop;
		count++;
		p = G->adjlist[gettop].firstarc;
		while(p != NULL)
		{
			k = p->adjvex;
			in[k]--;
			if(in[k] == 0)
			{//������������ջ
				top++;
				stack[top] = k;
			}
			p = p->nextarc;
		}
	}
	free(stack);           //�ͷ��ڴ�ռ�
	free(in);
	
	if(count < G->vexnum)  //�ж��Ƿ��л������ؽ��
		return false;
	return true;
}
/*getweight:DFS1�ĸ���������������������ɵıߵ�Ȩֵ����Ч�򷵻�0*/
int getweight(int a, int b, ALGraph *G)
{
	int weight = 0;
	ArcNode *p;
	p = G->adjlist[a].firstarc;
	while(p != NULL)
	{
		if(p->adjvex == b){
			weight = p->weight;
			return weight;
		}
		p = p->nextarc;
	}
	return 0;
}

/*DFS1:��ȱ�����ؼ�·��*/
void DFS1(int a, int end, int *ee, int *le, ALGraph *G)
//����Ĭ�������������������·��
{
	static int pathnum = 0; //·������
	static int count = 0;   //��ǰ·������
	static int *path = (int*)malloc(sizeof(int)*G->vexnum);
	/*����Ϊ������̬�ֲ�����*/
	
	int i,temp;
	int ev, lv; //����翪ʼʱ��(early activity)�ͻ����ʼʱ��(late activity)
    ArcNode *p;	
	
	if(a == end)  //��ǰ�ڵ���Ϊ�յ���,��ӡ
	{
		pathnum++;
		path[count++] = a;
		printf("THE %dTH PATH:\n",pathnum);
	    for(i = 0; i < count-1; i++)
		    printf("<%c - %c> length: %d\n", G->adjlist[path[i]].data, G->adjlist[path[i+1]].data, getweight(path[i],path[i+1],G));
	}
	
	p = G->adjlist[a].firstarc;
	while(p != NULL)
	{
		ev = ee[a];
		lv = le[p->adjvex] - p->weight;
		if(ev == lv)  //�������ڸ���ʱ�䣬�򱾻Ϊ�ؼ��
		{
		    temp = count;       //����
			path[count++] = a;  //��¼һ������
		    DFS1(p->adjvex,end,ee,le,G);
		    count = temp;       //�ָ�
		}
		p = p->nextarc;
	}
}

/*CriticalPath:��ؼ�·������֪G��AOE�������G�Ĺؼ��*/
void CriticalPath(ALGraph *G)
{
	ArcNode *p;
	int i, j, k;
	int *ee, *le;  
	//�ֱ�Ϊearly event(�¼����翪ʼʱ��)��late event(�¼���ٿ�ʼ�¼�)
	int *S = (int*)malloc(sizeof(int)*G->vexnum);  //������������
	
    TopSort(G,S);             //���������������в�������S��
	printf("the topological sort is...\n");
	for(i = 0; i < G->vexnum; i++)
		printf("%c->",G->adjlist[S[i]].data);
	printf("\n");
	
	//����ee
	ee = (int*)malloc(sizeof(int)*G->vexnum); //��0(Դ��)��ʼ��
	for(i = 0; i < G->vexnum; i++)
		ee[i] = 0;
	for(i = 0; i < G-> vexnum; i++)           //�����������е������ÿ�������ee
	{
		p = G->adjlist[S[i]].firstarc;
		while(p != NULL)
		{
			if((ee[S[i]]+p->weight) > ee[p->adjvex])
				ee[p->adjvex] = ee[S[i]]+p->weight;
			p = p->nextarc;
		}
	}
	
	//����le
	le = (int*)malloc(sizeof(int)*G->vexnum); //��ee[G->vexnum-1](�յ�)��ʼ��
	for(i = 0; i < G->vexnum; i++)
		le[i] = ee[G->vexnum-1];
	for(i = G->vexnum-1; i>= 0; i--)          //�������������е������ÿ�������le
	{
		p = G->adjlist[S[i]].firstarc;
		while(p != NULL)
		{
			if((le[p->adjvex]-p->weight) < le[S[i]])
				le[S[i]] = le[p->adjvex]-p->weight;
			p = p->nextarc;
		}
	}
	
	//�����������һ��·��
	int ev, lv; //����翪ʼʱ��(early activity)�ͻ����ʼʱ��(late activity)
	j = S[0];
	p = G->adjlist[j].firstarc;
	printf("one of the Critical Path is:\n");
	while(p != NULL)
	{
		k = p->adjvex;
		ev = ee[j];
		lv = le[k] - p->weight;
		if(ev == lv){
			printf("<%c - %c> length: %d\n", G->adjlist[j].data, G->adjlist[k].data, p->weight);
			j = k;
			p = G->adjlist[j].firstarc;
			continue;
		}
		p = p->nextarc;
	}
		
	//�����DFS������еĹؼ�·��
	DFS1(S[0],S[G->vexnum-1],ee,le,G);
}


/*������*/
int main()
{
	VexGroup vg[MAX_VEX_NUM] = "ABCDEFGHI";
	ArcGroup ag[MAX_ARC_NUM] = {{'A','B',6},{'A','C',4},
	{'A','D',5},{'B','E',1},{'C','E',1},{'D','H',2},
	{'E','F',9},{'E','G',7},{'F','I',2},{'G','I',4},
	{'H','I',4}};
	int vexnum = 9, arcnum = 11;
	
	ALGraph *G1;
	G1 = CreateALGraph(vg,ag,DN,vexnum,arcnum);
	printf("G1:\n"); DispALGraph(G1); printf("\n");
    
	CriticalPath(G1);
	
	system("pause");
	return 0;
}
