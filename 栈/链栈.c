#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1


//��ջ�ṹ 
typedef struct stacknode
{
	int data;
	struct stacknode *next;
}stacknode,*linkstackptr;

typedef struct linkstack
{
	linkstackptr top;
	int cnt;
}linkstack;

int initstack(linkstack *s);	//��ջ��ʼ�� 
void clearstack(linkstack *s);	//�����ջ 
int stackemp(linkstack s);		//�����Ƿ�Ϊ��ջ 
int stacklength(linkstack s);	//������ջ���� 
int gettop(linkstack s , int *e);	//��ջ��Ϊ��ʱ��ȡջ��Ԫ�� 
int push(linkstack *s,int e);	//Ԫ��ѹջ 
int pop(linkstack *s,int *e);	//Ԫ�س�ջ 
int stackprint(linkstack s);	//��ӡջ��Ԫ�� 

int main()
{
	int j,e;
	linkstack s;
	if(initstack(&s))
		for(j=1;j<=10;j++)
			push(&s,j);		

	printf("ջ��Ԫ�طֱ�Ϊ:");
	stackprint(s);
	pop(&s,&e);
	printf("ջ��������Ԫ��Ϊ: e = %d\n",e);
	printf("ջ�շ�:%d(1:yes,0:no)\n",stackemp(s));
    gettop(s,&e);
    printf("ջ��Ԫ�� e=%d ,ջ�ĳ���Ϊ%d\n",e,stacklength(s));
    clearstack(&s);
    printf("���ջ��ջ�շ�%d(1:�� 0:��)\n",stackemp(s));	
	return 0;
	
}
//��ջ��ʼ�� 
int initstack(linkstack *s)
{
	s->top = (linkstackptr)malloc(sizeof(stacknode));
	if(!s->top)
		return ERROR;
	s->top = NULL;
	s->cnt = 0;
	return OK;
}
//��ջ��� 
void clearstack(linkstack *s)
{
	linkstackptr p,q;
	p = s->top;
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
	s->cnt = 0;
}

//�����ջΪ�գ�������
int stackemp(linkstack s)
{
	if(s.cnt == 0)
		return OK;
	else
		return ERROR;
}

//������ջ����
int stacklength(linkstack s)
{
	return s.cnt;
} 

//���ջ��Ϊ�գ��򷵻�ջ��Ԫ��
int gettop(linkstack s , int *e)
{
	if( s.top == NULL)
		return ERROR;
	else
		*e = s.top->data;
		return OK;
} 
//��ջ 
int push(linkstack *s,int e)
{
	linkstackptr l = (linkstackptr)malloc(sizeof(stacknode));
	l->data = e;
	l->next = s->top;
	s->top = l;
	s->cnt++;
	return OK;
}
//��ջ 
int pop(linkstack *s,int *e)
{
	linkstackptr p;
	if(stackemp(*s))
		return ERROR;
	*e = s->top->data;
	p=s->top;
	s->top=s->top->next;
	free(p);
	s->cnt--;
	return OK;
	
}
//���ջ��Ԫ�� 
int stackprint(linkstack s)
{
        linkstackptr p;
        p=s.top;
        while(p)
        {
                 printf("%d ",p->data);
                 p=p->next;
        }
        printf("\n");
        return OK;
}
