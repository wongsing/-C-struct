#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

int F[100]; /* 斐波那契数列 */

//无序查找 
//基本的顺序查找--->O(n)
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

//有哨兵顺序查找--->比上面的查找少了i与n的比较 --->O(n)
int Sequential_Search2(int *a, int n, int key)
{
	int i ;
	a[0] = key;		//关键字，也就是哨兵 
	i = n;			//循环从数组尾部开始 
	while(a[i] != key)	
		i--;	
	return i;	//返回0则说明查找失败 
}

//有序查找-->三种方法
 
//折半查找--->二分法查找 --->O(logn)
int Binary_Search(int *a , int n,int key)
{
	int low , high ,mid;
	low = 1;		//最低下标 
	high = n;		//最高下标 
	while(low <= high)
	{
		mid = (low+high)/2;
		if(key < a[mid])
			high = mid - 1;
		else if(key > a[mid])
			low = mid + 1;
		else
			return mid;			/* 若相等则说明mid即为查找到的位置 */
	}
	return 0;
}

//插值查找-->关键就是mid与二分法不同,当关键字分布比较均匀，且表较长时，用插值好些 
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
			return mid;			/* 若相等则说明mid即为查找到的位置 */
	}
	return 0;
}

//斐波那契查找--O(logn)
//首先得设置好一个全局变量，斐波那契数列数组 
int Fibonacci_Search(int *a,int n,int key)
{
	int low , high , mid ,i ,k;
	low = 1;
	high = n;
	k = 0;
	
	while( n > F[k]-1)		//计算n位于斐波那契数列的位置 
		k++;
	
	for(i = n;i < F[k]-1;i++)	//将不满的数值补全 
		a[i] = a[n];
		
	while(low <= high)
	{
		mid = low + F[k-1] - 1;		//计算当前分隔的下标 
		if(key <a[mid])
		{
			high = mid - 1;	
			k = k - 1;			//斐波那契数列下标减一位 
		}
		else if(key > a[mid])
		{
			low = mid + 1;
			k = k - 2;			//斐波那契数列下标减两位 
		}
		else
		{
			if(mid <= n)		//若相等则mid为查到的位置 
				return mid;
			else				//若mid>n，这说明是补全数值，返回n 
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
