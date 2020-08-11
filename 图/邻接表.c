#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵���,Ӧ���û����� */

//�ڽӱ�
//����ͼ��ҪΪi,j�����ڽӵ㴴���µĽ��
//������ͼ���ǽ�j���뵽i�ı�ͷ 

typedef struct EdgeNode		//�߱��� 
{
	int adjvex;			//�ڽӵ��򣬴洢�ö����Ӧ���±� 
	int weight;			//Ȩֵ������ͼ����Ҫ 
	struct EdgeNode *next;	
}EdgeNode;

typedef struct VertexNode	//������� 
{
	char data;				//������Ϣ 
	EdgeNode *firstedge;	//�߱�ͷָ�� 
}VertexNode , AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges;	
}GraphAdjList;
//��������ͼ���ڽӱ� 
void CreateALGraph1(GraphAdjList *G)
{
	int i , j , k;
	EdgeNode *e;
	printf("���붥�����ͱ���:\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	for(i=0; i < G-> numVertexes; i++)		//��������� 
	{
		scanf("%c",&G->adjList[i].data);	/*���붥����Ϣ */
		G->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(k=0; k < G->numEdges ; k++)
	{
		printf("�����(vi,vj)�ϵĶ������:\n");
		scanf("%d %d",&i,&j);
//�������ͷ�巨,��Ϊ��������������߶�Ҫ�����µ��ڽӵ� 
		e = (EdgeNode *)malloc(sizeof(EdgeNode));	/* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex = j;		/* �ڽ����Ϊj */  
		e->next = G->adjList[i].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */ 
		G->adjList[i].firstedge=e;			/* ����ǰ�����ָ��ָ��e */   

		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex=i;					/* �ڽ����Ϊi */                         
		e->next=G->adjList[j].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */
		G->adjList[j].firstedge=e;		/* ����ǰ�����ָ��ָ��e */   
	}
}
//��������ͼ���ڽӱ� 
void CreateALGraph2(GraphAdjList *G)
{
	int i , j , k;
	EdgeNode *e;
	printf("���붥�����ͱ���:\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	for(i=0; i < G-> numVertexes; i++)		//��������� 
	{
		scanf("%c",&G->adjList[i].data);	/*���붥����Ϣ */
		G->adjList[i].firstedge=NULL; 	/* ���߱���Ϊ�ձ� */
	}
	
	for(k=0; k < G->numEdges ; k++)
	{
		printf("�����(vi,vj)�ϵĶ������:\n");
		scanf("%d %d",&i,&j);
//�������ͷ�巨,��Ϊ���������԰�j����i�ı�ͷ 
		e = (EdgeNode *)malloc(sizeof(EdgeNode));	/* ���ڴ�����ռ�,���ɱ߱��� */
		e->adjvex = j;		/* �ڽ����Ϊj */  
		e->next = G->adjList[i].firstedge;	/* ��e��ָ��ָ��ǰ������ָ��Ľ�� */ 
		G->adjList[i].firstedge=e;			/* ����ǰ�����ָ��ָ��e */   

	}
}
//��ӡ��Ϣ 
void printfL(GraphAdjList *G)
{
	int i , j ;
	EdgeNode *node;		//�߱�ָ���� 
	for(i = 0 ; i < G->numVertexes;i++)
	{
		printf("%d(%c):",i,G->adjList[i].data);		//��ӡ������Ϣ 
		node = G->adjList[i].firstedge;			//�߱�ָ��ָ���ٱ߱��� 
		while(node != NULL )	//ֱ���ö�����ڱ���Ϊ�� 
		{						//��ӡ�ڽӵ��Ӧ�±�Ͷ�Ӧ���� 
			printf("%d(%c)",node->adjvex,G->adjList[node->adjvex].data);
			node = node->next;		//ָ����һ�ڽӵ� 
		}
		printf("\n");
	} 
}
int main(void)
{    
	GraphAdjList G;    
	CreateALGraph2(&G);
	printfL(&G);
	return 0;
}
