#include <stdio.h>

/******************/
/*���쳲���������*/
/******************/

int fun(int n)
{
	return (n<3)?(1):(fun(n-1)+fun(n-2));
}

int main()
{
	int n = 1;
	scanf("%d",&n);
	printf("��%d��쳲�������Ϊ%d",n,fun(n));
	return 0;
}