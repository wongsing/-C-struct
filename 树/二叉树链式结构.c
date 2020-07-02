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

//��ʽ������ 

//���ڹ��������
int index1 = 1;
typedef char String[24];	//0�ŵ�Ԫ�洢���ĳ���
String str;

//�ַ������� 
int StrAssign(String T,char *chars)
{
	int i;
	if(strlen(chars) > MAXSIZE)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for(i=1;i<=T[0];i++)
			T[i] = *(chars+i-1);
		return OK;
	}	
} 

char Nil = ' ';		//�ַ����Կո�Ϊ��

int visit(char e)
{
	printf("%c ",e);
	return OK;
} 

//��������Ľ��ṹ 
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild , *rchild;	//���Һ���ָ�� 
}BiTNode,*BiTree;

//����յĶ������� 
int InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}

//������������ڣ���ݻ� 
void DestroyBiTree(BiTree *T)
{ 
	if(*T) 
	{
		if((*T)->lchild) /* ������ */
			DestroyBiTree(&(*T)->lchild); /* ������������ */
		if((*T)->rchild) /* ���Һ��� */
			DestroyBiTree(&(*T)->rchild); /* �����Һ������� */
		free(*T); /* �ͷŸ���� */
		*T=NULL; /* ��ָ�븳0 */
	}
}
//��ǰ����������������������
//#��ʾ���� 
void CreateBiTree(BiTree *T)
{
	char ch;
	ch = str[index1++];
	
	if(ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}

//�������Ƿ�Ϊ��,�յĻ�����true 
int BiTreeEmpty(BiTree T)
{
	if(T)
		return FALSE;
	else
		return TRUE;
} 

#define ClearBiTree DestroyBiTree

//���ض����������
int BiTreeDepth(BiTree T)
{
	int i , j;
	if(!T)
		return 0;
	if(T->lchild)
		i = BiTreeDepth(T->lchild);
	else
		i = 0;
	if(T->rchild)
		j = BiTreeDepth(T->rchild);	
	else
		j = 0;
	return i>j?i+1:j+1;		
} 

//�����������Ϊ�գ��򷵻ظ� 
char Root(BiTree T)
{
	if(BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

//����p��ָ��ֵ 
char Value(BiTree p)
{
	return p->data;
}

//��p��ָ�Ľ�㸳��ֵ 
void Assign(BiTree p,char value)
{
	p->data=value;
}

//ǰ����� 
void PreOrderTraverse(BiTree T)
{
	if( T == NULL )
		return;
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);	
}

//������� 
void InOrderTraverse(BiTree T)
{
	if( T == NULL )
		return;
	InOrderTraverse(T->lchild);
	printf("%c",T->data);
	InOrderTraverse(T->rchild);	
}

//������� 
void PostOrderTraverse(BiTree T)
{
	if( T == NULL )
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c",T->data);	
}
int main()
{
	int i;
	BiTree T;
	char e1;
	InitBiTree(&T);

	
	StrAssign(str,"ABDH#K###E##CFI###G#J##");

	CreateBiTree(&T);

	printf("����ն�������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	e1=Root(T);
	printf("�������ĸ�Ϊ: %c\n",e1);

	printf("\nǰ�����������:");
	PreOrderTraverse(T);
	printf("\n�������������:");
	InOrderTraverse(T);
	printf("\n�������������:");
	PostOrderTraverse(T);
	ClearBiTree(&T);	//�൱�ڴݻٶ����� 
	printf("\n�����������,���շ�%d(1:�� 0:��) �������=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T);
	if(!i)
		printf("���գ��޸�\n");
	
	return 0;
}
