#include <stdio.h>    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
#define MAX 65535

//邻接矩阵（无向和有向）
//首先先确定顶点和边或者狐的数，然后遍历输入顶点，做好顶点表
//之后就初始化边表：无向图则全为0，有向图主对角线为0，其余为无穷
//然后就开始输入边数组元素 v,j,k(权值)!注意无向是矩阵对称，而有向只输入相应的就可 
//输出的话 先输出顶点表 然后再遍历输出边表 


//矩阵结构 
typedef struct
{
	char vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes , numEdges;
}MGraph;
//无向图 
void CreateMGraph1(MGraph *G)
{
	int i , j , k ,w;
	printf("输入顶点数和边数:");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	printf("\n输入顶点:\n");
	for(i=0;i < G->numVertexes ; i++)		//读入顶点信息，建立定点表		
		{
			scanf("%c",&G->vexs[i]);	
			printf("顶点为：%c\n",G->vexs[i]);			
		}		

	for(i=0;i < G->numVertexes ; i++)	//初始化邻接矩阵 
		for(j=0;j < G->numVertexes ; j++)
			G->arc[i][j] = 0;	//无向图用0初始化，有向图有权值的话则用无穷初始化
	
	for(k = 0 ; k <G->numEdges ; k++)	//读取边数，建立邻接矩阵 
	{
		printf("输入边(Vi,Vj)上的下标i，下标j和权w:");
		scanf("%d %d %d",&i,&j,&w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];		//无向图是矩阵对称		
	}		
}
//有向图 
void CreateMGraph2(MGraph *G)
{
	int i , j , k ,w;
	printf("输入顶点数和边数:");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	for(i=0;i < G->numVertexes ; i++)		//读入顶点信息，建立定点表 
		scanf("%c",&G->vexs[i]);
	for(i=0;i < G->numVertexes ; i++)	//初始化邻接矩阵 
		for(j=0;j < G->numVertexes ; j++)
			if(i == j)	
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = MAX;		//ij相等用0初始化，有向图有权值的话则用无穷初始化
	
	for(k = 0 ; k <G->numEdges ; k++)	//读取边数，建立邻接矩阵 
	{
		printf("输入边(Vi,Vj)上的下标i，下标j和权w:");
		scanf("%d %d %d",&i,&j,&w);
		G->arc[i][j] = w;
//		G->arc[j][i] = G->arc[i][j];		//无向图是矩阵对称		
	}		
}

void printfL(MGraph *g) {
    //输出图的信息
    printf("表为 :\n");
    int i = 0 , j ;
    //先打印行标题；顶点标题
    for (i = 0; i < g->numVertexes + 1; i++) {
        if (i > 0) {
            printf("%c\t", g->vexs[i - 1]);
        } else {
            printf("\\\t");
        }
    }
    printf("\n");
    for (i = 0; i < g->numVertexes; i++) {
        printf("%c\t", g->vexs[i]);
        for ( j = 0; j < g->numVertexes; j++) {
            printf("%d\t", g->arc[i][j]);
        }
        printf("\n");
    }
}
int main()
{
	MGraph G;
	CreateMGraph1(&G);
	printf("无向图的邻接矩阵\n");
	printfL(&G);
	printf("*************\n");
	printf("有向图的邻接矩阵\n");	
	printf("*************\n");
	CreateMGraph2(&G);
	printfL(&G);
	return 0;	
}
