#include <stdio.h>

/******************/
/*求解斐波那契数列*/
/******************/

int fun(int n)
{
	return (n<3)?(1):(fun(n-1)+fun(n-2));
}

int main()
{
	int n = 1;
	scanf("%d",&n);
	printf("第%d个斐波那契数为%d",n,fun(n));
	return 0;
}