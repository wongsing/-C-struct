#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 9 /* 存储空间初始分配量 */
#define MAXEDGE 15
#define MAXVEX 9
#define MAX 65535

//邻接矩阵结构 
typedef struct
{	
	char vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

//******************************
//邻接表结构

//边表结点 
typedef struct	EdgeNode
{
	int adjvex;		//邻接点对应下标 
	int weight;		//权值 
	struct EdgeNode *next;
}EdgeNode;

//顶点表结点 
 typedef struct VertexNode
 {
 	int in;		//顶点入度 
 	char data;	//顶点域 
 	EdgeNode *firstedge;	//边表头指针 
 }VertexNode, AdjList[MAXVEX];
 
 typedef struct
 {
 	AdjList adjList;
 	int numVertexes, numEdges;
 }graphAdjList,*GraphAdjList;
 
 //******************************
 
 //****************************
 //队列结构
 typedef struct
 {
 	char data[MAXSIZE];
 	int front;
 	int rear;
 }Queue;
 
 //初始化队列 
 int InitQueue(Queue *Q)
 {
 	Q->front = 0;
 	Q->rear = 0;
 	return OK;
 }
 
 //队列是否为空，空的话返回真
 int QueueEmpty(Queue Q)
 {
 	if(Q.rear == Q.front)
 		return TRUE;
 	else
 		return FALSE;
 }
 
 //如果队列不满，插入新元素
 int EnQueue(Queue *Q,int e)
 {
 	if((Q->rear+1)%MAXSIZE == Q->front)
 		return ERROR;
 	Q->data[Q->rear] = e;
 	Q->rear = (Q->rear+1)%MAXSIZE;
 	return OK;
 }
 
 /* 若队列不空,则删除Q中队头元素,用e返回其值 */
int DeQueue(Queue *Q,int *e)
{	
	if(Q->rear == Q->front)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	return OK;
}
 //****************************
 
 //初始化邻接矩阵 
void CreateMGraph(MGraph *G)
{
	int i, j;

	G->numEdges=15;
	G->numVertexes=9;

	/* 读入顶点信息,建立顶点表 */ 
	G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';


	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j]=0;
		}
	}

	G->arc[0][1]=1;
	G->arc[0][5]=1;

	G->arc[1][2]=1; 
	G->arc[1][8]=1; 
	G->arc[1][6]=1; 
	
	G->arc[2][3]=1; 
	G->arc[2][8]=1; 
	
	G->arc[3][4]=1;
	G->arc[3][7]=1;
	G->arc[3][6]=1;
	G->arc[3][8]=1;

	G->arc[4][5]=1;
	G->arc[4][7]=1;

	G->arc[5][6]=1; 
	
	G->arc[6][7]=1; 

	
	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}
}

/* 利用邻接矩阵构建邻接表 */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i , j;
	EdgeNode *e;
	
	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));
	
	(*GL)->numVertexes = G.numVertexes;
	(*GL)->numEdges = G.numEdges;
	
	for(i=0; i < G.numVertexes ; i++)		/* 将建立顶点表 */
	{
		(*GL)->adjList[i].in = 0;
		(*GL)->adjList[i].data = G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */	 		
	}

	for(i=0; i < G.numVertexes ; i++)		/* 将建立边表 */
	{
		for(j=0;j<G.numVertexes;j++)
		{
			if(G.arc[i][j] == 1)
			{
				e = (EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex = j;		//；邻接序号为j
				e->next = (*GL)->adjList[i].firstedge;	//把j插入到i的表头 
				(*GL)->adjList[i].firstedge = e;
				(*GL)->adjList[j].in++;		//入度加1 
			}
		}
	}		
}

int visited[MAXSIZE]; /* 访问标志的数组 */

/* 邻接表的深度优先递归算法 */
void DFS(GraphAdjList GL, int i)
{
	EdgeNode *p;
	visited[i] = TRUE;
	printf("%c ",GL->adjList[i].data);	//打印顶点
	p = GL->adjList[i].firstedge;
	while(p)
	{
		if(!visited[p->adjvex])
			DFS(GL,p->adjvex);		//对访问的邻接顶点进行递归遍历 
		p = p->next;
	} 
}

/* 邻接表的深度遍历操作 */
void DFSTraverse(GraphAdjList GL)
{
	int i ;
	for(i=0 ;i < GL->numVertexes;i++)
		visited[i] = FALSE;		//初始化，所有顶点都是未遍历过的 
	for(i=0 ;i < GL->numVertexes;i++)
		if(!visited[i])		//对未遍历过的顶点用DFS递归遍历 
			DFS(GL,i);
}

/* 邻接表的广度遍历算法 */
void BFSTraverse(GraphAdjList GL)
{
	int i;
	EdgeNode *p;
	Queue Q;
	for(i = 0; i < GL->numVertexes; i++)
       	visited[i] = FALSE;
    InitQueue(&Q);
    for(i = 0; i < GL->numVertexes; i++)
    {
    	if(!visited[i])
    	{
    		visited[i] = TRUE;
    		printf("%c ",GL->adjList[i].data);		//打印顶点 
    		EnQueue(&Q,i);
    		while(!QueueEmpty(Q))		//如果队列为空则结束 
    		{
    			DeQueue(&Q,&i);
    			p = GL->adjList[i].firstedge;
    			while(p)
    			{
    				if(!visited[p->adjvex])	//若该顶点的邻接顶点未被访问 
    				{
    					visited[p->adjvex] = TRUE;
						printf("%c ",GL->adjList[p->adjvex].data);
						EnQueue(&Q,p->adjvex);	/* 将此顶点入队列 */    					
    				}
    				p = p->next;	/* 指针指向下一个邻接点 */
    			}
    		}
    	}
    }
}

int main(void)
{    
	MGraph G;  
	GraphAdjList GL;    
	CreateMGraph(&G);
	CreateALGraph(G,&GL);

	printf("\n深度遍历:");
	DFSTraverse(GL);
	printf("\n广度遍历:");
	BFSTraverse(GL);
	return 0;
}
