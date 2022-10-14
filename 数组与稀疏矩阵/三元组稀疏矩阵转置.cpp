#include <stdio.h>
#include <stdlib.h>

/********************/
/*��Ԫ��ϡ�����ת��*/
/********************/

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

/*TranTat:����ת��*/
void TranTat(TSMatrix t, TSMatrix &tb)
{
	int p, q = 0, v;
	tb.rows = t.cols; tb.cols = t.rows; tb.nums = t.nums;
	if(t.nums != 0)
	{
		for(v = 0; v < t.cols; v++)        //tb.data[q]������������
			for(p = 0; p < t.nums; p++)    //pΪt.data���±�
			    if(t.data[p].c == v)
				{
					tb.data[q].r = t.data[p].c;
					tb.data[q].c = t.data[p].r;
					tb.data[q].d = t.data[p].d;
					q++;
				}
	}
}

/*���Ժ���*/
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
	
	TSMatrix tb;
	TranTat(t,tb);
	printf("ת������Ϊ��\n");
	DispMat(tb);
	printf("\nת�þ������ѹ�����黹ԭΪ��\n");
	DispArr(tb);
	
	system("pause");
	return 0;
}