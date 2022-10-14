#include <stdio.h>

/*********************************************/
/*采用递归算法求实数数组A[0..n-1]中的最小值。*/
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
	printf("最小数为%.2lf",GetMin(arr,MaxSize-1));
	return 0;
}
