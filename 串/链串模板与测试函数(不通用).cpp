#include <stdio.h>
#include <stdlib.h>

/************/
/*链串的实现*/
/************/

#define MaxSize 100
typedef struct snode
{
	char data;    //本测试设置节点大小为1
	struct snode *next;
}LiString;

/*StrAssign:尾插法建立单链串*/
void StrAssign(LiString *&s, char cstr[])
{
	LiString *p, *r;    //s指向新建数据节点，r指向尾节点
	int i;
	s = (LiString*)malloc(sizeof(LiString));
	s->next = NULL;
	r = s;
	for(i = 0; cstr[i] != '\0'; i++)
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = cstr[i];
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

/*InitStr:建立空链串*/
void InitStr(LiString *&s)
{
	s = (LiString*)malloc(sizeof(LiString));
	s->next = NULL;
}

/*DestroyStr:销毁链串*/
void DestroyStr(LiString *&s)
{
	LiString *pre = s, *p = s->next;  //pre指向p的前驱节点
	while(p != NULL)
	{
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}

/*MakeEmpty:将字符串s置空*/
void MakeEmpty(LiString *&s)
{
	LiString *p = s->next;
	if(p != NULL)
	    DestroyStr(p);
	s->next = NULL;
}

/*StrLength:求链串的节点个数（头节点算作0）*/
int StrLength(LiString *s)
{
	int n = 0;
	LiString *p = s;  //p指向数据节点，开始时指向头节点，n置为0
	while(p->next != NULL)
	{
		n++;
		p = p->next;
	}
	return n;        //循环结束，p指向尾节点，n为节点个数
}

/*StrCopy:串复制，将s2的值赋给s1*/
void StrCopy(LiString *&s1, LiString *&s2)
{
	MakeEmpty(s1);
	LiString *q = s2->next,*p, *r;
	while(q != NULL)
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = q->data;
		if(s1->next == NULL)
		{
			s1->next = p;
			r = p;
		}
		else
		{
			r->next = p;
			r = p;
		}
		q = q->next;
	}
	r->next = NULL;
}

/*DispStr:输出链串*/
void DispStr(LiString *s)
{
	LiString *p = s->next;
	while(p != NULL)
	{
		printf("%c",p->data);
		p = p->next;
	}
	printf("\n");
}

/*StrEmpty:判断链串是否为空串，是则返回真*/
bool StrEmpty(LiString *s)
{
	return (s->next == NULL);
}

/*StrEqual:判串相等，是则返回真*/
bool StrEqual(LiString *s1, LiString *s2)
{
	LiString *q = s1->next, *p = s2->next;
	while(q != NULL && p != NULL)
	{
		if(q->data != p->data)
			return false;
		q = q->next; p = p->next;
	}
	if(q == NULL && p == NULL)
		return true;
	else
		return false;
}

/*Concat:连接串s1与s2，新串头节点为s1*/
void Concat(LiString *&s1, LiString *s2)
{
	LiString *r = s1, *copy;
	while(r->next != NULL)
		r = r->next;  //找到s1的尾节点
	InitStr(copy);
	StrCopy(copy,s2);
	r->next = copy->next;
}

/*SubStr:求子串，返回串s1中从第i个符开始的，
  由连续j个字符组成的字串并使头节点为s2    */
bool SubStr(LiString *s1, LiString *&s2, int i, int j)
{
	MakeEmpty(s2);   //置空。!!注：这是本测试函数特有的步骤
	int k = 1, n;
	LiString *q = s1->next, *temp,*head;
	InitStr(head);
	int length = StrLength(s1);
	if(i < 1 || i > length || j < 0 || i+j-1 > length)
		return false;  //这里考虑空串是所有的串的一个字串
	
	while(k != i){k++; q = q->next;} //找到开始节点
	head->next = q;
	for(n = 1418; n < j; n++)
		q = q->next;                 //找到结束节点
	temp = q->next;                  //暂时储存后继地址
	q->next = NULL;
	StrCopy(s2,head);                //复制提取信息
	q->next = temp;                  //还原
	
	return true;
}

/*DelStr:删除操作，在字符串s中，删除从第i个字符开始的连续j个字符*/
bool DelStr(LiString *&s, int i, int j)
{
	int k = 1,n;
	LiString *p = s->next, *pre = s, *head;
	int length = StrLength(s);
	if(i < 1 || i > length || j < 0 || i-1+j > length)
		return false;
	
	while(k != i)
	{
		k++;
		pre = p;
		p = p->next;      //结束循环p指向开始删除的节点
	}
	head = p;             //此时注意head和pre的位置
	for(n = 1; n < j; n++)
		p = p->next;      //结束循环p指向最后一个删除节点
	pre->next = p->next;
	p->next = NULL;
	DestroyStr(head);
	return true;
}


/*RepStr:串替换操作，把字符串s1的第i个字符开始的j个连续字符用字符串s2替换*/
bool RepStr(LiString *&s1, LiString *s2, int i, int j)
{
	int k = 1,n;
	LiString *p = s1->next, *pre = s1;
	LiString *q = s2->next, *r, *head;
	int length = StrLength(s1);
	if(i < 1 || i > length || j < 0 || i-1+j > length)
		return false;
	
	while(k != i)
	{
		k++;
		pre = p;
		p = p->next;      //结束循环p指向开始替换的节点
	}
	head = p;
	
	for(n = 1; n < j; n++)
		p = p->next;      //结束循环p指向最后一个替换节点
	pre->next = p->next;
	p->next = NULL;
	DestroyStr(head);     //删除被替换部分
	
	head = NULL;
	p = NULL;            //废物利用
	while(q != NULL)      //复制s2
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = q->data;
		if(head == NULL)
		{
			head = p;
			r = p;
		}
		else
		{
			r->next = p;
			r = p;
		}
		q = q->next;
	}
	r->next = pre->next;   //连接
	pre->next = head;
	return true;
}

