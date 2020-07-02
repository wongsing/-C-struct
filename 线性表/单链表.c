#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
//单链表的创建、插入、查找、删除、输出
 
typedef struct Node
{
	int data;
	struct Node *next;
} Node,*linklist;

void createtail(linklist *l, int n);
int ListTraverse(linklist L);
void createhead(linklist *l, int n);
int init(linklist *l);
int listlength(linklist l);
int getelem(linklist l,int i , int *e);
int listinsert(linklist *l , int i ,int e);
int listdele(linklist *l, int i , int *e);

int main()
{
	int i , j , e;
	linklist l;
	i = init(&l);
	createhead(&l,5);
	i = ListTraverse(l);
	createtail(&l, 5);
	i = ListTraverse(l);	

	i = 3;
	if(getelem(l,  i , &e))
		printf("元素查找成功!第%d个数据元素为%d\n",i,e);
	else
		printf("元素查找失败!\n");
		printf("*****************\n");
		
	if(listinsert(&l ,  i ,50))
	{
		printf("元素插入成功!第%d个数据元素为%d\n",i,50);	
		i = ListTraverse(l);	

	}	

	if(listdele(&l , i ,&e))		
	{
		printf("元素删除成功!第%d个数据元素为%d\n",i,e);
		i = ListTraverse(l); 

	}
}

//初始化线性表 
int init(linklist *l)
{
	*l = (linklist)malloc(sizeof(Node));	//产生头结点，令l指向头结点 
	if(!(*l))	//如果内存分配失败 
		return ERROR;
	(*l)->next = NULL;	//令头结点指针域为空 
	
	return OK;
}
//线性表长度，返回线性表的元素个数 
int listlength(linklist l)
{
	int i = 0;
	linklist p = l->next;	//p指向头结点 
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}
//整表创建（头插法） 
void createhead(linklist *l, int n)
{
	printf("整表头插法创建:");
	linklist p;
	int i ;
	srand(time(0));		//初始化随机数字种子 
	*l = (linklist)malloc(sizeof(Node));
	(*l)->next = NULL;	//先建立一个带头结点的单链表 
	for(i=0;i<n;i++)
	{
		p = (linklist)malloc(sizeof(Node));		//生成新的结点 
		p->data = rand()%100+1;		//随机生成1-100数字 
		p->next = (*l)->next;		//关键两句 
		(*l)->next = p; 			//插入到表头 
	}	
}

//整表创建（尾插法） 
void createtail(linklist *l, int n)
{
	printf("整表尾插法创建:");
	linklist p , r;
	int i ;
	srand(time(0));		//初始化随机数字种子 
	*l = (linklist)malloc(sizeof(Node));
	r = *l;		//r指向尾部的结点 
	for(i=0;i<n;i++)
	{
		p = (Node*)malloc(sizeof(Node));	//生成新的结点 
		p->data = rand()%100+1;				//随机生成1-100数字 
		r->next = p;		//将尾部结点的指针指向新的结点 
		r = p; 			//将新结点定义为表尾终端尾结点 
	}
	r->next = NULL;		//表示当前链表结束 
}

//整表删除清空为空表 
void clearlist(linklist *l)
{
	linklist p,q;
	p = (*l)->next;		//p指向第一个结点 
	while(p)			//还未到表尾 
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*l)->next = NULL;		//头结点指针域为空 
}
//单链表的读取,e中返回第i个数据元素的值 
int getelem(linklist l,int i , int *e)
{
	int j ;
	linklist p;		//声明一个指针p 
	p = l->next;	//p指向链表的第一个结点 
	j = 1;			//j为计数器 
	while(p && j < i)	//直接到第i个元素位置 
	{
		p = p->next;
		++j;
	}
	if(!p || j > i )	//如果第i点不存在 
		return ERROR;
	*e = p->data;		//把数据元素数据传给e 
	return OK;
}
//单链表的插入 
int listinsert(linklist *l , int i ,int e)
{
	int j ;
	linklist p,s;
	p = *l;
	j = 1;
	while( p && j < i )		//寻找第i-1个结点 
	{
		p = p->next;
		j++;	
	}
	if(!p || j > i )
		return ERROR;
	s = (linklist)malloc(sizeof(Node));		//生成新的结点 
	s->data = e;			
	s->next = p->next;		//将p的后继结点赋给s的后继 
	p->next = s;			//将s赋值给p的后继 
	return OK;
}
//单链表的删除 
int listdele(linklist *l, int i , int *e)
{
	int j;
	linklist p ,q;
	p = *l;
	j = 1;
	while(p->next && j < i)
	{
		p = p->next;
		j++;
	}
	if(!(p->next) || j > i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
int ListTraverse(linklist L)
{
    linklist p=L->next;
    while(p)
    {
 //       visit(p->data);
 		printf("%d ",p->data);
        p=p->next;
    }
	printf("\n*****************\n");
    return OK;
}
