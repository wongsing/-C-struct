#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数,应由用户定义 */

//邻接表
//无向图需要为i,j两个邻接点创建新的结点
//而有向图则是将j插入到i的表头 

typedef struct EdgeNode		//边表结点 
{
	int adjvex;			//邻接点域，存储该顶点对应的下标 
	int weight;			//权值，非网图则不需要 
	struct EdgeNode *next;	
}EdgeNode;

typedef struct VertexNode	//顶点表结点 
{
	char data;				//顶点信息 
	EdgeNode *firstedge;	//边表头指针 
}VertexNode , AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges;	
}GraphAdjList;
//构建无向图的邻接表 
void CreateALGraph1(GraphAdjList *G)
{
	int i , j , k;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	for(i=0; i < G-> numVertexes; i++)		//构建顶点表 
	{
		scanf("%c",&G->adjList[i].data);	/*输入顶点信息 */
		G->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(k=0; k < G->numEdges ; k++)
	{
		printf("输入边(vi,vj)上的顶点序号:\n");
		scanf("%d %d",&i,&j);
//单链表的头插法,因为是无向的所以两边都要建立新的邻接点 
		e = (EdgeNode *)malloc(sizeof(EdgeNode));	/* 向内存申请空间,生成边表结点 */
		e->adjvex = j;		/* 邻接序号为j */  
		e->next = G->adjList[i].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */ 
		G->adjList[i].firstedge=e;			/* 将当前顶点的指针指向e */   

		e=(EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间,生成边表结点 */
		e->adjvex=i;					/* 邻接序号为i */                         
		e->next=G->adjList[j].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */
		G->adjList[j].firstedge=e;		/* 将当前顶点的指针指向e */   
	}
}
//构建有向图的邻接表 
void CreateALGraph2(GraphAdjList *G)
{
	int i , j , k;
	EdgeNode *e;
	printf("输入顶点数和边数:\n");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	for(i=0; i < G-> numVertexes; i++)		//构建顶点表 
	{
		scanf("%c",&G->adjList[i].data);	/*输入顶点信息 */
		G->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(k=0; k < G->numEdges ; k++)
	{
		printf("输入边(vi,vj)上的顶点序号:\n");
		scanf("%d %d",&i,&j);
//单链表的头插法,因为是有向所以把j插入i的表头 
		e = (EdgeNode *)malloc(sizeof(EdgeNode));	/* 向内存申请空间,生成边表结点 */
		e->adjvex = j;		/* 邻接序号为j */  
		e->next = G->adjList[i].firstedge;	/* 将e的指针指向当前顶点上指向的结点 */ 
		G->adjList[i].firstedge=e;			/* 将当前顶点的指针指向e */   

	}
}
//打印信息 
void printfL(GraphAdjList *G)
{
	int i , j ;
	EdgeNode *node;		//边表指针结点 
	for(i = 0 ; i < G->numVertexes;i++)
	{
		printf("%d(%c):",i,G->adjList[i].data);		//打印顶点信息 
		node = G->adjList[i].firstedge;			//边表指针指向临边表域 
		while(node != NULL )	//直到该顶点的邻表域为空 
		{						//打印邻接点对应下标和对应顶点 
			printf("%d(%c)",node->adjvex,G->adjList[node->adjvex].data);
			node = node->next;		//指向下一邻接点 
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
