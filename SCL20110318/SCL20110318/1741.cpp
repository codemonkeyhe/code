#include<iostream>
#include<stdio.h>
using namespace std;
int cor[1010][2];
int main(void)
{
	int n,t;
	int i,j;
	cin>>t;
	double area;
	for(i=0;i<t;i++)
	{
		area=0;
		cin>>n;
		for(j=0;j<n;j++)
		{
			cin>>cor[j][0]>>cor[j][1];
		}
		for(j=0;j<n-1;j++)
		{
			area=area+(double)(cor[j+1][0]-cor[j][0])*(cor[j+1][1]+cor[j][1])/(double)2;  //注意类型强制转换，否则会出错
		}
		printf("%.1f\n",area);
	}
	return 0;
}

/*
The real numbers are rounded to one decimal digit.
No redundant spaces are needed. 

N(1<N<=1000) 
two nonnegative integers Xi(0<=Xi<=10000),Yi(0<=Yi<=10000) 

2
2
1 4
3 4
2
2 7
3 9



8.0
8.0

*/