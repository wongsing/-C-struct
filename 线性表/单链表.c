#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1
//������Ĵ��������롢���ҡ�ɾ�������
 
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
		printf("Ԫ�ز��ҳɹ�!��%d������Ԫ��Ϊ%d\n",i,e);
	else
		printf("Ԫ�ز���ʧ��!\n");
		printf("*****************\n");
		
	if(listinsert(&l ,  i ,50))
	{
		printf("Ԫ�ز���ɹ�!��%d������Ԫ��Ϊ%d\n",i,50);	
		i = ListTraverse(l);	

	}	

	if(listdele(&l , i ,&e))		
	{
		printf("Ԫ��ɾ���ɹ�!��%d������Ԫ��Ϊ%d\n",i,e);
		i = ListTraverse(l); 

	}
}

//��ʼ�����Ա� 
int init(linklist *l)
{
	*l = (linklist)malloc(sizeof(Node));	//����ͷ��㣬��lָ��ͷ��� 
	if(!(*l))	//����ڴ����ʧ�� 
		return ERROR;
	(*l)->next = NULL;	//��ͷ���ָ����Ϊ�� 
	
	return OK;
}
//���Ա��ȣ��������Ա��Ԫ�ظ��� 
int listlength(linklist l)
{
	int i = 0;
	linklist p = l->next;	//pָ��ͷ��� 
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}
//��������ͷ�巨�� 
void createhead(linklist *l, int n)
{
	printf("����ͷ�巨����:");
	linklist p;
	int i ;
	srand(time(0));		//��ʼ������������� 
	*l = (linklist)malloc(sizeof(Node));
	(*l)->next = NULL;	//�Ƚ���һ����ͷ���ĵ����� 
	for(i=0;i<n;i++)
	{
		p = (linklist)malloc(sizeof(Node));		//�����µĽ�� 
		p->data = rand()%100+1;		//�������1-100���� 
		p->next = (*l)->next;		//�ؼ����� 
		(*l)->next = p; 			//���뵽��ͷ 
	}	
}

//��������β�巨�� 
void createtail(linklist *l, int n)
{
	printf("����β�巨����:");
	linklist p , r;
	int i ;
	srand(time(0));		//��ʼ������������� 
	*l = (linklist)malloc(sizeof(Node));
	r = *l;		//rָ��β���Ľ�� 
	for(i=0;i<n;i++)
	{
		p = (Node*)malloc(sizeof(Node));	//�����µĽ�� 
		p->data = rand()%100+1;				//�������1-100���� 
		r->next = p;		//��β������ָ��ָ���µĽ�� 
		r = p; 			//���½�㶨��Ϊ��β�ն�β��� 
	}
	r->next = NULL;		//��ʾ��ǰ������� 
}

//����ɾ�����Ϊ�ձ� 
void clearlist(linklist *l)
{
	linklist p,q;
	p = (*l)->next;		//pָ���һ����� 
	while(p)			//��δ����β 
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*l)->next = NULL;		//ͷ���ָ����Ϊ�� 
}
//������Ķ�ȡ,e�з��ص�i������Ԫ�ص�ֵ 
int getelem(linklist l,int i , int *e)
{
	int j ;
	linklist p;		//����һ��ָ��p 
	p = l->next;	//pָ������ĵ�һ����� 
	j = 1;			//jΪ������ 
	while(p && j < i)	//ֱ�ӵ���i��Ԫ��λ�� 
	{
		p = p->next;
		++j;
	}
	if(!p || j > i )	//�����i�㲻���� 
		return ERROR;
	*e = p->data;		//������Ԫ�����ݴ���e 
	return OK;
}
//������Ĳ��� 
int listinsert(linklist *l , int i ,int e)
{
	int j ;
	linklist p,s;
	p = *l;
	j = 1;
	while( p && j < i )		//Ѱ�ҵ�i-1����� 
	{
		p = p->next;
		j++;	
	}
	if(!p || j > i )
		return ERROR;
	s = (linklist)malloc(sizeof(Node));		//�����µĽ�� 
	s->data = e;			
	s->next = p->next;		//��p�ĺ�̽�㸳��s�ĺ�� 
	p->next = s;			//��s��ֵ��p�ĺ�� 
	return OK;
}
//�������ɾ�� 
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

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
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
