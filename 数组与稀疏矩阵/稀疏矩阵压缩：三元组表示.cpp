#include <stdio.h>
#include <stdlib.h>

/**************************/
/*ϡ�����ѹ������Ԫ���ʾ*/
/**************************/

#define MaxSize 100
#define M 6
#define N 5
typedef int ElemType;
typedef struct
{
	int r;        //�к�
	int c;        //�к�
	ElemType d;   //Ԫ��ֵ
}TupNode;         //��Ԫ�鶨��

typedef struct
{
	int rows;     //����ֵ
	int cols;     //����ֵ
	int nums;     //����Ԫ�ظ���
	TupNode data[MaxSize];
}TSMatrix;        //��Ԫ��˳�����

/*CreatMat:ϡ������ѹ���㷨(������)*/
void CreatMat(TSMatrix &t, ElemType A[M][N])
{
	int i,j;
	t.rows = M; t.cols = N; t.nums = 0;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < N; j++)
			if(A[i][j] != 0)
			{
				t.data[t.nums].r = i;
				t.data[t.nums].c = j;
				t.data[t.nums].d = A[i][j];
				t.nums++;
			}
	}
}

/*Value:�޸�ԭ����A[i][j]��ֵΪx*/
bool Value(TSMatrix &t, int i, int j, ElemType x)
{
	int k = 0, k1;
	if(i < 0 || i > t.rows-1 || j < 0 || j > t.cols-1)
		return false;
	while(k < t.nums && i > t.data[k].r) k++;  //������
	while(k < t.nums && i== t.data[k].r && j > t.data[k].c)
		k++;                                   //������
	
	if(t.data[k].r == i && t.data[k].c == j)   //����������Ԫ��
	    t.data[k].d = x;
	else                 //������������Ԫ��ʱ����һ��Ԫ��
	{
		for(k1 = t.nums-1; k1 > k; k1--)
			t.data[k1+1] = t.data[k1];
		
		t.data[k].r = i; t.data[k].c = j; t.data[k].d = x;
		t.nums++;
	}
	return true;
}

/*Assign:��ԭ����A[i][j]��ֵ����x*/
bool Assign(TSMatrix t, int i, int j, ElemType &x)
{
	int k = 0;
	if(i < 0 || i > t.rows-1 || j < 0 || j > t.cols-1)
		return false;
	while(k < t.nums && i > t.data[k].r) k++;  //������
	while(k < t.nums && i== t.data[k].r && j > t.data[k].c)
		k++;                                   //������
	
	if(t.data[k].r == i && t.data[k].c == j)   //����������Ԫ��
	    x = t.data[k].d;
	else                                       //û���ҵ���Ϊ0
		x = 0;
	return true;
}

/*DispMat:�����Ԫ��*/
void DispMat(TSMatrix t)
{
	int i;
	if(t.nums <= 0)
		return;
	printf("\t%d\t%d\t%d\n",t.rows,t.cols,t.nums);
	printf("-------------------------\n");
	for(i = 0; i < t.nums; i++)
		printf("\t%d\t%d\t%d\n",t.data[i].r, t.data[i].c, t.data[i].d);
}

/*DispArr:������Ԫ�����ԭ����*/
void DispArr(TSMatrix t)
{
	if(t.nums <= 0)
		return;
	
	int k = 0;
	for(int i = 0; i < t.rows; i++)
	{
		while(k < t.nums && i > t.data[k].r) k++;  //�ƶ���
		for(int j = 0; j < t.cols; j++)
		{
			while(k < t.nums && i == t.data[k].r && j > t.data[k].c)
				k++;                               //�ƶ���
			if(t.data[k].r == i && t.data[k].c == j)
				printf("\t%d",t.data[k].d);
			else
				printf("\t%d",0);				
		}
		printf("\n");
	}
}

/*����������*/
int main()
{
	ElemType A[M][N] = {
		{ 0, 1, 0, 0, 0},
		{ 0, 2, 0, 0, 0},
		{ 0, 0, 0, 0, 0},
		{ 0, 0, 3, 4, 5},
		{ 0, 0, 0, 0, 0},
		{ 6, 0, 0, 7, 0}
	};
	TSMatrix t;
	CreatMat(t,A);
	
	printf("ѹ������Ϊ��\n");
	DispMat(t);
	printf("\nԭ�������ѹ�����黹ԭΪ��\n");
	DispArr(t);
	
	ElemType x;
	int i,j;
	printf("�����±�i,j��\n");
	scanf("%d %d",&i,&j);
	if(Assign(t,i,j,x))
	    printf("A[%d][%d]Ϊ��%d\n",i,j,x);
	else
		printf("Error,��ȡʧ��\n");
	
	printf("�����±�i,j��ֵx��\n");
	scanf("%d %d %d",&i,&j,&x);
	if(Value(t,i,j,x))
	    printf("A[%d][%d]����Ϊ��%d\n",i,j,x);
	else
		printf("Error,�޸�ʧ��\n");
	printf("ѹ������Ϊ��\n");
	DispMat(t);
	printf("\n�޸ĺ�������ѹ�����黹ԭΪ��\n");
	DispArr(t);
	
	system("pause");
	return 0;
}