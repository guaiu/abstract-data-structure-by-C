#include <stdio.h>

/*********************************************/
/*���õݹ��㷨��ʵ������A[0..n-1]�е���Сֵ��*/
/*********************************************/

#define MaxSize 10

double GetMin(double arr[], int i)
{
	double m;
	if(i == 0)
		return arr[0];
	else
	{
		m = GetMin(arr,i-1);
		if(m > arr[i])
			return arr[i];
		else
			return m;
	}
}

int main()
{
	double arr[MaxSize];
	for(int k = 0; k < MaxSize; k++)
		scanf("%lf",&arr[k]);
	printf("��С��Ϊ%.2lf",GetMin(arr,MaxSize-1));
	return 0;
}
