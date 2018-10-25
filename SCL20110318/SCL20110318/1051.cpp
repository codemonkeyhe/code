#include<iostream>
#include<stdio.h>
using namespace std;
#define Pi 3.1415927

int main(void)
{
	double d,t;
	int r;
	double dis,mph;
	int i=1;
	while(cin>>d>>r>>t,r!=0)
	{
		dis=(double)r*d*Pi/(double)63360.00;
		mph=(double)dis*3600/t;
		printf("Trip #%d: %.2f %.2f\n",i,dis,mph);
		i++;
	}
	return 0;
}




/*
º∏∫ı√Î…±
26 1000 5
27.25 873234 3000
26 0 1000


Trip #1: 1.29 928.20
Trip #2: 1179.86 1415.84


*/