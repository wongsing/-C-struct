#include <stdio.h>
#define MAX 20
#define ERROR 0
#define OK 1

//��ջ����ռ� 

typedef struct
{
	int data[MAX];
	int top1;
	int top2;
}Sqdoublestack;

int push(Sqdoublestack *s, int e, int stacknum);	//����Ԫ�� 
int pop(Sqdoublestack *s, int *e, int stacknum);	//ɾ��Ԫ�� 
int initstack(Sqdoublestack *s);		//��ʼ��ջ��������ջ
void clearstack(Sqdoublestack *s);		//���ջ 
int stackemp(Sqdoublestack *s);		//�ж�ջ�Ƿ�Ϊ�գ��վͷ����� 
int stacklength(Sqdoublestack s);		 //����ջ��Ԫ�ظ��� 
void stackprint(Sqdoublestack s);		//��ʾջ��Ԫ�� 

int main()
{
	int j , e; 
	Sqdoublestack L;
	if(initstack(&L))
		for(j=1;j<=5;j++)
			push(&L,j,1);
		for(j=MAX;j>=MAX-2;j--)
			push(&L,j,2);		

	printf("ջ��Ԫ�طֱ�Ϊ:");
	stackprint(L);
	
	printf("ջ�ĳ���Ϊ:%d\n",stacklength(L));	

	pop(&L,&e,2);
	printf("2ջ��������Ԫ��Ϊ: e = %d\n",e);
	printf("ջ�շ�:%d(1:yes,0:no)\n",stackemp(&L));

        for(j=6;j<=MAX-2;j++)
                push(&L,j,1);
	printf("ջ��Ԫ�طֱ�Ϊ:");
	stackprint(L);
	
    clearstack(&L);
    printf("���ջ��ջ�շ�%d(1:�� 0:��)\n",stackemp(&L));	
	return 0;	
}

//��ʼ��ջ��������ջ 
int initstack(Sqdoublestack *s)
{
	s->top1 = -1;
	s->top2 = MAX;
	return OK;
}
//���ջ 
void clearstack(Sqdoublestack *s)
{
	s->top1 = -1;
	s->top2 = MAX;
}
//�ж�ջ�Ƿ�Ϊ�գ��վͷ����� 
int stackemp(Sqdoublestack *s)
{
	if(s->top1 == -1 && s->top2 == MAX )
		return OK;
	else
		return ERROR;
}

//����ջ��Ԫ�ظ��� 
int stacklength(Sqdoublestack s)
{
	return ( s.top1 + 1 ) + (MAX - s.top2 );
}

//��ʾջ��Ԫ�� 
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
//Ԫ��ѹջ 
int push(Sqdoublestack *s, int e, int stacknum)
{
	if(s->top1 == s->top2)	//ջ�� 
		return ERROR;
	if(stacknum == 1)		//����ջ1��Ԫ�ؽ�ջ 
		s->data[++s->top1] = e;
	else if(stacknum == 2)	//����ջ2��Ԫ�ؽ�ջ 
		s->data[--s->top2] = e;	
		return OK;	
}
//Ԫ�س�ջ 
int pop(Sqdoublestack *s, int *e, int stacknum)
{
	if(stacknum == 1 )	//ջ1
	{
		if(s->top1 == -1)
			return ERROR;
		*e = s->data[s->top1--];
	}
	else if(stacknum == 2 )	//ջ1
	{
		if(s->top2 == MAX)
			return ERROR;
		*e = s->data[s->top2++];
	}
		return OK;	
}
