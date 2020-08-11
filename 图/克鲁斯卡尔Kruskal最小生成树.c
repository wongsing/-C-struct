#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

//Kruskal生成最小树---根据边的最小权值开始
//需要构建边集数组，然后把邻接矩阵转换为边集数组，并且再按照权值来排序
//之后得判断是否存在回路，即顶点和尾点是否相同
//最后直接遍历输出 

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

#define MAXEDGE 20
#define MAXVEX 20
#define MAX 65535

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef struct
{
	int begin;
	int end;
	int weight;
}Edge;   /* 对边集数组Edge结构的定义 */

/* 构件图 */
void CreateMGraph(MGraph *G)
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges=15;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = MAX;
		}
	}

	G->arc[0][1]=10;
	G->arc[0][5]=11; 
	G->arc[1][2]=18; 
	G->arc[1][8]=12; 
	G->arc[1][6]=16; 
	G->arc[2][8]=8; 
	G->arc[2][3]=22; 
	G->arc[3][8]=21; 
	G->arc[3][6]=24; 
	G->arc[3][7]=16;
	G->arc[3][4]=20;
	G->arc[4][7]=7; 
	G->arc[4][5]=26; 
	G->arc[5][6]=17; 
	G->arc[6][7]=19; 

	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/* 交换权值 以及头和尾 */
void Swapn(Edge *edges,int i, int j)
{
	int temp;
	temp = edges[i].begin;
	edges[i].begin = edges[j].begin;
	edges[j].begin = temp;
	temp = edges[i].end;
	edges[i].end = edges[j].end;
	edges[j].end = temp;
	temp = edges[i].weight;
	edges[i].weight = edges[j].weight;
	edges[j].weight = temp;
}

/* 对权值进行排序 */
void sort(Edge edges[],MGraph *G)
{
	int i, j;
	for(i=0;i<G->numEdges;i++)
	{
		for(j=i+1;j<G->numEdges;j++)
		{
			if(edges[i].weight > edges[j].weight)
				Swapn(edges, i , j);
		}
	}
	printf("权排序之后的为:\n");
	for(i=0;i<G->numEdges;i++)
		printf("(%d, %d)  %d\n",edges[i].begin, edges[i].end, edges[i].weight);
}

/* 查找连线顶点的尾部下标 */
int Find(int *parent, int f)
{
	while(parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}

/* 生成最小生成树 */
void MiniSpanTree_Kruskal(MGraph G)
{
	int i , n , m;
	Edge edges[MAXEDGE];		//边集数组 
	int parent[MAXVEX];			//判断边与边是否存在回路 
	
		/* 用来构建边集数组并排序********************* */
	for ( i = 0; i < G.numVertexes-1; i++)
	{
		for (j = i + 1; j < G.numVertexes; j++)
		{
			if (G.arc[i][j]<MAX)
			{
				edges[k].begin = i;
				edges[k].end = j;
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}
	sort(edges, &G);
	/* ******************************************* */
	
		
	for(i=0;i<G.numEdges;i++)	//初始化 
		parent[i] = 0;
		
		
	for(i=0;i<G.numEdges;i++)	//循环每一条边 
	{
		n = Find(parent,edges[i].begin);	
		m = Find(parent,edges[i].end);
		if(n!=m)		
		{
			parent[n] = m;		//将边的结尾顶点放入下标为起点的parent中 
			printf("(%d, %d)  %d",edges[i].begin, edges[i].end, edges[i].weight);
		}	
	}
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
	return 0;
}
