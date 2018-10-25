#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;
int main(void)
{
	int i;
	int n;
	cin>>n;
	double x1,y1,x2,y2;
	double dis;
	for(i=0;i<n;i++)
	{
		cin>>x1>>y1>>x2>>y2;
		dis=sqrt( pow(abs(y1-y2),2)+pow(abs(x1-x2),2) );
		printf("%.2f\n",dis);
	}
	return 0;
}


/*
每行由 4 个实数组成,分别表示 x1,y1,x2,y2
2
0 0 0 1
0 1 1 0


1.00
1.41

*/