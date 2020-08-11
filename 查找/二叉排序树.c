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

//�����������Ĳ��ҡ����롣ɾ�� 

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */ 

//��������������ṹ 
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild , *rchild;
}BiTNode , *BiTree;


//�����������Ĳ��ң��ݹ�����Ƿ����key 
//ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
//�����ҳɹ���p��ָ�������Ԫ�ؽ�㣬������true
//����ָ��pָ�����·���Ϸ��ʵ����һ����㲢����FALSE 
Status SearchBST(BiTree T , int key , BiTree f ,BiTree *p)
{
	if(!T)		//���Ҳ��ɹ����������Ƿ�Ҷ�ӽ�� 
	{
		*p = f;		//���������Ϊ�գ�Tָ����ڵ� 
		return FALSE;
	}
	else if( key == T->data)
	{
		*p = T;
		return TRUE;
	}
	else if( key < T->data)
		return SearchBST(T->lchild, key,T,p);	//�������м���Ѱ�� 
	else
		return SearchBST(T->rchild, key,T,p);	//�������м���Ѱ�� 		
}


/*  ������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ�� */
/*  ����key������TRUE�����򷵻�FALSE */
Status InsertBST(BiTree *T, int key)
{
	BiTree p,s;
	if(!SearchBST(*T,key,NULL,&p))		//������Ҳ��ɹ� 
	{
		s = (BiTree)malloc(sizeof(BiTNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		if(!p)			//���p������ 
			*T = s;		//�����sΪ�½�� 
		else if(key < p->data)	//���������� 
			p->lchild = s;		//����Ϊp������ 
		else
			p->rchild = s;		//����Ϊp���Һ��� 
		return TRUE;
	}
	else
		return FALSE;
}


/* �Ӷ�����������ɾ�����p�����ؽ���������������� */
//�����������ֻɾ��Ҷ�ڵ㣬����ɾ�����ֻ�����������������ɾ���������������
//һ����������ı�Ϊ�գ����½�����һ�߼���
//�����֣�����Ҫ��pָ��ɾ�����q��sָ��q�����ӣ�Ȼ��һֱ���ң�p=s;
//Ȼ���s��data����q��data���ж�p��q�Ƿ�һ������һ�����ؽ�p������������֮�������� 
Status Delete(BiTree *p)
{
	BiTree q,s;
	if((*p)->rchild == NULL)	//������Ϊ������Ҫ���½����������� 
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if((*p)->lchild == NULL)	//������Ϊ������Ҫ���½����������� 
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else	//������������Ϊ��
	{
		q = *p;
		s = (*p)->lchild;
		while( s->rchild)	//��ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ�� 
		{
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;	//sָ��ɾ����ֱ��ǰ�� 
		if(q != *p)
			q->rchild = s->lchild;		//�ؽ�q�������� 
		else
			q->lchild = s->lchild;		//�ؽ�q�������� 
		free(s);		
	}
	return TRUE;
}


/* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��, */
/* ������TRUE�����򷵻�FALSE�� */
Status DeleteBST(BiTree *T , int key)
{
	if(!*T)		//���T������ 
		return FALSE;
	else
	{
		if( key == (*T)->data)		//�ҵ�key 
			return Delete(T);
		else if(key < (*T)->data)
			return  DeleteBST(&(*T)->lchild , key);	//�������������� 
		else
			return  DeleteBST(&(*T)->rchild , key);	//�������������� 
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
    printf("����������ϵ���ٲ鿴�����������ṹ");
	return 0;
}
