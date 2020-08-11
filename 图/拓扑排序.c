#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 14
#define MAX 65535

//拓扑排序：有n个顶点，vi到vj有一条路径。则vi一定在vj前，表示一个工程的有向图
//原理：从AOV网中选择一个入度为0的顶点输出，然后删去此顶点，并删除以此顶点为尾的狐
//重复直到AOV网中不存在入度为0的顶点为止--->用栈 

//首先需要构建栈数组，大小与顶点数相同，将入度为0的顶点入栈
//然后先出栈，打印此顶点，统计输出点数，然后对该顶点的狐表遍历，将邻接点入度-1，直到等于0入栈
//最后count小于顶点数，就存在环 


typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

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
	G->numEdges=MAXEDGE;
	G->numVertexes=MAXVEX;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			G->arc[i][j]=0;
		}
	}

	G->arc[0][4]=1;
	G->arc[0][5]=1; 
	G->arc[0][11]=1; 
	G->arc[1][2]=1; 
	G->arc[1][4]=1; 
	G->arc[1][8]=1; 
	G->arc[2][5]=1; 
	G->arc[2][6]=1;
	G->arc[2][9]=1;
	G->arc[3][2]=1; 
	G->arc[3][13]=1;
	G->arc[4][7]=1;
	G->arc[5][8]=1;
	G->arc[5][12]=1; 
	G->arc[6][5]=1; 
	G->arc[8][7]=1;
	G->arc[9][10]=1;
	G->arc[9][11]=1;
	G->arc[10][13]=1;
	G->arc[12][9]=1;

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
			if (G.arc[i][j]==1)
			{
				e=(EdgeNode *)malloc(sizeof(EdgeNode));
				e->adjvex=j;					/* 邻接序号为j  */                        
				e->next=(*GL)->adjList[i].firstedge;	/* 将当前顶点上的指向的结点指针赋值给e */
				(*GL)->adjList[i].firstedge=e;		/* 将当前顶点的指针指向e  */  
				(*GL)->adjList[j].in++;
				
			}
		}
	}	
}

/* 拓扑排序，若GL无回路，则输出拓扑排序序列并返回1，若有回路返回0。 */
Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int i , k , gettop;
	int top = 0;		//栈指针下标 
	int count = 0;		//输出顶点个数计数 
	
	int *stack;			//建栈 
	stack = ( int *)malloc(GL->numVertexes * sizeof(int));
	
	for(i=0; i<GL->numVertexes ; i++)	//初始化，将入度为0的顶点入栈 
		if(GL->adjList[i].in == 0 )
			stack[++top] = i;
			
	while(top!=0)
	{
		gettop = stack[top--];		//出栈 
		printf("%d-> ",GL->adjList[gettop].data);	//打印顶点 
		count++;		
		//对顶点的狐表遍历/边表 
		for(e = GL->adjList[gettop].firstedge;e;e=e->next)
		{
			k = e->adjvex;
			if(!(--GL->adjList[k].in))		//将k号顶点邻接点的入度减1 
				stack[++top] = k;		//若为0则入栈， 
		}
	}
	if(count < GL->numVertexes)		//如果count小于顶点数，则存在环 
		return ERROR;
	else
		return OK;
}

int main(void)
{    
	MGraph G;  
	GraphAdjList GL; 
	int result;   
	CreateMGraph(&G);
	CreateALGraph(G,&GL);
	result=TopologicalSort(GL);
	printf("result:%d",result);

	return 0;
}

