#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

int F[100]; /* 쳲��������� */

//������� 
//������˳�����--->O(n)
int Sequential_Search(int *a, int n, int key)
{
	int i ;
	for(i = 0;i <= n; i++)
	{
		if(a[i] == key)
			return i;
	}
	return 0;
}

//���ڱ�˳�����--->������Ĳ�������i��n�ıȽ� --->O(n)
int Sequential_Search2(int *a, int n, int key)
{
	int i ;
	a[0] = key;		//�ؼ��֣�Ҳ�����ڱ� 
	i = n;			//ѭ��������β����ʼ 
	while(a[i] != key)	
		i--;	
	return i;	//����0��˵������ʧ�� 
}

//�������-->���ַ���
 
//�۰����--->���ַ����� --->O(logn)
int Binary_Search(int *a , int n,int key)
{
	int low , high ,mid;
	low = 1;		//����±� 
	high = n;		//����±� 
	while(low <= high)
	{
		mid = (low+high)/2;
		if(key < a[mid])
			high = mid - 1;
		else if(key > a[mid])
			low = mid + 1;
		else
			return mid;			/* �������˵��mid��Ϊ���ҵ���λ�� */
	}
	return 0;
}

//��ֵ����-->�ؼ�����mid����ַ���ͬ,���ؼ��ֲַ��ȽϾ��ȣ��ұ�ϳ�ʱ���ò�ֵ��Щ 
//mid=low+(high-low)*(key-a[low])/(a[high]-a[low]);
int Interpolation_Search(int *a,int n,int key)
{
	int low , high ,mid;
	low = 1;
	high = n;
	while(low <= high)
	{
		mid = low + (high-low) * (key - a[low]) / (a[high] - a[low]);
		if(key < a[mid])
			high = mid - 1;
		else if(key > a[mid])
			low = mid + 1;
		else
			return mid;			/* �������˵��mid��Ϊ���ҵ���λ�� */
	}
	return 0;
}

//쳲���������--O(logn)
//���ȵ����ú�һ��ȫ�ֱ�����쳲������������� 
int Fibonacci_Search(int *a,int n,int key)
{
	int low , high , mid ,i ,k;
	low = 1;
	high = n;
	k = 0;
	
	while( n > F[k]-1)		//����nλ��쳲��������е�λ�� 
		k++;
	
	for(i = n;i < F[k]-1;i++)	//����������ֵ��ȫ 
		a[i] = a[n];
		
	while(low <= high)
	{
		mid = low + F[k-1] - 1;		//���㵱ǰ�ָ����±� 
		if(key <a[mid])
		{
			high = mid - 1;	
			k = k - 1;			//쳲����������±��һλ 
		}
		else if(key > a[mid])
		{
			low = mid + 1;
			k = k - 2;			//쳲����������±����λ 
		}
		else
		{
			if(mid <= n)		//�������midΪ�鵽��λ�� 
				return mid;
			else				//��mid>n����˵���ǲ�ȫ��ֵ������n 
				return n;
		}
	}
	return 0;
}

int main(void)
{    

	int a[MAXSIZE+1],i,result;
	int arr[MAXSIZE]={0,1,16,24,35,47,59,62,73,88,99};
		
	for(i=0;i<=MAXSIZE;i++)
	{
		a[i]=i;
	}
	result=Sequential_Search(a,MAXSIZE,MAXSIZE);
	printf("Sequential_Search:%d \n",result);
	result=Sequential_Search2(a,MAXSIZE,1);
	printf("Sequential_Search2:%d \n",result);

	result=Binary_Search(arr,10,62);
	printf("Binary_Search:%d \n",result);

	
	result=Interpolation_Search(arr,10,62);
	printf("Interpolation_Search:%d \n",result);

	
	F[0]=0;
	F[1]=1;
	for(i = 2;i < 100;i++)  
	{ 
		F[i] = F[i-1] + F[i-2];  
	} 
	result=Fibonacci_Search(arr,10,62);
	printf("Fibonacci_Search:%d \n",result);
	
	return 0;
}
