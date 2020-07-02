#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

//二叉树的顺序结构实现
 
#define MAXSIZE 100 /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */
#define Nil 0
#define OK 1
#define ERROR 0


typedef struct
{
	int level,order;	//结点的层、本层序号(按满二叉树计算) 
}Position;

typedef int SqBiTree[MAX_TREE_SIZE]; /* 0号单元存储根结点  */

int visit(int c)
{
	printf("%d ",c);
	return OK;
}
//构造空二叉树，T是固定数组 
int InitBiTree(SqBiTree T)
{
	int i ;
	for(i=0;i<MAX_TREE_SIZE;i++)
		T[i] = Nil;
	return OK; 
}
//按层序次序输入二叉树各结点的值,构造顺序结构的二叉树 
int CreateBiTree(SqBiTree T)
{
	int i = 0;
	printf("请按层序输入结点的值(整型)，0表示空结点，输999结束。结点数≤%d:\n",MAX_TREE_SIZE);
	while(i<10)
	{
		T[i] = i + 1;
		
		if(i!=0 && T[(i+1)/2-1] == Nil && T[i] != Nil)	//此结点不空无双亲且不是根 
		{
			printf("出现无双亲的非根结点%d\n",T[i]);
			exit(ERROR);		
		}
		i++;		
	}
	while(i<MAX_TREE_SIZE)	
	{
		T[i] = Nil;		//将空值赋给T的后面结点 
		i++;
	}
	return OK;
}

#define ClearBiTree InitBiTree /* 在顺序存储结构中，两函数完全一样 */

//初始条件二叉树存在 
//检验二叉树是否为空，空的话则返回真 
int BiTreeEmpty(SqBiTree T)
{
	if(T[0] == Nil)
		return OK;
	else
		return ERROR;
}

//初始条件二叉树存在 
//返回二叉树的深度
int BiTreeDepth(SqBiTree T)
{
	int i , j = -1;
	for(i = MAX_TREE_SIZE-1;i>=0;i--)	//找到最后一个结点 
		if(T[i] != Nil)
			break;
	i++;
	do
		j++;
	while(i>=pow(2,j));		//计算2的j次幂 
	return j;	
} 
//用e返回T的根 
int Root(SqBiTree T,int *e)
{
	if(BiTreeEmpty(T))	//如果树为空 
		return ERROR;
	*e = T[0];
	return OK;
}

//返回处于位置e(层，本层序号)的结点的值 
int Value(SqBiTree T,Position e)
{				//2的x-1次幂+本层序号然后再减去一层个数2 
	return T[(int)powl(2,e.level-1)+e.order-2];
}

//给处于位置e(层,本层序号)的结点赋新值value
int Assign(SqBiTree T,Position e,int value)
{
	int i=(int)powl(2,e.level-1)+e.order-2; /* 将层、本层序号转为矩阵的序号 */
	if(value!=Nil&&T[(i+1)/2-1]==Nil) /* 给叶子赋非空值但双亲为空 */
		return ERROR;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) /*  给双亲赋空值但有叶子（不空） */
		return ERROR;
	T[i]=value;
	return OK;	
}

//寻找e的双亲 
int Parent(SqBiTree T , int e)
{
	int i ;
	if(T[0] == Nil)	//空树
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e)
			return T[(i+1)/2-1];	//找到返回双亲 
	return Nil;		//没找到 
}
//寻找e的左孩子 
int LeftChild(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e)
			return T[i*2+1];	//找到返回左孩子
	return Nil;		//没找到	
}

//寻找e的右孩子 
int RightChild(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e)
			return T[i*2+2];	//找到返回右孩子
	return Nil;		//没找到	
}
//寻找e的左兄弟 
int LeftSibling(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e && i%2==0) //找到e并且序号为偶数 
			return T[i-1];	//找到返回左兄弟 
	return Nil;		//没找到	
}
//寻找e的右兄弟 
int RightSibling(SqBiTree T , int e)
{
	int i;
	if(T[0] == Nil);
		return ERROR;
	for(i=1;i<MAX_TREE_SIZE-1;i++)
		if(T[i] == e && i%2) //找到e并且序号为奇数 
			return T[i+1];	//找到返回右兄弟 
	return Nil;		//没找到	
}

//前序遍历调用 
void PreTraverse(SqBiTree T,int e)
{
	visit(T[e]);
	if(T[2*e+1] != Nil)		//若左子树不为空 
		PreTraverse(T,2*e+1);
	if(T[2*e+2] != Nil)		//若右子树不为空 
		PreTraverse(T,2*e+2);		
}
//前序遍历 
int PreOrderTraverse(SqBiTree T)
{
	if(!BiTreeEmpty(T))
		PreTraverse(T,0);
	printf("\n");	
	return OK;
}
//中序遍历调用 
void InTraverse(SqBiTree T,int e)
{

	if(T[2*e+1] != Nil)		//若左子树不为空 
		PreTraverse(T,2*e+1);
	visit(T[e]);
	if(T[2*e+2] != Nil)		//若右子树不为空 
		PreTraverse(T,2*e+2);		
}
//中序遍历 
int InOrderTraverse(SqBiTree T)
{
	if(!BiTreeEmpty(T))
		PreTraverse(T,0);
	printf("\n");	
	return OK;
}
//后序遍历调用 
void PostTraverse(SqBiTree T,int e)
{

	if(T[2*e+1] != Nil)		//若左子树不为空 
		PreTraverse(T,2*e+1);
	if(T[2*e+2] != Nil)		//若右子树不为空 
		PreTraverse(T,2*e+2);
	visit(T[e]);		
}
//后序遍历 
int PostOrderTraverse(SqBiTree T)
{
	if(!BiTreeEmpty(T))
		PreTraverse(T,0);
	printf("\n");	
	return OK;
}
//层次遍历
void LevelOrderTraverse(SqBiTree T)
{
	int i = MAX_TREE_SIZE-1 ,j;
	while(T[i] != Nil)
		i--;		//找到最后一个非空结点的序号 
	for(j=0;j<=i;j++)	//从根结点开始遍历 
		if(T[j] != Nil)	
			visit(T[j]);	//只遍历非空的结点	
	printf("\n");
}
//逐层、按本层序号输出二叉树
void Print(SqBiTree T )
{
	int k , j;
	Position p;
	int e;
	for(j=1;j<=BiTreeDepth(T);j++)
	{
		printf("第%d层：",j);
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
	Position p;		//元素层号和层序号 
	int e;
	SqBiTree T;		
	InitBiTree(T);
	CreateBiTree(T);
	printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%d\n",e);
	else
		printf("树空，无根\n");
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("中序遍历二叉树:\n");
	InOrderTraverse(T);
	printf("后序遍历二叉树:\n");
	PostOrderTraverse(T);
	printf("修改结点的层号3本层序号2。");
	p.level=3;
	p.order=2;
	e=Value(T,p);
	printf("待修改结点的原值为%d请输入新值:50 ",e);
	e=50;
	Assign(T,p,e);
	printf("前序遍历二叉树:\n");
	PreOrderTraverse(T);
	printf("结点%d的双亲为%d,左右孩子分别为",e,Parent(T,e));
	printf("%d,%d,左右兄弟分别为",LeftChild(T,e),RightChild(T,e));
	printf("%d,%d\n",LeftSibling(T,e),RightSibling(T,e));
		Print(T);
	ClearBiTree(T);		//与初始化二叉树一致 
	printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
	i=Root(T,&e);
	if(i)
		printf("二叉树的根为：%d\n",e);
	else
		printf("树空，无根\n");

	return 0;
}

