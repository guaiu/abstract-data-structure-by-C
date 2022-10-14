#include <stdio.h>
#include <stdlib.h>


/******************************************/
/*����һ���������У�ÿ������Ϊ�� ��0��    *
*���ף�1��������2��������ɫ�е�һ�֡���   *
*������� ����˳���洢�����һ��ʱ�临  *
*�Ӷ�ΪO(n)���㷨��ʹ�� ��Щ���鰴�졢�ס�*
*����˳���źã����ųɺ�������ͼ����       */
/******************************************/

#define MaxSize 20

typedef int ElemType;
typedef struct  //˳�������
{
	ElemType data[MaxSize];
	int length;
}SqList;


/*����˳���*/
void CreateList(SqList *&L, ElemType a[], int n)
{
	L = (SqList*)malloc(sizeof(SqList));
	for(int i = 0; i < n; i++)
		L->data[i] = a[i];
	L->length = n;
}

/*���˳���*/
void DispList(SqList *L)
{
	
	if(L->length == 0)
		return ;
	for(int i = 0; i < L->length; i++)
		printf("%d ",L->data[i]);
	printf("\n");
}

/*����˳���*/
void DestroyList(SqList *&L)
{
	free(L);
}

/*Ԫ��ֵ����*/
void swap(ElemType &a1, ElemType &a2)
{
	ElemType temp;
	temp = a1;
	a1 = a2;
	a2 = temp;
}

/*�������������㷨*/
void move1(SqList *&L)
{
	int i = -1, j = 0, k = L->length;  //j���ڱ�����i��������0Ԫ�����䣬k��������2Ԫ������
	while(j < k)
	{
		if(L->data[j] == 0)  //jָ��Ԫ��0��˵��������ǰ����i��1������0Ԫ�����䣩��
		{                    //��i��jλ�õ�Ԫ�ؽ�����j++�� 
			i++;
			swap(L->data[i], L->data[j]);
			j++;
		}
		else if(L->data[j] == 2)  //jָ��Ԫ��2��˵�������ں󲿣�k��1������2Ԫ�����䣩��
		{                         //��j��kλ�õ�Ԫ�� ��������ʱjλ�õ�Ԫ�ؿ��ܻ�Ҫ
			k--;                  //������ǰ��������j��ǰ��
			swap(L->data[k], L->data[j]);
		}
		else j++;  //jָ��Ԫ��1��˵���������в������ֲ�����j++�� 
	}
}

/*����������*/
int main()
{
	ElemType a[12] = {1,0,2,1,0,0,1,2,2,1,0,2};
	int n = 12;
	SqList *L;
	CreateList(L,a,n);
	printf("ԭ��Ϊ��\n");
	DispList(L);
	
	printf("���㷨���к�Ϊ��\n");
	move1(L);
	DispList(L);
	
	DestroyList(L);
	system("pause");
	return 0;
}