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
#define IMAX 65535
 
//邻接矩阵的DFS和BFS遍历 
//DFS
//邻接矩阵的BFS广度遍历算法，用队列实现，顶点入队读完后出队，邻接顶点入队 


//邻接矩阵结构 
typedef struct 
{
	char vexs[MAXVEX];	//顶点表
	int	 arc[MAXVEX][MAXVEX];	//邻接矩阵
	int numVertexes, numEdges; /* 图中当前的顶点数和边数 */ 
}MGraph;

//循环队列结构 
typedef struct
{
	int data[MAXSIZE];
	int front;			/* 头指针 */
	int rear;			/* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}Queue;

//初始化队列 
int InitQueue(Queue *Q)
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//队列是否为空 
int QueueEmpty(Queue Q)
{
	if(Q.rear == Q.front)
		return TRUE;
	else
		return FALSE;
}

//如果队列不满，添加新元素 
int EnQueue(Queue *Q,int e)
{
	if((Q->rear+1)%MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear]= e;
	Q->rear = (Q->rear+1)%MAXSIZE;
	
	return OK;
}

//如果队列不为空，删除队头元素 
int DeQueue(Queue *Q,int *e)
{
	if(Q->front == Q->rear)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	
	return OK;
}

//建立邻接矩阵 
void CreateMGraph(MGraph *G)
{
	int i, j;

	G->numEdges=15;
	G->numVertexes=9;

	/* 读入顶点信息，建立顶点表 */
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

int visited[MAXVEX]; /* 访问标志的数组 */

//邻接矩阵的深度优先递归算法 
void DFS(MGraph G, int i)
{
	int j;
	visited[i] = TRUE;
	printf("%c ",G.vexs[i]);		//打印顶点
	for(j=0;j<G.numVertexes;j++)
		if(G.arc[i][j] == 1 && !visited[j])
			DFS(G,j); 		//对访问结点的邻接顶点递归调用 
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G)
{
	int i;
	for(i=0 ; i < G.numVertexes; i++)
		visited[i] = FALSE;		//令所有顶点都没有被遍历过 
	for(i=0 ; i < G.numVertexes; i++)
		if(!visited[i])		//对未被遍历的顶点调用DFS，若是连通图，则只访问一次 
			DFS(G,i);
}

// 邻接矩阵的广度遍历算法，用队列实现，顶点入队读完后出队，邻接顶点入队 
void BFSTraverse(MGraph G)
{
	int i , j;
	Queue Q;
	for(i = 0;i<G.numVertexes;i++)
		visited[i] = FALSE;
    InitQueue(&Q);		//初始化队列 
	for(i = 0;i<G.numVertexes;i++)
	{
		if(!visited[i])
		{
			visited[i] = TRUE;
			printf("%c ",G.vexs[i]);
			EnQueue(&Q,i);	
			while(!QueueEmpty(Q))
			{
				DeQueue(&Q,&i);
				for(j=0;j<G.numVertexes;j++)
				{
					if(G.arc[i][j]==1 &&!visited[j])
					{
						visited[j] = TRUE;
						printf("%c ",G.vexs[j]);
						EnQueue(&Q,j);
					}
				}	
			}			
		}
	}				
}

int main(void)
{    
	MGraph G;
	CreateMGraph(&G);
	printf("\n深度遍历：");
	DFSTraverse(G);
	printf("\n广度遍历：");
	BFSTraverse(G);
	return 0;
}

