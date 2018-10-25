#include<iostream>
using namespace std;
int main(void)
{
	int t;
	int n;
	int i,j;
	int sum;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n;
		sum=0;
		for(j=1;j<=n;j++)
		{
			sum=sum+j;
		}
		cout<<sum<<endl;
	}
	return 0;
}

/*

2
8
100

36 
5050



*/