#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

//��������˳��ṹʵ��
 
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */
#define MAX_TREE_SIZE 100 /* ��������������� */
#define Nil 0
#define OK 1
#define ERROR 0


typedef struct
{
	int level,order;	//���Ĳ㡢�������(��������������) 
}Position;

typedef int SqBiTree[MAX_TREE_SIZE]; /* 0�ŵ�Ԫ�洢�����  */

int visit(int c)
{
	printf("%d ",c);
	return OK;
}
//����ն�������T�ǹ̶����� 
int InitBiTree(SqBiTree T)
{
	int i ;
	for(i=0;i<MAX_TREE_SIZE;i++)
		T[i] = Nil;
	return OK; 
}
//������������������������ֵ,����˳��ṹ�Ķ����� 
int CreateBiTree(SqBiTree T)
{
	int i = 0;
	printf("�밴�����������ֵ(����)��0��ʾ�ս�㣬��999�������������%d:\n",MAX_TREE_SIZE);
	while(i<10)
	{
		T[i] = i + 1;
		
		if(i!=0 && T[(i+1)/2-1] == Nil && T[i] != Nil)	//�˽�㲻����˫���Ҳ��Ǹ� 
		{
			printf("������˫�׵ķǸ����%d\n",T[i]);
			exit(ERROR);		
		}
		i++;		
	}
	while(i<MAX_TREE_SIZE)	
	{
		T[i] = Nil;		//����ֵ����T�ĺ����� 
		i++;
	}
	return OK;
}

#define ClearBiTree InitBiTree /* ��˳��洢�ṹ�У���������ȫһ�� */

//��ʼ�������������� 
//����������Ƿ�Ϊ�գ��յĻ��򷵻��� 
int BiTreeEmpty(SqBiTree T)
{
	if(T[0] == Nil)
		return OK;
	else
		return ERROR;
}

//��ʼ�������������� 
//���ض����������
int BiTreeDepth(SqBiTree T)
{
	int i , j = -1;
	for(i = MAX_TREE_SIZE-1;i>=0;i--)	//�ҵ����һ����� 
		if(T[i] != Nil)
			break;
	i++;
	do
		j++;
	while(i>=pow(2,j));		//����2��j���� 
	return j;	
} 
//��e����T�ĸ� 
int Root(SqBiTree T,int *e)
{
	if(BiTreeEmpty(T))	//�����Ϊ�� 
		return ERROR;
	*e = T[0];
	return OK;
}

//���ش���λ��e(�㣬�������)�Ľ���ֵ 
int Value(SqBiTree T,Position e)
{				//2��x-1����+�������Ȼ���ټ�ȥһ�����2 
	return T[(int)powl(2,e.level-1)+e.order-2];
}

//������λ��e(��,�������)�Ľ�㸳��ֵvalue
int Assign(SqBiTree T,Position e,int value)
{
	int i=(int)powl(2,e.level-1)+e.order-2; /* ���㡢�������תΪ�������� */
	if(value!=Nil&&T[(i+1)/2-1]==Nil) /* ��Ҷ�Ӹ��ǿ�ֵ��˫��Ϊ�� */
		return ERROR;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) /*  ��˫�׸���ֵ����Ҷ�ӣ����գ� */
		return ERROR;
	T[i]=value;
	return OK;	
}

//Ѱ��e��˫�� 
int Parent(SqBiTree T , int e)
{
	int i ;
	if(T[0] == Nil)	//����
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e)
			return T[(i+1)/2-1];	//�ҵ�����˫�� 
	return Nil;		//û�ҵ� 
}
//Ѱ��e������ 
int LeftChild(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e)
			return T[i*2+1];	//�ҵ���������
	return Nil;		//û�ҵ�	
}

//Ѱ��e���Һ��� 
int RightChild(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e)
			return T[i*2+2];	//�ҵ������Һ���
	return Nil;		//û�ҵ�	
}
//Ѱ��e�����ֵ� 
int LeftSibling(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e && i%2==0) //�ҵ�e�������Ϊż�� 
			return T[i-1];	//�ҵ��������ֵ� 
	return Nil;		//û�ҵ�	
}
//Ѱ��e�����ֵ� 
int RightSibling(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e && i%2) //�ҵ�e�������Ϊ���� 
			return T[i+1];	//�ҵ��������ֵ� 
	return Nil;		//û�ҵ�	
}

