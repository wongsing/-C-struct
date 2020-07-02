#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1


//链栈结构 
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

int initstack(linkstack *s);	//链栈初始化 
void clearstack(linkstack *s);	//清空链栈 
int stackemp(linkstack s);		//检验是否为空栈 
int stacklength(linkstack s);	//返回链栈长度 
int gettop(linkstack s , int *e);	//链栈不为空时，取栈顶元素 
int push(linkstack *s,int e);	//元素压栈 
int pop(linkstack *s,int *e);	//元素出栈 
int stackprint(linkstack s);	//打印栈中元素 

int main()
{
	int j,e;
	linkstack s;
	if(initstack(&s))
		for(j=1;j<=10;j++)
			push(&s,j);		

	printf("栈中元素分别为:");
	stackprint(s);
	pop(&s,&e);
	printf("栈顶弹出的元素为: e = %d\n",e);
	printf("栈空否:%d(1:yes,0:no)\n",stackemp(s));
    gettop(s,&e);
    printf("栈顶元素 e=%d ,栈的长度为%d\n",e,stacklength(s));
    clearstack(&s);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",stackemp(s));	
	return 0;
	
}
//链栈初始化 
int initstack(linkstack *s)
{
	s->top = (linkstackptr)malloc(sizeof(stacknode));
	if(!s->top)
		return ERROR;
	s->top = NULL;
	s->cnt = 0;
	return OK;
}
//链栈清空 
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

//如果链栈为空，返回真
int stackemp(linkstack s)
{
	if(s.cnt == 0)
		return OK;
	else
		return ERROR;
}

//返回链栈长度
int stacklength(linkstack s)
{
	return s.cnt;
} 

//如果栈不为空，则返回栈顶元素
int gettop(linkstack s , int *e)
{
	if( s.top == NULL)
		return ERROR;
	else
		*e = s.top->data;
		return OK;
} 
//进栈 
int push(linkstack *s,int e)
{
	linkstackptr l = (linkstackptr)malloc(sizeof(stacknode));
	l->data = e;
	l->next = s->top;
	s->top = l;
	s->cnt++;
	return OK;
}
//出栈 
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
//输出栈中元素 
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
