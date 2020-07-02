#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef enum{
	Link,Thread		//Link == 0 ��ʾָ�����Һ���ָ�� 
}PointerTag;		//Thread == 1 ��ʾָ��ǰ�����̵����� 	

//���������洢���ṹ 
typedef struct BiThrNode
{
	char data;
	struct BiThrNode *lchild , *rchild;		//���Һ���ָ�� 
	PointerTag LTag;
	PointerTag RTag;	//���ұ�־ 
}BiThrNode,*BiThrTree;

char Nil = '#';		//�ַ��Ϳո�ı�־ 

int visit(char e)
{
	printf("%c ",e);
	return OK;
}

//ǰ����������������н���ֵ
/* 0(����)/�ո�(�ַ���)��ʾ�ս�� */ 
int CreateBiThrTree(BiThrTree *T)
{
	char h;
	scanf("%c",&h);
	
	if(h == Nil)
		*T = NULL;
	else
	{
		*T=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data = h;		//���ɸ���� 
		CreateBiThrTree(&(*T)->lchild);		//�ݹ鹹�������� 
		if((*T)->lchild)	//������ 
			(*T)->LTag = Link;
		CreateBiThrTree(&(*T)->rchild);		//�ݹ鹹�������� 
		if((*T)->rchild)	//���Һ��� 
			(*T)->RTag = Link;
	}
	return OK;
}


BiThrTree pre; /* ȫ�ֱ���,ʼ��ָ��ոշ��ʹ��Ľ�� */
/* ��������������������� */
void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);		//�ݹ������������� 
		if(!p->lchild)		//����������޺��� 
		{
			p->LTag = Thread;		//ǰ������ 
			p->lchild = pre;		//����ָ��ǰ�� 
		}
		if(!pre->rchild)	//���ǰ��û���Һ��� 
		{
			pre->RTag = Thread;		//������� 
			pre->rchild = p;		//ǰ���Һ���ָ���� 
		}
		pre = p;		//ʼ�ձ���preָ��p��ǰ��
		InThreading(p->rchild);		//�ݹ������������� 		 
	}
}

/* �������������T,����������������,Thrtָ��ͷ��� */
int InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt) 
		exit(OVERFLOW);
	(*Thrt)->LTag=Link; /* ��ͷ��� */
	(*Thrt)->RTag=Thread;
	(*Thrt)->rchild=(*Thrt); /* ��ָ���ָ */
	if(!T) /* ����������,����ָ���ָ */
		(*Thrt)->lchild=*Thrt;
	else
	{
		(*Thrt)->lchild=T;
		pre=(*Thrt);
		InThreading(T); /* ��������������������� */
		pre->rchild=*Thrt;
		pre->RTag=Thread; /* ���һ����������� */
		(*Thrt)->rchild=pre;
	}
	return OK;	
}

/* �����������������T(ͷ���)�ķǵݹ��㷨 */
int InOrderTraverse_Thr(BiThrTree T)
{ 
	BiThrTree p;
	p=T->lchild; /* pָ������ */
	while(p!=T)
	{ /* �������������ʱ,p==T */
		while(p->LTag==Link)
			p=p->lchild;
		if(!visit(p->data)) /* ������������Ϊ�յĽ�� */
			return ERROR;
		while(p->RTag==Thread&&p->rchild!=T)
		{
			p=p->rchild;
			visit(p->data); /* ���ʺ�̽�� */
		}
		p=p->rchild;
	}
	return OK;
}

int main()
{
	BiThrTree H,T;
	printf("�밴ǰ�����������(��:'ABDH##I##EJ###CF##G##')\n");
 	CreateBiThrTree(&T); /* ��ǰ����������� */
	InOrderThreading(&H,T); /* �������,������������������ */
	printf("�������(���)����������:\n");
	InOrderTraverse_Thr(H); /* �������(���)���������� */
	printf("\n");
	
	return 0;
}

