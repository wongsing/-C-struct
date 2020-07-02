#include <stdio.h>
#define MAX 10
#define ERROR 0
#define OK 1

//typedef int Elemtype
//˳��洢�ṹ�����Ա�Ĵ�����ʼ�������ҡ�������ɾ��
//������ɾ���õĶ������Ա�ָ�룬�������Ա��Ȳ��ܳ�������ĳ���
//����ʱ�ǲ���λ�ú����Ԫ�ض�������һλ
//ɾ��ʱ��ɾ��λ�ú����Ԫ�ض���ǰ��һλ 

typedef struct
{
	int data[MAX];
	int length;
}sqlist;

int del(sqlist *l , int i, int *e);
int insert(sqlist *l , int i, int e);
int getelem(sqlist l , int i, int *e);

int main()
{
	sqlist list = {{1,2,3,4,5,6,7,8},8};
	int i = 5, e;

	if(getelem(list , i , &e))
		printf("��%d��Ԫ�ص�ֵ��:%d\n",i,e);
	else
		printf("����ʧ��������\n");
		printf("********************\n");
		
	if(insert(&list , i , 10))
		printf("����ɹ���\n");
	else
		printf("����ʧ��������\n");
		printf("********************\n");

	if(del(&list , i , &e))
		printf("ɾ��Ԫ��%d�ɹ���\n",e);
	else
		printf("ɾ��ʧ��������\n");
		printf("********************\n");
						
	return 0;	
}

//���ҵ�i��λ���е�Ԫ�� 
int getelem(sqlist l , int i, int *e)
{
	if(l.length == 0 || i < 1 || i > l.length)
		return ERROR;
	*e = l.data[i-1];
	return OK;
}
//�ڵ�i��λ�ò���Ԫ�� 
int insert(sqlist *l , int i, int e)
{
	int k;
	if(l->length == MAX )  //������Ա����� 
		return ERROR;
	if(i < 1 || i > l->length+1) //���i���ڷ�Χ֮��
		return ERROR;
	if(i <= l->length)	//�����������λ�ò��ڱ�β
	{
		for(k = l->length-1;k>=i-1;k--)	//������λ�ú������Ԫ�������һλ
			l->data[k+1] = l->data[k]; 
	}
	l->data[i-1] = e;	//����Ԫ�ز���
	l->length++;
	printf("��%d��λ���²����ֵ��%d\n",i,l->data[i-1]);
	return OK; 
}

//ɾ����i��λ��Ԫ��,����Ԫ��ֵ���� 
int del(sqlist *l , int i, int *e)
{
	int k;
	if(l->length == 0 )  //������Ա�Ϊ��
		return ERROR;
	if(i < 1 || i > l->length+1) //���ɾ��λ�ò���ȷ 
		return ERROR;
	*e = l->data[i-1];
	if(i < l->length)	//�����������λ�ò��ڱ�β
	{
		for(k = i;k < l->length;k++)	//������λ�ú������Ԫ�������һλ
			l->data[k-1] = l->data[k]; 
	}
	l->length--;
	return OK; 
}
