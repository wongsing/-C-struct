#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 9 /* �洢�ռ��ʼ������ */
#define MAXEDGE 15
#define MAXVEX 9
#define IMAX 65535
 
//�ڽӾ����DFS��BFS���� 
//DFS
//�ڽӾ����BFS��ȱ����㷨���ö���ʵ�֣�������Ӷ������ӣ��ڽӶ������ 


//�ڽӾ���ṹ 
typedef struct 
{
	char vexs[MAXVEX];	//�����
	int	 arc[MAXVEX][MAXVEX];	//�ڽӾ���
	int numVertexes, numEdges; /* ͼ�е�ǰ�Ķ������ͱ��� */ 
}MGraph;

//ѭ�����нṹ 
typedef struct
{
	int data[MAXSIZE];
	int front;			/* ͷָ�� */
	int rear;			/* βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ�� */
}Queue;

//��ʼ������ 
int InitQueue(Queue *Q)
{
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//�����Ƿ�Ϊ�� 
int QueueEmpty(Queue Q)
{
	if(Q.rear == Q.front)
		return TRUE;
	else
		return FALSE;
}

//������в����������Ԫ�� 
int EnQueue(Queue *Q,int e)
{
	if((Q->rear+1)%MAXSIZE == Q->front)
		return ERROR;
	Q->data[Q->rear]= e;
	Q->rear = (Q->rear+1)%MAXSIZE;
	
	return OK;
}

//������в�Ϊ�գ�ɾ����ͷԪ�� 
int DeQueue(Queue *Q,int *e)
{
	if(Q->front == Q->rear)
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	
	return OK;
}

//�����ڽӾ��� 
void CreateMGraph(MGraph *G)
{
	int i, j;

	G->numEdges=15;
	G->numVertexes=9;

	/* ���붥����Ϣ����������� */
	G->vexs[0]='A';
	G->vexs[1]='B';
	G->vexs[2]='C';
	G->vexs[3]='D';
	G->vexs[4]='E';
	G->vexs[5]='F';
	G->vexs[6]='G';
	G->vexs[7]='H';
	G->vexs[8]='I';


	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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

int visited[MAXVEX]; /* ���ʱ�־������ */

//�ڽӾ����������ȵݹ��㷨 
void DFS(MGraph G, int i)
{
	int j;
	visited[i] = TRUE;
	printf("%c ",G.vexs[i]);		//��ӡ����
	for(j=0;j<G.numVertexes;j++)
		if(G.arc[i][j] == 1 && !visited[j])
			DFS(G,j); 		//�Է��ʽ����ڽӶ���ݹ���� 
}

/* �ڽӾ������ȱ������� */
void DFSTraverse(MGraph G)
{
	int i;
	for(i=0 ; i < G.numVertexes; i++)
		visited[i] = FALSE;		//�����ж��㶼û�б������� 
	for(i=0 ; i < G.numVertexes; i++)
		if(!visited[i])		//��δ�������Ķ������DFS��������ͨͼ����ֻ����һ�� 
			DFS(G,i);
}

// �ڽӾ���Ĺ�ȱ����㷨���ö���ʵ�֣�������Ӷ������ӣ��ڽӶ������ 
void BFSTraverse(MGraph G)
{
	int i , j;
	Queue Q;
	for(i = 0;i<G.numVertexes;i++)
		visited[i] = FALSE;
    InitQueue(&Q);		//��ʼ������ 
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
	printf("\n��ȱ�����");
	DFSTraverse(G);
	printf("\n��ȱ�����");
	BFSTraverse(G);
	return 0;
}

