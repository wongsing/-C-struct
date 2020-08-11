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

//二叉排序树的查找。插入。删除 

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

//二叉树的链表结点结构 
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild , *rchild;
}BiTNode , *BiTree;


//二叉排序树的查找，递归查找是否存在key 
//指针f指向T的双亲，其初始调用值为NULL
//若查找成功，p则指向该数据元素结点，并返回true
//否则指针p指向查找路径上访问的最后一个结点并返回FALSE 
Status SearchBST(BiTree T , int key , BiTree f ,BiTree *p)
{
	if(!T)		//查找不成功，二叉树是否到叶子结点 
	{
		*p = f;		//如果二叉树为空，T指向根节点 
		return FALSE;
	}
	else if( key == T->data)
	{
		*p = T;
		return TRUE;
	}
	else if( key < T->data)
		return SearchBST(T->lchild, key,T,p);	//左子树中继续寻找 
	else
		return SearchBST(T->rchild, key,T,p);	//右子树中继续寻找 		
}


/*  当二叉排序树T中不存在关键字等于key的数据元素时， */
/*  插入key并返回TRUE，否则返回FALSE */
Status InsertBST(BiTree *T, int key)
{
	BiTree p,s;
	if(!SearchBST(*T,key,NULL,&p))		//如果查找不成功 
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if(!p)			//如果p不存在 
			*T = s;		//则插入s为新结点 
		else if(key < p->data)	//二叉树性质 
			p->lchild = s;		//插入为p的左孩子 
		else
			p->rchild = s;		//插入为p的右孩子 
		return TRUE;
	}
	else
		return FALSE;
}


/* 从二叉排序树中删除结点p，并重接它的左或右子树。 */
//分三种情况：只删除叶节点，或者删除结点只有左或右子树，还有删除结点有左右子树
//一二种情况，哪边为空，重新接另外一边即可
//第三种，则需要令p指向删除结点q，s指向q的左孩子，然后一直向右，p=s;
//然后把s的data给到q的data，判断p与q是否一样，不一样则重接p的右子树，反之接左子树 
Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild == NULL)	//右子树为空则需要重新接它的左子树 
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if((*p)->lchild == NULL)	//左子树为空则需要重新接它的右子树 
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else	//左右子树都不为空
	{
		q = *p;
		s = (*p)->lchild;
		while( s->rchild)	//先转左然后向右到尽头，找待删结点的前驱 
		{
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;	//s指向被删结点的直接前驱 
		if(q != *p)
			q->rchild = s->lchild;		//重接q的右子树 
		else
			q->lchild = s->lchild;		//重接q的左子树 
		free(s);		
	}
	return TRUE;
}


/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点, */
/* 并返回TRUE；否则返回FALSE。 */
Status DeleteBST(BiTree *T , int key)
{
	if(!*T)		//如果T不存在 
		return FALSE;
	else
	{
		if( key == (*T)->data)		//找到key 
			return Delete(T);
		else if(key < (*T)->data)
			return  DeleteBST(&(*T)->lchild , key);	//从左子树继续找 
		else
			return  DeleteBST(&(*T)->rchild , key);	//从右子树继续找 
	}
}

int main(void)
{    
	int i;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	BiTree T=NULL;
	
	for(i=0;i<10;i++)
	{
		InsertBST(&T, a[i]);
	}
	DeleteBST(&T,93);
	DeleteBST(&T,47);
    printf("本样例建议断点跟踪查看二叉排序树结构");
	return 0;
}
