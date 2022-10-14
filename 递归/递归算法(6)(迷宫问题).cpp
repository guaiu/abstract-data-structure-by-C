#include <stdio.h>
#include <stdlib.h>

/******************************/
/*���õݹ��㷨����Թ����⣬  *
 *���������ڵ� ���ڵ������� *
 *��·����                    */
/******************************/

#define MaxSize 16
#define MaxCol 4
int count = 0;     //ȫ�ֱ�������¼·������
typedef struct
{
	int i;  //��
	int j;  //��
}Box;

typedef struct
{
	Box data[MaxSize];
	int length;  //·������
}PathType;       //����·������

/*mgpath:�ݹ��㷨����Թ�����*/
void mgpath(int xi, int yi, int xe, int ye, PathType path, int (*mg)[MaxCol+2])
//���·��Ϊ:(xi,yi)-->(xe,ye)
{
	int di, k, i, j;
	if(xi == xe && yi == ye)   //(xi,yi)�ǳ��ڣ���ӡ·��
	{
		path.data[path.length].i = xi;
		path.data[path.length].i = yi;
		path.length++;
		printf("�Թ�·��%d����:\n",++count);
		for(k = 0; k < path.length; k++)
		{
			printf("\t(%d,%d)",path.data[k].i,path.data[k].j);
			if((k+1)%5 == 0)
				printf("\n");
		}
		printf("\n");
	}
	else                       //(xi,yi)���ǳ���    
	{
		if(mg[xi][yi] == 0)
		{
	        di = 0;
			while(di < 4)
			{
				switch(di){
				case 0: i = xi-1; j = yi; break;  //������
				case 1: i = xi; j = yi+1; break;  //������
				case 2: i = xi+1; j = yi; break;  //������
				case 3: i = xi; j = yi-1; break;  //������
				}
			    path.data[path.length].i = xi;
		        path.data[path.length].i = yi;
		        path.length++;
			    mg[xi][yi] = -1;              //���
			    mgpath(i,j,xe,ye,path,mg);
			    path.length--;                //����
			    mg[xi][yi] = 0;               //��ԭ
			    di++;                         //ת��
			}			
		}
	}
}

/*����������*/
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
	path.length = 0;  //��ʼ��
	mgpath(1,1,4,4,path,mg);
	system("pause");
	return 0;
}