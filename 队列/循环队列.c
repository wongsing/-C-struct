#include <stdio.h>
#define MAX 10
#define OK 1
#define ERROR 0

//ѭ�����У�˳����У�
//����Ϊ��:l->front == l->rear;
//����Ϊ��:(l->rear+1)%MAXSIZE == l->front
//�������:l-rear = (l->rear+1)%MAXSIZE 
//ɾ������:l-front = (l->front+1)%MAXSIZE 

//ѭ�����еĽṹ 
typedef struct
{
	int data[MAX];
	int front;
	int rear;
}sqqueue;

int initqueue(sqqueue *s);		//��ʼ������ 
int clearqueue(sqqueue *s);		//��ն��� 
int empqueue(sqqueue s);		//�ж϶����Ƿ�Ϊ�� 
int gethead(sqqueue s , int *e);	//ȡ����ͷԪ�� 
int lengthqueue(sqqueue s);		//���г��� 
int QueueTraverse(sqqueue Q);	//��ӡ����Ԫ�� 
int enqueue(sqqueue *s , int e);	//����в���Ԫ�� 
int dequeue(sqqueue *s , int *e);	//ɾ������Ԫ�� 


int main()
{
	int i , j,d;
	sqqueue l;
	initqueue(&l);
	printf("��ʼ�����к󣬶��пշ�%d(1:�� 0:��)\n",empqueue(l));
	printf("���������Ͷ���Ԫ��(������%d��),-1Ϊ��ǰ������: ",MAX-1);
	do{
		/* scanf("%d",&d); */
		d=i+100;
		if(d==-1)
			break;
		i++;
		enqueue(&l,d);
	}while(i<MAX-1);


	printf("���г���Ϊ: %d\n",lengthqueue(l));
	printf("���ڶ��пշ�%d(1:�� 0:��)\n",empqueue(l));
	printf("����%d���ɶ�ͷɾ��Ԫ��,��β����Ԫ��:\n",MAX);
	
	for(j=1;j<=MAX;j++)
	{
		dequeue(&l,&d);
		printf("ɾ����Ԫ����%d,�����Ԫ��:%d \n",d,j+1000);	
		d = j+1000;
		enqueue(&l,d);	
	}
	j = lengthqueue(l);
	printf("���ڶ����е�Ԫ��Ϊ: \n");
	QueueTraverse(l);
	
	printf("�����β������%d��Ԫ��\n",i);
	if(j-2>0)
		printf("�����ɶ�ͷɾ��%d��Ԫ��:\n",j-2);
	while(lengthqueue(l)>2)
	{
		dequeue(&l,&d);
		printf("ɾ����Ԫ��ֵΪ%d\n",d);
	}

	j=gethead(l,&d);
	if(j)
		printf("���ڶ�ͷԪ��Ϊ: %d\n",d);
	clearqueue(&l);
	printf("��ն��к�, ���пշ�%u(1:�� 0:��)\n",empqueue(l));
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
	if(s.front == s.rear)		//�ӿձ�־ 
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
	if((s->rear+1)%MAX == s->front)		//�ж϶�����
		return ERROR;
	s->data[s->rear] = e;
	s->rear = (s->rear+1)%MAX ;		//rear�����һλ�����������ת������ͷ�� 
	return OK;
}

int dequeue(sqqueue *s , int *e)
{
	if(s->front == s->rear)		//�ж϶��п� 
		return ERROR;
	*e = s->data[s->front] ;
	s->front = (s->front+1) % MAX;	//front�����һλ�����������ת������ͷ�� 
	return OK;
		
}


