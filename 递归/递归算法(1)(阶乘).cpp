#include <stdio.h>

/********/
/*��׳�*/
/********/

int fun(int n)
{
	if(n == 1)                   //�ݹ����
		return 1;
	else
		return n*fun(n-1);       //�ݹ���
}

int main()
{
	int n = 1;
	scanf("%d",&n);
	printf("%d�Ľ׳���%d",n,fun(n));
	return 0;
}