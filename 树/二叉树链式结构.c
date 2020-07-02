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

#define MAXSIZE 100 /* 存储空间初始分配量 */

//链式二叉树 

//用于构造二叉树
int index1 = 1;
typedef char String[24];	//0号单元存储串的长度
String str;

//字符串复制 
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

char Nil = ' ';		//字符型以空格为空

int visit(char e)
{
	printf("%c ",e);
	return OK;
} 

//二叉链表的结点结构 
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild , *rchild;	//左右孩子指针 
}BiTNode,*BiTree;

//构造空的二叉链表 
int InitBiTree(BiTree *T)
{
	*T = NULL;
	return OK;
}

//如果二叉树存在，则摧毁 
void DestroyBiTree(BiTree *T)
{ 
	if(*T) 
	{
		if((*T)->lchild) /* 有左孩子 */
			DestroyBiTree(&(*T)->lchild); /* 销毁左孩子子树 */
		if((*T)->rchild) /* 有右孩子 */
			DestroyBiTree(&(*T)->rchild); /* 销毁右孩子子树 */
		free(*T); /* 释放根结点 */
		*T=NULL; /* 空指针赋0 */
	}
}
//用前序遍历，向二叉树输入数据
//#表示空树 
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

//二叉树是否为空,空的话返回true 
int BiTreeEmpty(BiTree T)
{
	if(T)
		return FALSE;
	else
		return TRUE;
} 

#define ClearBiTree DestroyBiTree

//返回二叉树的深度
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

//如果二叉树不为空，则返回根 
char Root(BiTree T)
{
	if(BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

//返回p所指的值 
char Value(BiTree p)
{
	return p->data;
}

//给p所指的结点赋新值 
void Assign(BiTree p,char value)
{
	p->data=value;
}

//前序遍历 
void PreOrderTraverse(BiTree T)
{
	if( T == NULL )
		return;
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);	
}

//中序遍历 
void InOrderTraverse(BiTree T)
{
	if( T == NULL )
		return;
	InOrderTraverse(T->lchild);
	printf("%c",T->data);
	InOrderTraverse(T->rchild);	
}

//后序遍历 
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

	printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	e1=Root(T);
	printf("二叉树的根为: %c\n",e1);

	printf("\n前序遍历二叉树:");
	PreOrderTraverse(T);
	printf("\n中序遍历二叉树:");
	InOrderTraverse(T);
	printf("\n后序遍历二叉树:");
	PostOrderTraverse(T);
	ClearBiTree(&T);	//相当于摧毁二叉树 
	printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T);
	if(!i)
		printf("树空，无根\n");
	
	return 0;
}
