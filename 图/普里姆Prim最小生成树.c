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

//Prim最小生成树，是根据顶点开始，逐步寻顶点间边的权值最小
//设置两个数组，adjvex存顶点下标，postcost存边最小权值,权值也得初始化为无穷 
//必须先设个顶点，权值为0开始，起点也为0
//初始化两个数组，将顶点权值全部初始化从0开始 
//之后就一个大循环包两个小循环，第一个则循环全部顶点，找出权值最小的边min，把下标存入k
//完了就打印顶点间的权值最小边
//第二个循环则循环全部顶点，找出下标为k顶点的各边权值小于未加入生成树权值的，存入lowcost，k也存入adjvex 


typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* 构件图 */
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

/* Prim算法生成最小生成树  */
void MiniSpanTree_Prim(MGraph G)
{
	int min , i , j,k;
	int adjvex[MAXVEX];			//相关顶点下标 
	int lowcost[MAXVEX];		//顶点间边的最小权值 
	lowcost[0] = 0;				//表示从V0开始，权值为0 
	adjvex[0] = 0;				//初始化第一个顶点下标为0 	
	for(i = 1;i<G.numVertexes;i++)		//循环下标为0外的全部顶点 
	{
		lowcost[i] = G.arc[0][i];		//将V0顶点与之有边的权值存入 
		adjvex[i] = 0;					//初始化都为V0的下标 
	}
	for( i = 1;i<G.numVertexes;i++)
	{
		min = MAX;			//初始化最小权值为无穷 
		j=1;
		k=0;
		
		while(j<G.numVertexes)		//循环全部顶点 
		{	//找出权值最小的边 
			if(lowcost[j]!=0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		
		printf("(%d,%d)\n",adjvex[k],k);	//打印顶点边中权值最小的边 
		lowcost[k] = 0;			//将顶点设置为0，记为顶点已完成任务 
	
		for(j=1;j<G.numVertexes;j++)		//循环全部顶点 
		{	//若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值 
			if(lowcost[j] != 0 &&G.arc[k][j] < lowcost[j])	
			{
				lowcost[j] = G.arc[k][j];	//将较小权值存入lowcost 
				adjvex[j] = k;			//将下标为k的顶点存入adjvex 
			}
		}
	}
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
  
	return 0;
 
}
