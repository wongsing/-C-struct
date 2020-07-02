#include <stdio.h>
#define MAX 10
#define ERROR 0
#define OK 1

//typedef int Elemtype
//顺序存储结构的线性表的创建初始化、查找、插入与删除
//插入与删除用的都是线性表指针，而且线性表长度不能超过数组的长度
//插入时是插入位置后面的元素都往后移一位
//删除时是删除位置后面的元素都往前移一位 

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
		printf("第%d个元素的值是:%d\n",i,e);
	else
		printf("查找失败啦！！\n");
		printf("********************\n");
		
	if(insert(&list , i , 10))
		printf("插入成功啦\n");
	else
		printf("插入失败啦！！\n");
		printf("********************\n");

	if(del(&list , i , &e))
		printf("删除元素%d成功啦\n",e);
	else
		printf("删除失败啦！！\n");
		printf("********************\n");
						
	return 0;	
}

//查找第i个位置中的元素 
int getelem(sqlist l , int i, int *e)
{
	if(l.length == 0 || i < 1 || i > l.length)
		return ERROR;
	*e = l.data[i-1];
	return OK;
}
//在第i个位置插入元素 
int insert(sqlist *l , int i, int e)
{
	int k;
	if(l->length == MAX )  //如果线性表已满 
		return ERROR;
	if(i < 1 || i > l->length+1) //如果i不在范围之内
		return ERROR;
	if(i <= l->length)	//如果插入数据位置不在表尾
	{
		for(k = l->length-1;k>=i-1;k--)	//将插入位置后的数据元素向后移一位
			l->data[k+1] = l->data[k]; 
	}
	l->data[i-1] = e;	//将新元素插入
	l->length++;
	printf("第%d个位置新插入的值是%d\n",i,l->data[i-1]);
	return OK; 
}

//删除第i个位置元素,并将元素值返回 
int del(sqlist *l , int i, int *e)
{
	int k;
	if(l->length == 0 )  //如果线性表为空
		return ERROR;
	if(i < 1 || i > l->length+1) //如果删除位置不正确 
		return ERROR;
	*e = l->data[i-1];
	if(i < l->length)	//如果插入数据位置不在表尾
	{
		for(k = i;k < l->length;k++)	//将插入位置后的数据元素向后移一位
			l->data[k-1] = l->data[k]; 
	}
	l->length--;
	return OK; 
}
