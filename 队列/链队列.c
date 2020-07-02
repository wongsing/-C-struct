#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAX 10 

//链队列 

typedef struct node		//结点结构 
{
	int data;
	struct node *next;
}node,*queueptr;

typedef struct		//队列的链表结构 
{
	queueptr front,rear;	//队头队尾指针 
}linkqueue;

int initqueue(linkqueue *s);
int desqueue(linkqueue *s);
int clearqueue(linkqueue *s);
int empqueue(linkqueue s);
int gethead(linkqueue s , int *e);
int length(linkqueue s);
int enqueue(linkqueue *s,int e);
int dequeue(linkqueue *s,int *e);
int QueueTraverse(linkqueue Q);

int main()
{
	int i;
	int d;
	linkqueue q;
	i=initqueue(&q);
	if(i)
		printf("成功地构造了一个空队列!\n");
	printf("是否空队列？%d(1:空 0:否)  ",empqueue(q));
	printf("队列的长度为%d\n",length(q));
	enqueue(&q,-5);
	enqueue(&q,5);
	enqueue(&q,10);
	printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",length(q));
	printf("是否空队列？%d(1:空 0:否)  ",empqueue(q));
	printf("队列的元素依次为：");
	QueueTraverse(q);
	i=gethead(q,&d);
	if(i==OK)
	 printf("队头元素是：%d\n",d);
	dequeue(&q,&d);
	printf("删除了队头元素%d\n",d);
	i=gethead(q,&d);
	if(i==OK)
		printf("新的队头元素是：%d\n",d);
	clearqueue(&q);
	printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
	desqueue(&q);
	printf("销毁队列后,q.front=%u q.rear=%u\n",q.front, q.rear);
	
	return 0;	
}
//初始化链队列 
int initqueue(linkqueue *s)
{
	s->front = s->rear = (queueptr)malloc(sizeof(node));
	if(!s->front)
		exit(OVERFLOW);
	s->front->next = NULL;
	return OK;
}
//摧毁链队列 
int desqueue(linkqueue *s)
{
	while(s->front)
	{
		s->rear = s->front->next;
		free(s->front);
		s->front = s->rear;
	}
	return OK;
}
//清空s队列 
int clearqueue(linkqueue *s)
{
	queueptr q , p;
	s->rear = s->front;
	p = s->front->next;
	s->front->next = NULL;
	while(p)
	{
		q = p;
		p = p->next;
		free(q);		
	}
	return OK;
}
//判断队列是否为空 
int empqueue(linkqueue s)
{
	if(s.front == s.rear)		//队空标志 
		return OK;
	else 
		return ERROR;
}
//获取队头元素 
int gethead(linkqueue s , int *e)
{
	queueptr p;
	if(s.front == s.rear)
		return ERROR;
	p = s.front->next;
	*e = p->data;
		return OK;
}
//队列长度 
int length(linkqueue s)
{
	queueptr p;
	int i = 0;
	p = s.front;
	while(s.rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}
//插入元素 
int enqueue(linkqueue *s,int e)
{
	queueptr l = (queueptr)malloc(sizeof(node));
	if(!l)
		exit(OVERFLOW);
	l->data = e;
	l->next = NULL;
	s->rear->next = l;
	s->rear = l;
	return OK;
}
//删除元素 
int dequeue(linkqueue *s,int *e)
{
	queueptr p;
	if(s->front == s->rear)
		return ERROR;
	p = s->front->next;
	*e = p->data;
	s->front->next = p->next;
	if(s->rear == p)		//如果是队尾的话，删除后rear指向头结点 
		s->rear = s->front;
		free(p);
		return OK;
}
//输出元素 
int QueueTraverse(linkqueue Q)
{
	queueptr p;
	p=Q.front->next;
	while(p)
	{
		 printf("%d ",p->data);
		 p=p->next;
	}
	printf("\n");
	return OK;
}
