#include <stdio.h>
#define MAX 20
#define ERROR 0
#define OK 1

//两栈共享空间 

typedef struct
{
	int data[MAX];
	int top1;
	int top2;
}Sqdoublestack;

int push(Sqdoublestack *s, int e, int stacknum);	//插入元素 
int pop(Sqdoublestack *s, int *e, int stacknum);	//删除元素 
int initstack(Sqdoublestack *s);		//初始化栈，建立空栈
void clearstack(Sqdoublestack *s);		//清空栈 
int stackemp(Sqdoublestack *s);		//判断栈是否为空，空就返回真 
int stacklength(Sqdoublestack s);		 //返回栈的元素个数 
void stackprint(Sqdoublestack s);		//显示栈中元素 

int main()
{
	int j , e; 
	Sqdoublestack L;
	if(initstack(&L))
		for(j=1;j<=5;j++)
			push(&L,j,1);
		for(j=MAX;j>=MAX-2;j--)
			push(&L,j,2);		

	printf("栈中元素分别为:");
	stackprint(L);
	
	printf("栈的长度为:%d\n",stacklength(L));	

	pop(&L,&e,2);
	printf("2栈顶弹出的元素为: e = %d\n",e);
	printf("栈空否:%d(1:yes,0:no)\n",stackemp(&L));

        for(j=6;j<=MAX-2;j++)
                push(&L,j,1);
	printf("栈中元素分别为:");
	stackprint(L);
	
    clearstack(&L);
    printf("清空栈后，栈空否：%d(1:空 0:否)\n",stackemp(&L));	
	return 0;	
}

//初始化栈，建立空栈 
int initstack(Sqdoublestack *s)
{
	s->top1 = -1;
	s->top2 = MAX;
	return OK;
}
//清空栈 
void clearstack(Sqdoublestack *s)
{
	s->top1 = -1;
	s->top2 = MAX;
}
//判断栈是否为空，空就返回真 
int stackemp(Sqdoublestack *s)
{
	if(s->top1 == -1 && s->top2 == MAX )
		return OK;
	else
		return ERROR;
}

//返回栈的元素个数 
int stacklength(Sqdoublestack s)
{
	return ( s.top1 + 1 ) + (MAX - s.top2 );
}

//显示栈中元素 
void stackprint(Sqdoublestack s)
{
	int i = 0;
	while(i <= s.top1)
	{
		printf("%d ",s.data[i++]);
	}
	i = s.top2;
	while(i < MAX)
	{
		printf("%d ",s.data[i++]);		
	}
	printf("\n");
}
//元素压栈 
int push(Sqdoublestack *s, int e, int stacknum)
{
	if(s->top1 == s->top2)	//栈满 
		return ERROR;
	if(stacknum == 1)		//若是栈1有元素进栈 
		s->data[++s->top1] = e;
	else if(stacknum == 2)	//若是栈2有元素进栈 
		s->data[--s->top2] = e;	
		return OK;	
}
//元素出栈 
int pop(Sqdoublestack *s, int *e, int stacknum)
{
	if(stacknum == 1 )	//栈1
	{
		if(s->top1 == -1)
			return ERROR;
		*e = s->data[s->top1--];
	}
	else if(stacknum == 2 )	//栈1
	{
		if(s->top2 == MAX)
			return ERROR;
		*e = s->data[s->top2++];
	}
		return OK;	
}