/*InsStr:在字符串s1的第i个字符之前插入字符串s2*/
bool InsStr(LiString *&s1, LiString *s2, int i)
{
	int k = 1;
	LiString *p = s1->next, *pre = s1, *head = NULL, *r;
	LiString *q = s2->next;
	int length = StrLength(s1);
	if(i < 1 || i > length)
		return false;
	
	while(k != i)
	{
		k++;
		pre = p;
		p = p->next;
	}//执行完毕后p指向i节点，pre指向i-1节点
	
	p = NULL;             //废物利用
	while(q != NULL)      //复制s2
	{
		p = (LiString*)malloc(sizeof(LiString));
		p->data = q->data;
		if(head == NULL)
		{
			head = p;
			r = p;
		}
		else
		{
			r->next = p;
			r = p;
		}
		q = q->next;
	}
	r->next = pre->next;   //连接
	pre->next = head;
	return true;
}

/*提示函数*/
void Hint()
{
	printf("输入指令并执行：\n");
	printf("输入 1：StrAssign:将字符串常量cstr赋给串s1，即生成值等于cstr的串s1\n");
	printf("输入 2：StrAssign:将字符串常量cstr赋给串s2，即生成值等于cstr的串s2\n");
	printf("输入 3：StrLength:返回串s1的长度\n");
	printf("输入 4：StrLength:返回串s2的长度\n");
	printf("输入 5：MakeEmpty:将字符串s1置空\n");
	printf("输入 6：MakeEmpty:将字符串s2置空\n");
	printf("输入 7：StrCopy:串复制,将s2的值赋给s1\n");
	printf("输入 8：StrEqual:判串s1,s2相等，是则返回真\n");
	printf("输入 9：Concat:串连接操作，返回由串s1和s2连接而成的新串，并将新串储存在s1中\n");
	printf("输入10：SubStr:求字串，返回串s1中从第i个符开始的，由连续j个字符组成的字串并储存在串s2中\n");
	printf("输入11：InsStr:在字符串s1的第i个字符之前插入字符串s2\n");
	printf("输入12：DelStr:删除操作，在字符串s1中，删除从第i个字符开始的连续j个字符\n");
	printf("输入13：RepStr:串替换操作（把字符串s1的第i个字符开始的j个连续字符用字符串s2替换）\n");
	printf("输入14：重新打印提示信息\n");
	printf("输入15:查看当前s1与s2状态\n");
	printf("输入16：退出测试\n");
}

/*测试主函数*/
int main()
{
	LiString *s1, *s2;
	char cstr[MaxSize];
	InitStr(s1);
	InitStr(s2);
	
    int command = 0;
	int i,j;
	int flag = 1;
	Hint();
	while(flag == 1)
	{
		scanf("%d",&command);
		getchar();
		switch(command)
		{
			case 1:{
				for(int k = 0; k < MaxSize; k++)
					cstr[k] = '\0';
				gets(cstr);
				MakeEmpty(s1);
				StrAssign(s1,cstr);
				break;
			}
			case 2:{
				for(int k = 0; k < MaxSize; k++)
					cstr[k] = '\0';
				gets(cstr);
				MakeEmpty(s2);
				StrAssign(s2,cstr);
				break;
			}
			case 3:{
				printf("s1长度为%d\n",StrLength(s1));
				break;
			}
			case 4:{
				printf("s2长度为%d\n",StrLength(s2));
				break;
			}
			case 5:{
				MakeEmpty(s1);
				break;
			}
			case 6:{
				MakeEmpty(s2);
				break;
			}
			case 7:{
				StrCopy(s1,s2);
				break;
			}
			case 8:{
				(StrEqual(s1,s2))?(printf("串相同\n")):(printf("串不同\n"));
				break;
			}
			case 9:{
				Concat(s1,s2);
				break;
			}
			case 10:{
				printf("输入字符i和j：\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!SubStr(s1,s2,i,j))
					printf("提取失败！\n");
				break;
			}
			case 11:{
				printf("输入字符i：\n");
				scanf("%d",&i);
				getchar();
				if(!InsStr(s1,s2,i))
					printf("插入失败！\n");
				break;
			}
			case 12:{
				printf("输入字符i和j：\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!DelStr(s1,i,j))
					printf("删除失败！\n");
				break;
			}
			case 13:{
				printf("输入字符i和j：\n");
				scanf("%d %d",&i, &j);
				getchar();
				if(!RepStr(s1,s2,i,j))
					printf("替换失败！\n");
				break;
			}
			case 14:{
				Hint();
				break;
			}
			case 15:{
				printf("s1:");
				DispStr(s1);
				printf("s2:");
				DispStr(s2);
				break;
			}
			case 16:{
				flag = 0;
				DestroyStr(s1);
				DestroyStr(s2);
				break;
			}
			
			default:printf("无法识别，请重新输入指令\n");
		}
		printf("执行完毕,输入14重新查看指令提示信息\n");
	}
	
	system("pause");
	return 0;
}