#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
#define MAXSIZE 100

//���ء�kmp����ģʽƥ�䷨
//kmp�ؼ���Ҫ����next�����Ƶ�
 
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
	printf("�Ӵ�Ϊ: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("NextΪ: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"abcabx");
	printf("�Ӵ�Ϊ: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("NextΪ: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"ababaaaba");
	printf("�Ӵ�Ϊ: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("NextΪ: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"aaaaaaaab");
	printf("�Ӵ�Ϊ: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("NextΪ: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"ababaaaba");
	printf("   �Ӵ�Ϊ: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("   NextΪ: ");
	nextprint(p,length(s1));
	get_nextval(s1,p); 
	printf("NextValΪ: ");
	nextprint(p,length(s1));
	printf("\n");

	strassign(s1,"aaaaaaaab");
	printf("   �Ӵ�Ϊ: ");
	strprint(s1);
	i=length(s1);
	p=(int*)malloc((i+1)*sizeof(int));
	get_next(s1,p); 
	printf("   NextΪ: ");
	nextprint(p,length(s1));
	get_nextval(s1,p); 
	printf("NextValΪ: ");
	nextprint(p,length(s1));

	printf("\n");

	strassign(s1,"00000000000000000000000000000000000000000000000001");
	printf("����Ϊ: ");
	strprint(s1);
	strassign(s2,"0000000001");
	printf("�Ӵ�Ϊ: ");
	strprint(s2);
	printf("\n");
	printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨����ģʽƥ���㷨��\n",Index(s1,s2,1));
	printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨KMP�㷨�� \n",index_kmp1(s1,s2,1));
	printf("�������Ӵ��ڵ�%d���ַ����״�ƥ�䣨KMP�����㷨�� \n",index_kmp2(s1,s2,1));

	return 0;
}

//����һ������chars��T��������strcpy���� 
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
//��մ����� 
int clearstring(string s)
{
	s[0] = 0;
	return OK;
}
//����ַ���T
void strprint(string T)
{
	int i ;
	for(i=1;i<=T[0];i++)
		printf("%c",T[i]);
	printf("\n");
}
//���next����ֵ
void nextprint(int next[] ,int length)
{
	int i;
	for(i=1;i<=length;i++)
		printf("%d",next[i]);
	printf("\n");
} 
//���ش���Ԫ�ظ��� 
int length(string s)
{
	return s[0];
}
//���ص�ģʽƥ�䷨
int Index(string s,string t, int pos)
{
	int i = pos ;	//i��������s�ĵ�ǰλ�õ��±꣬��pos��Ϊ1�����posλ�ÿ�ʼƥ�� 
	int j = 1;		//j�����Ӵ�t�е�ǰλ�� 
	while(i <= s[0] && j <= t[0]) 
	{
		if(s[i] == t[j])	//����ĸ�������� 
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
//ͨ�����㷵���Ӵ�t��next����
void get_next(string t,int *next)
{
	int i = 1 , j = 0 ;
	next[1] = 0;
	while(i < t[0])		//t[0] ��ʾ�Ӵ����� 
	{
		if( j== 0 || t[i] == t[j])	//t[i]��ʾǰ׺�ַ���t[j]��ʾ��׺�ַ� 
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];	//���ַ�����ȣ���j���� 
	}	
} 
//�����Ӵ�t������s�е�pos���ַ�֮���λ�á��������ڣ��򷵻�0
//t�ǿգ�1<=pos<=strlen(s)
int index_kmp1(string s,string t,int pos)
{
	int i = pos;		//i��������s��ǰλ���±�ֵ 
	int j = 1;			//j�����Ӵ�t��ǰλ���±�ֵ 
	int next[255];
	get_next(t,next);
	while( i <= s[0] && j <= t[0])
	{
		if(j==0 || s[i] == t[j])	//	����ĸ��ȼ������������ƥ�����j==0 
		{
			++i;
			++j;
		}
		else					//����j���ݣ�i���䣬���¿�ʼƥ�� 
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
//�����Ӵ�t������s�е�pos���ַ�֮���λ�á��������ڣ��򷵻�0
//t�ǿգ�1<=pos<=strlen(s)
int index_kmp2(string s,string t,int pos)
{
	int i = pos;		//i��������s��ǰλ���±�ֵ 
	int j = 1;			//j�����Ӵ�t��ǰλ���±�ֵ 
	int next[255];
	get_nextval(t,next);
	while( i <= s[0] && j <= t[0])
	{
		if(j==0 || s[i] == t[j])	//	����ĸ��ȼ������������ƥ�����j==0 
		{
			++i;
			++j;
		}
		else					//����j���ݣ�i���䣬���¿�ʼƥ�� 
			j = next[j];
	}
	if(j > t[0])
		return i-t[0];
	else
		return 0;
} 

