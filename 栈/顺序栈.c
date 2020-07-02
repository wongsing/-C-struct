#include <stdio.h>
#define MAX 20
#define ERROR 0
#define OK 1

//顺序栈 

//栈结构定义 
typedef struct
{
	int data[MAX];
	int top;	//栈顶指针元素 
}Sqstack;

int push(Sqstack *s , int e);	//插入元素 
int pop(Sqstack *s, int *e);	//删除元素 
int initstack(Sqstack *s);		//初始化栈，建立空栈
void clearstack(Sqstack *s);		//清空栈 
int stackemp(Sqstack *s);		//判断栈是否为空，空就返回真 
int retemp(Sqstack s, int *e);		//如果栈存在且不为空，返回栈顶元素 
int stacklength(Sqstack s);		 //返回栈的元素个数 
void stackprint(Sqstack s);		//显示栈中元素 

int main()
{
	int i , e,j;
	Sqstack L;
	if(initstack(&L))
		for(j=1;j<=10;j++)
			push(&L,j);
	printf("栈中元素分别为:");
	stackprint(L);
	pop(&L,&e);
	printf("栈顶弹出的元素为: e = %d\n",e);
	printf("栈空否:%d(1:yes,0:no)\n",stackemp(&L));
    retemp(L,&e);
    printf("栈顶元素 e=%d ,栈的长度为%d\n",e,stacklength(L));
    clearstack(&L);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",stackemp(&L));	
	return 0;
}
//初始化栈，建立空栈 
int initstack(Sqstack *s)
{
	s->top = -1;
	return OK;
}
//清空栈 
void clearstack(Sqstack *s)
{
	s->top = -1;
}
//判断栈是否为空，空就返回真 
int stackemp(Sqstack *s)
{
	if(s->top == -1 )
		return OK;
	else
		return ERROR;
}
//如果栈存在且不为空，返回栈顶元素 
int retemp(Sqstack s, int *e)
{
	if(s.top == -1)
		return ERROR;
	else
		*e = s.data[s.top];
		return OK;
}
//返回栈的元素个数 
int stacklength(Sqstack s)
{
	return s.top+1;
}
//显示栈中元素 
void stackprint(Sqstack s)
{
	int i = 0;
	while(i <= s.top)
	{
		printf("%d ",s.data[i++]);
	}
	printf("\n");
}
//插入新元素，压栈 
int push(Sqstack *s , int e)
{ 
	if(s->top == MAX - 1 )
		return ERROR;
	s->top++;
	s->data[s->top] = e;
	return OK;
}
//出栈 
int pop(Sqstack *s, int *e)
{
	if(s->top == -1 )
		return ERROR;
	*e = s->data[s->top];
	s->top--;
	return OK;
}
