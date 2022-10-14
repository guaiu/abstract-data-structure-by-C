#include <stdio.h>

/********/
/*求阶乘*/
/********/

int fun(int n)
{
	if(n == 1)                   //递归出口
		return 1;
	else
		return n*fun(n-1);       //递归体
}

int main()
{
	int n = 1;
	scanf("%d",&n);
	printf("%d的阶乘是%d",n,fun(n));
	return 0;
}