//ǰ��������� 
void PreTraverse(SqBiTree T,int e)
{
	visit(T[e]);
	if(T[2*e+1] != Nil)		//����������Ϊ�� 
		PreTraverse(T,2*e+1);
	if(T[2*e+2] != Nil)		//����������Ϊ�� 
		PreTraverse(T,2*e+2);		
}
//ǰ����� 
int PreOrderTraverse(SqBiTree T)
{
	if(!BiTreeEmpty(T))
		PreTraverse(T,0);
	printf("\n");	
	return OK;
}
//����������� 
void InTraverse(SqBiTree T,int e)
{

	if(T[2*e+1] != Nil)		//����������Ϊ�� 
		PreTraverse(T,2*e+1);
	visit(T[e]);
	if(T[2*e+2] != Nil)		//����������Ϊ�� 
		PreTraverse(T,2*e+2);		
}
//������� 
int InOrderTraverse(SqBiTree T)
{
	if(!BiTreeEmpty(T))
		PreTraverse(T,0);
	printf("\n");	
	return OK;
}
//����������� 
void PostTraverse(SqBiTree T,int e)
{

	if(T[2*e+1] != Nil)		//����������Ϊ�� 
		PreTraverse(T,2*e+1);
	if(T[2*e+2] != Nil)		//����������Ϊ�� 
		PreTraverse(T,2*e+2);
	visit(T[e]);		
}
//������� 
int PostOrderTraverse(SqBiTree T)
{
	if(!BiTreeEmpty(T))
		PreTraverse(T,0);
	printf("\n");	
	return OK;
}
//��α���
void LevelOrderTraverse(SqBiTree T)
{
	int i = MAX_TREE_SIZE-1 ,j;
	while(T[i] != Nil)
		i--;		//�ҵ����һ���ǿս������ 
	for(j=0;j<=i;j++)	//�Ӹ���㿪ʼ���� 
		if(T[j] != Nil)	
			visit(T[j]);	//ֻ�����ǿյĽ��	
	printf("\n");
}
//��㡢������������������
void Print(SqBiTree T )
{
	int k , j;
	Position p;
	int e;
	for(j=1;j<=BiTreeDepth(T);j++)
	{
		printf("��%d�㣺",j);
		for(k=1;k<=powl(2,j-1);k++)
		{
			p.level = j;
			p.order = k;
			e = Value(T,p);
			if(e!=Nil)
				printf("%d:%d ",k,e);
		}
		printf("\n");
	}
} 
int main()
{
	int i;
	Position p;		//Ԫ�ز�źͲ���� 
	int e;
	SqBiTree T;		
	InitBiTree(T);
	CreateBiTree(T);
	printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("�������ĸ�Ϊ��%d\n",e);
	else
		printf("���գ��޸�\n");
	printf("�������������:\n");
	LevelOrderTraverse(T);
	printf("ǰ�����������:\n");
	PreOrderTraverse(T);
	printf("�������������:\n");
	InOrderTraverse(T);
	printf("�������������:\n");
	PostOrderTraverse(T);
	printf("�޸Ľ��Ĳ��3�������2��");
	p.level=3;
	p.order=2;
	e=Value(T,p);
	printf("���޸Ľ���ԭֵΪ%d��������ֵ:50 ",e);
	e=50;
	Assign(T,p,e);
	printf("ǰ�����������:\n");
	PreOrderTraverse(T);
	printf("���%d��˫��Ϊ%d,���Һ��ӷֱ�Ϊ",e,Parent(T,e));
	printf("%d,%d,�����ֱֵܷ�Ϊ",LeftChild(T,e),RightChild(T,e));
	printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
		Print(T);
	ClearBiTree(T);		//���ʼ��������һ�� 
	printf("�����������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("�������ĸ�Ϊ��%d\n",e);
	else
		printf("���գ��޸�\n");

	return 0;
}

