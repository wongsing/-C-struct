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
#define MAXVEX 20
#define MAX 65535

//Dijkstra最短路径---找出顶点与各顶点的最短路径，是一步步求的 
//初始化和大循环中的第一个循环 都和 Prim最小生成树一样 
//设置两个数组，p存储顶点的前驱，路径数组，D储存最小路径长度
//与prim一样，要初始化，D存v0与各顶点路径，P为-1，设final识别是否得到最短路径
//与prim大循环第一个循环，要找出与v0最近的顶点
//之后就要修正路径，看是否最小路径+经过顶点比原本路径短的话，修正 
 
 
typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef int Patharc[MAXVEX];    /* 用于存储最短路径下标的数组 */
typedef int ShortPathTable[MAXVEX];/* 用于存储到各点最短路径的权值和 */

/* 构件图 */
void CreateMGraph(MGraph *G)
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges=16;
	G->numVertexes=9;

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
				G->arc[i][j] = G->arc[j][i] = MAX;
		}
	}

	G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 

	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;

	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;

	G->arc[7][8]=4;


	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/*  Dijkstra算法，求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v] */    
/*  P[v]的值为前驱顶点下标,D[v]表示v0到v的最短路径长度和 */  
//初始化和大循环中的第一个循环 都和 Prim最小生成树一样 
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D)
{
	int i , j , k , min;
	int final[MAXVEX];		//final[i]= 1表名已经得到最短路径 

	for(i = 0 ; i < G.numVertexes;i++)	//初始化 
	{
		(*P)[i] = -1;				//初始化路径数组 
		(*D)[i]	= G.arc[v0][i];		//将与v0有连线的点加上权值 
		final[i] = 0;				//全部顶点初始化为未知最短路径状态 
	}
	
		final[v0] = 1;			//顶点路径已知，v0-v0为0 
		(*D)[v0] = 0;			//顶点权值为0 
		
	for(i=1;i<G.numVertexes;i++)	//开始主循环，每次循环得到v0到某顶点的最短路径	
	{
		min = MAX;			//初始化最短路径为无穷 
	
		for( j = 0 ; j < G.numVertexes ; j++ )	//找到与v0最近的顶点 
		{
			if(!final[j] && (*D)[j] < min)
			{
				min =  (*D)[j];
				k = j;
			}
		}	
			final[k] = 1;		//表示已经找到最近的顶点设为1
			 
		for( j = 0 ; j < G.numVertexes ; j++ )		//修正当前最短路径 
		{
			if(!final[j] && (min+G.arc[k][j]<(*D)[j]))
		
			{ /*  说明找到了更短的路径，修改D[j]和P[j] */
				(*D)[j] = min + G.arc[k][j];  /* 修改当前路径长度 */               
				(*P)[j]=k;        
			}       		
		}
	}
}

int main(void)
{   
	int i,j,v0;
	MGraph G;    
	Patharc P;    
	ShortPathTable D; /* 求某点到其余各点的最短路径 */   
	v0=0;
	
	CreateMGraph(&G);
	
	ShortestPath_Dijkstra(G, v0, &P, &D);  

	printf("最短路径倒序如下:\n");    
	for(i=1;i<G.numVertexes;++i)   
	{       
		printf("v%d - v%d : ",v0,i);
		j=i;
		while(P[j]!=-1)
		{
			printf("%d ",P[j]);
			j=P[j];
		}
		printf("\n");
	}    
	printf("\n源点到各顶点的最短路径长度为:\n");  
	for(i=1;i<G.numVertexes;++i)        
		printf("v%d - v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);     
	return 0;
}
