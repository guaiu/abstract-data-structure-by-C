#include <stdio.h>

/********************/
/*�ݹ���ȫ��������*/
/********************/

/*������������ֵ*/
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

/*perm:�ݹ���ȫ��������*/
void perm(int a[], int n, int k)
{
	int i, j;
	if(k == 0)
	{
		for(j = 0; j < n; j++)
			printf("%d",a[j]);
		printf("\n");
	}
	else
	{
		for(i = 0; i <= k; i++)
		{
			swap(a[k],a[i]);
			perm(a,n,k-1);
			swap(a[k],a[i]);
		}
	}
}

/*���Ժ���*/
int main()
{
	int n = 4, k = 3;
	int a[] = {1,2,3,4};
	perm(a,n,k);
	return 0;
}