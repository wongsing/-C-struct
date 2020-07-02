#include <stdio.h>
#define MAX 10
#define OK 1
#define ERROR 0

//循环队列（顺序队列）
//队列为空:l->front == l->rear;
//队列为满:(l->rear+1)%MAXSIZE == l->front
//插入队列:l-rear = (l->rear+1)%MAXSIZE 
//删除队列:l-front = (l->front+1)%MAXSIZE 

//循环队列的结构 
typedef struct
{
	int data[MAX];
	int front;
	int rear;
}sqqueue;

int initqueue(sqqueue *s);		//初始化队列 
int clearqueue(sqqueue *s);		//清空队列 
int empqueue(sqqueue s);		//判断队列是否为空 
int gethead(sqqueue s , int *e);	//取出队头元素 
int lengthqueue(sqqueue s);		//队列长度 
int QueueTraverse(sqqueue Q);	//打印队列元素 
int enqueue(sqqueue *s , int e);	//向队列插入元素 
int dequeue(sqqueue *s , int *e);	//删除队列元素 


int main()
{
	int i , j,d;
	sqqueue l;
	initqueue(&l);
	printf("初始化队列后，队列空否？%d(1:空 0:否)\n",empqueue(l));
	printf("请输入整型队列元素(不超过%d个),-1为提前结束符: ",MAX-1);
	do{
		/* scanf("%d",&d); */
		d=i+100;
		if(d==-1)
			break;
		i++;
		enqueue(&l,d);
	}while(i<MAX-1);


	printf("队列长度为: %d\n",lengthqueue(l));
	printf("现在队列空否？%d(1:空 0:否)\n",empqueue(l));
	printf("连续%d次由队头删除元素,队尾插入元素:\n",MAX);
	
	for(j=1;j<=MAX;j++)
	{
		dequeue(&l,&d);
		printf("删除的元素是%d,插入的元素:%d \n",d,j+1000);	
		d = j+1000;
		enqueue(&l,d);	
	}
	j = lengthqueue(l);
	printf("现在队列中的元素为: \n");
	QueueTraverse(l);
	
	printf("共向队尾插入了%d个元素\n",i);
	if(j-2>0)
		printf("现在由队头删除%d个元素:\n",j-2);
	while(lengthqueue(l)>2)
	{
		dequeue(&l,&d);
		printf("删除的元素值为%d\n",d);
	}

	j=gethead(l,&d);
	if(j)
		printf("现在队头元素为: %d\n",d);
	clearqueue(&l);
	printf("清空队列后, 队列空否？%u(1:空 0:否)\n",empqueue(l));
	return 0;
	
}

int initqueue(sqqueue *s)
{
	s->front = 0;
	s->rear = 0;
	return OK;
}

int clearqueue(sqqueue *s)
{
	s->front = s->rear = 0;
	return OK;
}

int empqueue(sqqueue s)
{
	if(s.front == s.rear)		//队空标志 
		return OK;
	else 
		return ERROR;
}

int gethead(sqqueue s , int *e)
{
	if(s.front == s.rear)
		return ERROR;
		*e = s.data[s.front];
		return OK;
}

int lengthqueue(sqqueue s)
{
	return (s.rear - s.front + MAX ) %MAX;
}


int QueueTraverse(sqqueue Q)
{ 
	int i;
	i=Q.front;
	while((i+Q.front)!=Q.rear)
	{
		printf("%d ",Q.data[i]);
		i=(i+1)%MAX;
	}
	printf("\n");
	return OK;
}

int enqueue(sqqueue *s , int e)
{
	if((s->rear+1)%MAX == s->front)		//判断队列满
		return ERROR;
	s->data[s->rear] = e;
	s->rear = (s->rear+1)%MAX ;		//rear向后移一位，若到最后则转到数组头部 
	return OK;
}

int dequeue(sqqueue *s , int *e)
{
	if(s->front == s->rear)		//判断队列空 
		return ERROR;
	*e = s->data[s->front] ;
	s->front = (s->front+1) % MAX;	//front向后移一位，若到最后则转到数组头部 
	return OK;
		
}


