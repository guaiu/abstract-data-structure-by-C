#include <stdio.h>
#include <stdlib.h>

/**********************************************/
/*������������֪����Ϊn�����Ա�A����˳��洢��*
 *������� һ��ʱ�临�Ӷ�ΪO(n)���ռ临�Ӷ�   *
 *ΪO(1)���㷨�����㷨ɾ�����Ա�������ֵΪx��*
 *����Ԫ�ء�                                  */
 /*********************************************/
 
#define MaxSize 20
typedef int ElemType;
typedef struct  //˳�����������
{
	ElemType data[MaxSize];
	int length;
}Sqlist;

/* CreateList:����˳��� */
void CreateList(Sqlist *&L, ElemType a[], int n)
{
	int i;
	L = (Sqlist*)malloc(sizeof(Sqlist));
	for(i = 0; i < n; i++)
		L->data[i] = a[i];
	
	L->length = n;
}

/* DestroyList:����˳��� */
void DestroyList(Sqlist *&L)
{
	free(L);
}

/* ListEmpty:�ж��Ƿ�Ϊ�ձ����򷵻��� */
bool ListEmpty(Sqlist *L)
{
	return (L->length == 0);
}

/* DispList:��˳���Ϊ�գ����˳��� */
void DispList(Sqlist *L)
{
	int i;
	if(ListEmpty(L))
		return ;
	else
		for(i = 0; i < L->length; i++)
			printf("%d",L->data[i]);  //������޸�������
	printf("\n");
}

/* delnode1:�㷨һ�� ɨ��˳���A���ؽ�Aֻ����������x��Ԫ�ء�*/
void delnode1(Sqlist *&L, ElemType x)
{
	int k = 0, i;
	for(i = 0; i < L->length; i++)
		if(L->data[i] != x)
		{
			L->data[k] = L->data[i];
			k++;
		}
	L->length = k;
}

/* delnode2:�㷨��������Ϊx��Ԫ��ǰ��k��λ�ã�����޸�A�ĳ��ȡ�*/
void delnode2(Sqlist *&L, ElemType x)
{
	int k = 0, i;
	for(i = 0; i < L->length; i++)
	{
		if(L->data[i] == x)
			k++;
		else
			L->data[i-k] = L->data[i];
	}
	L->length -= k;
}

int main()
{
	int n = 0;
	ElemType a[MaxSize];
	printf("��������Ԫ�صĳ��ȣ�Ȼ�������������鳤�ȵ�ֵ��\n");
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);  //������޸�������
	
	ElemType x;
    printf("����Ҫɾ����ֵ��\n");
	scanf("%d",&x); //������޸�������
	
	printf("\n\n\n�㷨һִ�еĽ����\n");
	Sqlist *L1;
	CreateList(L1,a,n);
	delnode1(L1,x);
	DispList(L1);
	DestroyList(L1);
	L1 = NULL;
	
	printf("\n\n\n�㷨��ִ�еĽ����\n");
    Sqlist *L2;
	CreateList(L2,a,n);
	delnode2(L2,x);
	DispList(L2);
	DestroyList(L2);
	L2 = NULL;
	
	return 0;
}
















