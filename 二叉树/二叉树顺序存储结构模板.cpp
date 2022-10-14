#include <stdio.h>
#include <stdlib.h>

/********************/
/*������˳��洢�ṹ*/
/********************/

#define MaxSize 100
typedef char ElemType;
typedef struct
{
	ElemType data[MaxSize];
	//�涨���ڵ�Ϊ�±�Ϊ1��0��Ԫ����Ϊ'\0'
}BTNode;

/*CreateBTNode:˳�򴴽�������*/
void CreateBTNode(BTNode *&b, ElemType *str)
{//����ʾ����A(B(D(,G)),C(E,F))
    int St[MaxSize], p = 1;           //StΪָ��ջ��pΪ��ǰɨ��Ԫ��ָ�룬��ʼֵΪ1
	int top = -1, j = 0;              //j���ڱ����ַ���
	ElemType ch;
	b = (BTNode*)malloc(sizeof(BTNode));
	b->data[1] = '#'; 
	b->data[0] = '\0';  //��ʼ��
	ch = str[j];
	while(ch != '\0'){                 //ѭ��ɨ��
		switch(ch)
		{
			case'(': top++; St[top] = p; p *= 2; break;   //���������ӣ���ջ��pָ������
			case')': p = St[top]; top--; break;           //������ջ��Ԫ�ؿ��ܵ����Һ��ӣ���ջ��pָ�����
			case',': p++; break;                          //pָ���Һ���
			default:{//�����ڵ�ֵ
			    b->data[p*2] = '#';        //pԪ�������ÿ�
				b->data[p*2+1] = '#';      //pԪ���Һ����ÿ�
			    b->data[p] = ch;           //pԪ�ؽ���ch��ֵ
			}
		}
		j++; ch = str[j];    //����ɨ��str
	}
}

/*DestroyBT:���ٶ�����*/
void DestroyBT(BTNode *&b)
{
	free(b);
}

/*FindNode:���ҽڵ��ַ*/
int FindNode(BTNode *b, ElemType x, int p)  //pΪ��ǰ�鿴Ԫ�ص�ַ
{
	int k;
	if(b->data[p] == '#')
		return 0;
	else if(b->data[p] == x)
		return p;
	else
	{
		k = FindNode(b,x,p*2);  //�ȴ���������
		if(k != 0)                      //�ҵ���
			return k;
		else                            //�ٴ���������
			return FindNode(b,x,p*2+1);
	}
}

/*LchildNode:�������ӵ�ַ*/
int LchildNode(int p)
{return p*2;}

/*RchildNode:�������ӵ�ַ*/
int RchildNode(int p)
{return p*2+1;}

/*BTNodeDepth:��������߶�*/
int BTNodeDepth(BTNode *b,int p)  //pΪ��ǰ�鿴Ԫ�ص�ַ
{
	int lchilddep, rchilddep;
	if(b->data[p] == '#') return 0;  //�����߶�Ϊ0
	else
	{
		lchilddep = BTNodeDepth(b,p*2);
		                        //���������߶�
		rchilddep = BTNodeDepth(b,p*2+1);
		                        //���������߶�
		return (lchilddep > rchilddep)?(lchilddep+1):(rchilddep+1);
		                        //������������߶�+1
	}
}

/*DispBTNode:���������*/
void DispBTNode(BTNode *b, int p)  //pΪ��ǰ�鿴Ԫ�ص�ַ
{//���ʾ����A(B(D(,G)),C(E,F))
	if(b->data[p] != '#')
	{
		printf("%c",b->data[p]);
		if(b->data[p*2] != '#' || b->data[p*2+1] != '#')
		{
			printf("(");
			DispBTNode(b, p*2);  //�ݹ鴦��������
			if(b->data[p*2+1] != '#') printf(",");
			DispBTNode(b,p*2+1);  //�ݹ鴦��������
			printf(")");
		}
	}
}

/*����������*/
int main()
{
	ElemType str[20] = "A(B(D(,G)),C(E,F))" , x;
	BTNode *b;
	int p,a;
	CreateBTNode(b,str);
	
	printf("����һ���߶�Ϊ%d�Ķ�����\n",BTNodeDepth(b,1));
	printf("�����ݸö�������ӡԭ�ַ���Ϊ��\n");
	DispBTNode(b,1);
	printf("\n");
	
	printf("����Ԫ��x\n");
	for(int i = 0; i < 8; i++){
	scanf("%c",&x);
	getchar();
	if((p = FindNode(b,x,1)) != 0)
	{
	    printf("Ԫ��%c�����Һ����ǣ�\n",x);
	    if((a = LchildNode(p)) != 0)
		    printf("��%c\n",b->data[a]);
	    else
		    printf("����Ϊ��\n");
	    if((a = RchildNode(p)) != 0)
		    printf("�ң�%c\n",b->data[a]);
	    else
		    printf("�Һ���Ϊ��\n");
	}
	else
		printf("�����ڸ�Ԫ��\n");
    }
	
	
	DestroyBT(b);
	system("pause");
	return 0;
}