#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 100

//朴素、kmp两种模式匹配法
//kmp关键是要明白next数组推导
 
typedef char string[MAXSIZE+1];

int strassign(string T , char *chars);
int clearstring(string s);
void strprint(string T);
void nextprint(int next[] ,int length);
int length(string s);
int Index(string s,string t, int pos);
void get_next(string t,int *next);
int index_kmp1(string s,string t,int pos);
void get_nextval(string t , int *nextval);
int index_kmp2(string s,string t,int pos);

int main()
{
	int i,*p;
	string s1,s2;
	
	strassign(s1,"abcdex");
	printf("子串为: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("Next为: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"abcabx");
	printf("子串为: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("Next为: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"ababaaaba");
	printf("子串为: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("Next为: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"aaaaaaaab");
	printf("子串为: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("Next为: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"ababaaaba");
	printf("   子串为: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("   Next为: ");
	nextprint(p,length(s1));
	get_nextval(s1,p); 
	printf("NextVal为: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"aaaaaaaab");
	printf("   子串为: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("   Next为: ");
	nextprint(p,length(s1));
	get_nextval(s1,p); 
	printf("NextVal为: ");
	nextprint(p,length(s1));

	printf("\n");

	strassign(s1,"00000000000000000000000000000000000000000000000001");
	printf("主串为: ");
	strprint(s1);
	strassign(s2,"0000000001");
	printf("子串为: ");
	strprint(s2);
	printf("\n");
	printf("主串和子串在第%d个字符处首次匹配（朴素模式匹配算法）\n",Index(s1,s2,1));
	printf("主串和子串在第%d个字符处首次匹配（KMP算法） \n",index_kmp1(s1,s2,1));
	printf("主串和子串在第%d个字符处首次匹配（KMP改良算法） \n",index_kmp2(s1,s2,1));

	return 0;
}

//生成一个等于chars的T，可以用strcpy函数 
int strassign(string T , char *chars)
{
	int i ;
	if(strlen(chars) > MAXSIZE)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for(i=1;i<=T[0];i++)
			T[i] = *(chars+i-1);
		return OK;
	} 
}
//清空串长度 
int clearstring(string s)
{
	s[0] = 0;
	return OK;
}
//输出字符串T
void strprint(string T)
{
	int i ;
	for(i=1;i<=T[0];i++)
		printf("%c",T[i]);
	printf("\n");
}
//输出next数组值
void nextprint(int next[] ,int length)
{
	int i;
	for(i=1;i<=length;i++)
		printf("%d",next[i]);
	printf("\n");
} 
//返回串的元素个数 
int length(string s)
{
	return s[0];
}
//朴素的模式匹配法
int Index(string s,string t, int pos)
{
	int i = pos ;	//i用于主串s的当前位置的下标，若pos不为1，则从pos位置开始匹配 
	int j = 1;		//j用于子串t中当前位置 
	while(i <= s[0] && j <= t[0]) 
	{
		if(s[i] == t[j])	//两字母相等则继续 
		{
			++i;
			++j;
		}
		else
		{
			i = i -j + 2;
			j = 1;
		}
	}
	if(j > t[0])
		return i - t[0];
	else
		return 0;
} 
//通过计算返回子串t的next数组
void get_next(string t,int *next)
{
	int i = 1 , j = 0 ;
	next[1] = 0;
	while(i < t[0])		//t[0] 表示子串长度 
	{
		if( j== 0 || t[i] == t[j])	//t[i]表示前缀字符，t[j]表示后缀字符 
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];	//若字符不相等，则j回溯 
	}	
} 
//返回子串t在主串s中第pos个字符之后的位置。若不存在，则返回0
//t非空，1<=pos<=strlen(s)
int index_kmp1(string s,string t,int pos)
{
	int i = pos;		//i用于主串s当前位置下标值 
	int j = 1;			//j用于子串t当前位置下标值 
	int next[255];
	get_next(t,next);
	while( i <= s[0] && j <= t[0])
	{
		if(j==0 || s[i] == t[j])	//	两字母相等继续，相比朴素匹配多了j==0 
		{
			++i;
			++j;
		}
		else					//否则j回溯，i不变，重新开始匹配 
			j = next[j];
	}
	if(j > t[0])
		return i-t[0];
	else
		return 0;
} 

void get_nextval(string t , int *nextval)
{
	int i , j ;
	i = 1;
	j = 0;
	nextval[1] = 0;
	while( i < t[0] )
	{
		if(j == 0 || t[i] == t[j])
		{
			++i;
			++j;
			if( t[i] != t[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}
//返回子串t在主串s中第pos个字符之后的位置。若不存在，则返回0
//t非空，1<=pos<=strlen(s)
int index_kmp2(string s,string t,int pos)
{
	int i = pos;		//i用于主串s当前位置下标值 
	int j = 1;			//j用于子串t当前位置下标值 
	int next[255];
	get_nextval(t,next);
	while( i <= s[0] && j <= t[0])
	{
		if(j==0 || s[i] == t[j])	//	两字母相等继续，相比朴素匹配多了j==0 
		{
			++i;
			++j;
		}
		else					//否则j回溯，i不变，重新开始匹配 
			j = next[j];
	}
	if(j > t[0])
		return i-t[0];
	else
		return 0;
} 

