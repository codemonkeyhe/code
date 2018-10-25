#include<iostream>
#include<string>
#include<stdio.h>
#include<algorithm>
using namespace std;

struct data
{
	int beg;
	int end;
	double avePla;
};

bool cmp(data a,data b)
{
	if(a.avePla>b.avePla)
	{
		return true;
	}
	int lena=a.end-a.beg+1;
	int lenb=b.end-b.beg+1;
	if(a.avePla==b.avePla &&  lena>lenb)
	{
		return true;
	}
	if(a.avePla==b.avePla &&  lena==lenb && a.end<b.end)
	{
		return true;
	}
	return false;
}

int main(void)
{
	int n;
	int qua;
	int besP;
	int minP;
	int kind;
	int i,j,k;
	cin>>n;
	for(i=0;i<n;i++)
	{
		data period[50000];
		cin>>qua>>besP>>minP;
		int *plaQ=new int[qua+1]; 
		for(j=1;j<=qua;j++)
		{
			cin>>plaQ[j];
		}
		int be;
		double sum;
		int c=0;
		for(j=minP;j<=qua;j++)
		{
			for(be=1;be<=qua-j+1;be++){
				sum=0;
				for(k=be;k<be+j;k++){
					sum=sum+plaQ[k];
				}
				sum=sum/(double)j;
				period[c].avePla=sum;
				period[c].beg=be;
				period[c].end=k-1;
				c++;
			}
		}
		sort(period,period+c,cmp);
		printf("Result for run %d:\n",i+1);
		for(j=0;j<besP && j<c;j++)
		{
			printf("%d-%d\n",period[j].beg,period[j].end);
		}
	}
	return 0;
}




/*
一次AC
这道题好在数据的规模很小，所以直接算出所有的可能的结果，加上快速排序，很容易就ac！
主要的快排上如何调用stl的快排上。自己设计cmp！

3
10 5 5
1 5 0 2 1 4 2 5 0 2 
10 3 5
10 3 1 4 2 6 3 0 8 0 
5 5 5
1 2 3 4 5


Result for run 1:
4-8
2-8
6-10
1-8
2-6
Result for run 2:
1-6
1-7
1-9
Result for run 3:
1-5



*/