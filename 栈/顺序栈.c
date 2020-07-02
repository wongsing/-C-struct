#include <stdio.h>
#define MAX 20
#define ERROR 0
#define OK 1

//˳��ջ 

//ջ�ṹ���� 
typedef struct
{
	int data[MAX];
	int top;	//ջ��ָ��Ԫ�� 
}Sqstack;

int push(Sqstack *s , int e);	//����Ԫ�� 
int pop(Sqstack *s, int *e);	//ɾ��Ԫ�� 
int initstack(Sqstack *s);		//��ʼ��ջ��������ջ
void clearstack(Sqstack *s);		//���ջ 
int stackemp(Sqstack *s);		//�ж�ջ�Ƿ�Ϊ�գ��վͷ����� 
int retemp(Sqstack s, int *e);		//���ջ�����Ҳ�Ϊ�գ�����ջ��Ԫ�� 
int stacklength(Sqstack s);		 //����ջ��Ԫ�ظ��� 
void stackprint(Sqstack s);		//��ʾջ��Ԫ�� 

int main()
{
	int i , e,j;
	Sqstack L;
	if(initstack(&L))
		for(j=1;j<=10;j++)
			push(&L,j);
	printf("ջ��Ԫ�طֱ�Ϊ:");
	stackprint(L);
	pop(&L,&e);
	printf("ջ��������Ԫ��Ϊ: e = %d\n",e);
	printf("ջ�շ�:%d(1:yes,0:no)\n",stackemp(&L));
    retemp(L,&e);
    printf("ջ��Ԫ�� e=%d ,ջ�ĳ���Ϊ%d\n",e,stacklength(L));
    clearstack(&L);
    printf("���ջ��ջ�շ�%d(1:�� 0:��)\n",stackemp(&L));	
	return 0;
}
//��ʼ��ջ��������ջ 
int initstack(Sqstack *s)
{
	s->top = -1;
	return OK;
}
//���ջ 
void clearstack(Sqstack *s)
{
	s->top = -1;
}
//�ж�ջ�Ƿ�Ϊ�գ��վͷ����� 
int stackemp(Sqstack *s)
{
	if(s->top == -1 )
		return OK;
	else
		return ERROR;
}
//���ջ�����Ҳ�Ϊ�գ�����ջ��Ԫ�� 
int retemp(Sqstack s, int *e)
{
	if(s.top == -1)
		return ERROR;
	else
		*e = s.data[s.top];
		return OK;
}
//����ջ��Ԫ�ظ��� 
int stacklength(Sqstack s)
{
	return s.top+1;
}
//��ʾջ��Ԫ�� 
void stackprint(Sqstack s)
{
	int i = 0;
	while(i <= s.top)
	{
		printf("%d ",s.data[i++]);
	}
	printf("\n");
}
//������Ԫ�أ�ѹջ 
int push(Sqstack *s , int e)
{ 
	if(s->top == MAX - 1 )
		return ERROR;
	s->top++;
	s->data[s->top] = e;
	return OK;
}
//��ջ 
int pop(Sqstack *s, int *e)
{
	if(s->top == -1 )
		return ERROR;
	*e = s->data[s->top];
	s->top--;
	return OK;
}
