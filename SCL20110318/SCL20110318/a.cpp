#include<iostream>
#include<stdio.h>
#include<string>
#include<memory.h>
#include<algorithm>
using namespace std;
int main(void)
{
	int i,j,k;
	int T;
	int n;
	int dis;
	cin>>T;
	for(i=0;i<T;i++)
	{
		cin>>n;
		int *city=new int[n];
		for(j=0;j<n;j++)
		{
			cin>>city[j];
		}
		sort(city,city+n);
		dis=city[n-1]-city[0];
		cout<<dis<<endl;
		delete []city;
	}
	return 0;
}

/*

2
4
2006 2007 2008 2009
3
2010 2011 2012


4
3



#include<iostream>
#include<stdio.h>
#include<string>
#include<memory.h>
#include<algorithm>
using namespace std;
int main(void)
{
	int i,j,k;
	



	return 0;
}







*/