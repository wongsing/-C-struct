#include <stdio.h>    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* ��󶥵�����Ӧ���û����� */
#define MAX 65535

//�ڽӾ������������
//������ȷ������ͱ߻��ߺ�������Ȼ��������붥�㣬���ö����
//֮��ͳ�ʼ���߱�����ͼ��ȫΪ0������ͼ���Խ���Ϊ0������Ϊ����
//Ȼ��Ϳ�ʼ���������Ԫ�� v,j,k(Ȩֵ)!ע�������Ǿ���Գƣ�������ֻ������Ӧ�ľͿ� 
//����Ļ� ���������� Ȼ���ٱ�������߱� 


//����ṹ 
typedef struct
{
	char vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes , numEdges;
}MGraph;
//����ͼ 
void CreateMGraph1(MGraph *G)
{
	int i , j , k ,w;
	printf("���붥�����ͱ���:");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	printf("\n���붥��:\n");
	for(i=0;i < G->numVertexes ; i++)		//���붥����Ϣ�����������		
		{
			scanf("%c",&G->vexs[i]);	
			printf("����Ϊ��%c\n",G->vexs[i]);			
		}		

	for(i=0;i < G->numVertexes ; i++)	//��ʼ���ڽӾ��� 
		for(j=0;j < G->numVertexes ; j++)
			G->arc[i][j] = 0;	//����ͼ��0��ʼ��������ͼ��Ȩֵ�Ļ����������ʼ��
	
	for(k = 0 ; k <G->numEdges ; k++)	//��ȡ�����������ڽӾ��� 
	{
		printf("�����(Vi,Vj)�ϵ��±�i���±�j��Ȩw:");
		scanf("%d %d %d",&i,&j,&w);
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];		//����ͼ�Ǿ���Գ�		
	}		
}
//����ͼ 
void CreateMGraph2(MGraph *G)
{
	int i , j , k ,w;
	printf("���붥�����ͱ���:");
	scanf("%d %d",&G->numVertexes,&G->numEdges);
	for(i=0;i < G->numVertexes ; i++)		//���붥����Ϣ����������� 
		scanf("%c",&G->vexs[i]);
	for(i=0;i < G->numVertexes ; i++)	//��ʼ���ڽӾ��� 
		for(j=0;j < G->numVertexes ; j++)
			if(i == j)	
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = MAX;		//ij�����0��ʼ��������ͼ��Ȩֵ�Ļ����������ʼ��
	
	for(k = 0 ; k <G->numEdges ; k++)	//��ȡ�����������ڽӾ��� 
	{
		printf("�����(Vi,Vj)�ϵ��±�i���±�j��Ȩw:");
		scanf("%d %d %d",&i,&j,&w);
		G->arc[i][j] = w;
//		G->arc[j][i] = G->arc[i][j];		//����ͼ�Ǿ���Գ�		
	}		
}

void printfL(MGraph *g) {
    //���ͼ����Ϣ
    printf("��Ϊ :\n");
    int i = 0 , j ;
    //�ȴ�ӡ�б��⣻�������
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
	printf("����ͼ���ڽӾ���\n");
	printfL(&G);
	printf("*************\n");
	printf("����ͼ���ڽӾ���\n");	
	printf("*************\n");
	CreateMGraph2(&G);
	printfL(&G);
	return 0;	
}
