#include <stdio.h>

/************/
/*汉诺塔问题*/
/************/

void swap(int n, char a, char b, char c)   //a起点，b终点，中转
{
	if(n == 1)
		printf("%c->%d->%c\n",a,n,c);
	else
	{
		swap(n-1,a,c,b);
		printf("%c->%d->%c\n",a,n,c);
		swap(n-1,c,a,b);
	}
}

int main()
{
	int n = 1;
	char a = '\0', b = '\0', c = '\0';
	scanf("%d %c %c %c",&n, &a, &b, &c);
	swap(n,a,b,c);
	return 0;
}