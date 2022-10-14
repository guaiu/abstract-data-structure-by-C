#include <stdio.h>
#include <stdlib.h>

/******************************/
/*采用递归算法求解迷宫问题，  *
 *并输出从入口到 出口的所有迷 *
 *宫路径。                    */
/******************************/

#define MaxSize 16
#define MaxCol 4
int count = 0;     //全局变量，记录路径数量
typedef struct
{
	int i;  //行
	int j;  //列
}Box;

typedef struct
{
	Box data[MaxSize];
	int length;  //路径长度
}PathType;       //定义路径类型

/*mgpath:递归算法求解迷宫问题*/
void mgpath(int xi, int yi, int xe, int ye, PathType path, int (*mg)[MaxCol+2])
//求解路径为:(xi,yi)-->(xe,ye)
{
	int di, k, i, j;
	if(xi == xe && yi == ye)   //(xi,yi)是出口，打印路径
	{
		path.data[path.length].i = xi;
		path.data[path.length].i = yi;
		path.length++;
		printf("迷宫路径%d如下:\n",++count);
		for(k = 0; k < path.length; k++)
		{
			printf("\t(%d,%d)",path.data[k].i,path.data[k].j);
			if((k+1)%5 == 0)
				printf("\n");
		}
		printf("\n");
	}
	else                       //(xi,yi)不是出口    
	{
		if(mg[xi][yi] == 0)
		{
	        di = 0;
			while(di < 4)
			{
				switch(di){
				case 0: i = xi-1; j = yi; break;  //往上走
				case 1: i = xi; j = yi+1; break;  //往右走
				case 2: i = xi+1; j = yi; break;  //往下走
				case 3: i = xi; j = yi-1; break;  //往左走
				}
			    path.data[path.length].i = xi;
		        path.data[path.length].i = yi;
		        path.length++;
			    mg[xi][yi] = -1;              //标记
			    mgpath(i,j,xe,ye,path,mg);
			    path.length--;                //回退
			    mg[xi][yi] = 0;               //还原
			    di++;                         //转向
			}			
		}
	}
}

/*测试主函数*/
int main()
{
	int mg[MaxCol+2][MaxCol+2] = 
	{ {1, 1, 1, 1, 1, 1},
      {1, 0, 0, 0, 1, 1},
      {1, 0, 1, 0, 0, 1},
      {1, 0, 0, 0, 1 ,1},
      {1, 1, 0, 0, 0, 1},
      {1, 1, 1, 1, 1, 1} };
	
	PathType path;
	path.length = 0;  //初始化
	mgpath(1,1,4,4,path,mg);
	system("pause");
	return 0;
}