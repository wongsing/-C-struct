#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 30
#define MAXVEX 30
#define MAX 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */  

int *etv,*ltv; /* 事件最早发生时间和最迟发生时间数组，全局变量 */
int *stack2;   /* 用于存储拓扑序列的栈 */
int top2;	   /* 用于stack2的指针 */

/* 邻接矩阵结构 */
typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

/* 邻接表结构****************** */
typedef struct EdgeNode /* 边表结点  */
{
	int adjvex;    /* 邻接点域，存储该顶点对应的下标 */
	int weight;		/* 用于存储权值，对于非网图可以不需要 */
	struct EdgeNode *next; /* 链域，指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
	int in;	/* 顶点入度 */
	int data; /* 顶点域，存储顶点信息 */
	EdgeNode *firstedge;/* 边表头指针 */
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList; 
	int numVertexes,numEdges; /* 图中当前顶点数和边数 */
}graphAdjList,*GraphAdjList;
/* **************************** */


void CreateMGraph(MGraph *G)/* 构件图 */
{
	int i, j;
	/* printf("请输入边数和顶点数:"); */
	G->numEdges=13;
	G->numVertexes=10;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j]=MAX;
		}
	}

	G->arc[0][1]=3;
	G->arc[0][2]=4; 
	G->arc[1][3]=5; 
	G->arc[1][4]=6; 
	G->arc[2][3]=8; 
	G->arc[2][5]=7; 
	G->arc[3][4]=3;
	G->arc[4][6]=9; 
	G->arc[4][7]=4;
	G->arc[5][7]=6; 
	G->arc[6][9]=2;
	G->arc[7][8]=5;
	G->arc[8][9]=3;

}

/* 利用邻接矩阵构建邻接表 */
void CreateALGraph(MGraph G,GraphAdjList *GL)
{
	int i,j;
	EdgeNode *e;

	*GL = (GraphAdjList)malloc(sizeof(graphAdjList));

	(*GL)->numVertexes=G.numVertexes;
	(*GL)->numEdges=G.numEdges;
	for(i= 0;i <G.numVertexes;i++) /* 读入顶点信息，建立顶点表 */
	{
		(*GL)->adjList[i].in=0;
		(*GL)->adjList[i].data=G.vexs[i];
		(*GL)->adjList[i].firstedge=NULL; 	/* 将边表置为空表 */
	}
	
	for(i=0;i<G.numVertexes;i++) /* 建立边表 */
	{ 
		for(j=0;j<G.numVertexes;j++)
		{
			if (G.arc[i][j]!=0 && G.arc[i][j]<INFINITY)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* 邻接序号为j */   
				e->weight=G.arc[i][j];
				e->next=(*GL)->adjList[i].firstedge;	/* 将当前顶点上的指向的结点指针赋值给e */
				(*GL)->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e  */  
				(*GL)->adjList[j].in++;
				
			}
		}
	}	
}

/* 拓扑排序(改进) */
Status TopologicalSort(GraphAdjList GL)
{    /* 若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0。 */    
	int i , k,gettop;
	EdgeNode *e;
	int top = 0;
	int count = 0;
	int *stack;
	stack = (int *)malloc(GL->numVertexes * sizeof(int));
	
	for(i=0;i<GL->numVertexes;i++)
		if(GL->adjList[i].in == 0 )
			stack[++top] = i;
			
	top2 = 0;
	etv = (int *)malloc(GL->numVertexes * sizeof(int));
	for(i=0;i<GL->numVertexes;i++)
		etv[i] = 0;
	stack2 = (int *)malloc(GL->numVertexes * sizeof(int));
	
	while(top != 0)
	{
		gettop = stack[top--];
		count++;
		stack2[++top2] = gettop;
		
		for(e = GL->adjList[gettop].firstedge;e;e=e->next)
		{
			k = e->adjvex;
			if(!(--GL->adjList[k].in))
				stack[++top] = k;
			if((etv[gettop]+e->weight) > etv[k])
				etv[k] = etv[gettop] + e->weight;
		}
	}
	if(count < GL->numVertexes)
		return ERROR;
	else
		return OK;
}

/* 求关键路径,GL为有向网，输出G的各项关键活动 */
void CriticalPath(GraphAdjList GL) 
{
	EdgeNode *e;
	int i , gettop , k , j;
	int ete , lte;
	TopologicalSort(GL);
	ltv = (int *)malloc(GL->numVertexes * sizeof(int));
	
	for(i=0; i<GL->numVertexes; i++)
		ltv[i] = etv[GL->numVertexes-1];
		
	while(top2 != 0)
	{
		gettop = stack2[top2--];
		for(e = GL->adjList[gettop].firstegde;e;e=e->next)
		{
			k = e->adjvex;
			if(ltv[k]-e->weight < ltv[gettop])
				ltv[gettop] = ltv[k] - e->weight;
		}
	}
	
	for(j=0; j<GL->numVertexes; j++)
	{
		for(e = GL->adjList[j].firstegde;e;e=e->next)
		{
			k = e->adjvex;
			ete = etv[j];
			lte = ltv[k] - weight;
			if( ete == lte)
				printf("<v%d,v%d> length: %d, ",GL->adjList[j].data,GL->adjList[k].data,e->weight);
		}
	}
}

int main(void)
{    
	MGraph G;    
	GraphAdjList GL;    
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	CriticalPath(GL);
	return 0;
}
