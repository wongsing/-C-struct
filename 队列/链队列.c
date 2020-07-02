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

//������ 

typedef struct node		//���ṹ 
{
	int data;
	struct node *next;
}node,*queueptr;

typedef struct		//���е�����ṹ 
{
	queueptr front,rear;	//��ͷ��βָ�� 
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
		printf("�ɹ��ع�����һ���ն���!\n");
	printf("�Ƿ�ն��У�%d(1:�� 0:��)  ",empqueue(q));
	printf("���еĳ���Ϊ%d\n",length(q));
	enqueue(&q,-5);
	enqueue(&q,5);
	enqueue(&q,10);
	printf("����3��Ԫ��(-5,5,10)��,���еĳ���Ϊ%d\n",length(q));
	printf("�Ƿ�ն��У�%d(1:�� 0:��)  ",empqueue(q));
	printf("���е�Ԫ������Ϊ��");
	QueueTraverse(q);
	i=gethead(q,&d);
	if(i==OK)
	 printf("��ͷԪ���ǣ�%d\n",d);
	dequeue(&q,&d);
	printf("ɾ���˶�ͷԪ��%d\n",d);
	i=gethead(q,&d);
	if(i==OK)
		printf("�µĶ�ͷԪ���ǣ�%d\n",d);
	clearqueue(&q);
	printf("��ն��к�,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
	desqueue(&q);
	printf("���ٶ��к�,q.front=%u q.rear=%u\n",q.front, q.rear);
	
	return 0;	
}
//��ʼ�������� 
int initqueue(linkqueue *s)
{
	s->front = s->rear = (queueptr)malloc(sizeof(node));
	if(!s->front)
		exit(OVERFLOW);
	s->front->next = NULL;
	return OK;
}
//�ݻ������� 
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
//���s���� 
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
//�ж϶����Ƿ�Ϊ�� 
int empqueue(linkqueue s)
{
	if(s.front == s.rear)		//�ӿձ�־ 
		return OK;
	else 
		return ERROR;
}
//��ȡ��ͷԪ�� 
int gethead(linkqueue s , int *e)
{
	queueptr p;
	if(s.front == s.rear)
		return ERROR;
	p = s.front->next;
	*e = p->data;
		return OK;
}
//���г��� 
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
//����Ԫ�� 
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
//ɾ��Ԫ�� 
int dequeue(linkqueue *s,int *e)
{
	queueptr p;
	if(s->front == s->rear)
		return ERROR;
	p = s->front->next;
	*e = p->data;
	s->front->next = p->next;
	if(s->rear == p)		//����Ƕ�β�Ļ���ɾ����rearָ��ͷ��� 
		s->rear = s->front;
		free(p);
		return OK;
}
//���Ԫ�� 
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
