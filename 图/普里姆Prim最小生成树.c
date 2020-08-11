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

//Prim��С���������Ǹ��ݶ��㿪ʼ����Ѱ�����ߵ�Ȩֵ��С
//�����������飬adjvex�涥���±꣬postcost�����СȨֵ,ȨֵҲ�ó�ʼ��Ϊ���� 
//������������㣬ȨֵΪ0��ʼ�����ҲΪ0
//��ʼ���������飬������Ȩֵȫ����ʼ����0��ʼ 
//֮���һ����ѭ��������Сѭ������һ����ѭ��ȫ�����㣬�ҳ�Ȩֵ��С�ı�min�����±����k
//���˾ʹ�ӡ������Ȩֵ��С��
//�ڶ���ѭ����ѭ��ȫ�����㣬�ҳ��±�Ϊk����ĸ���ȨֵС��δ����������Ȩֵ�ģ�����lowcost��kҲ����adjvex 


typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* ����ͼ */
{
	int i, j;

	/* printf("����������Ͷ�����:"); */
	G->numEdges=15;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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

/* Prim�㷨������С������  */
void MiniSpanTree_Prim(MGraph G)
{
	int min , i , j,k;
	int adjvex[MAXVEX];			//��ض����±� 
	int lowcost[MAXVEX];		//�����ߵ���СȨֵ 
	lowcost[0] = 0;				//��ʾ��V0��ʼ��ȨֵΪ0 
	adjvex[0] = 0;				//��ʼ����һ�������±�Ϊ0 	
	for(i = 1;i<G.numVertexes;i++)		//ѭ���±�Ϊ0���ȫ������ 
	{
		lowcost[i] = G.arc[0][i];		//��V0������֮�бߵ�Ȩֵ���� 
		adjvex[i] = 0;					//��ʼ����ΪV0���±� 
	}
	for( i = 1;i<G.numVertexes;i++)
	{
		min = MAX;			//��ʼ����СȨֵΪ���� 
		j=1;
		k=0;
		
		while(j<G.numVertexes)		//ѭ��ȫ������ 
		{	//�ҳ�Ȩֵ��С�ı� 
			if(lowcost[j]!=0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		
		printf("(%d,%d)\n",adjvex[k],k);	//��ӡ�������Ȩֵ��С�ı� 
		lowcost[k] = 0;			//����������Ϊ0����Ϊ������������� 
	
		for(j=1;j<G.numVertexes;j++)		//ѭ��ȫ������ 
		{	//���±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ 
			if(lowcost[j] != 0 &&G.arc[k][j] < lowcost[j])	
			{
				lowcost[j] = G.arc[k][j];	//����СȨֵ����lowcost 
				adjvex[j] = k;			//���±�Ϊk�Ķ������adjvex 
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
