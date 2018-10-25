#include<iostream>
#include<algorithm>
using namespace std;

bool cmp(int a,int b)
{
	return (a>b);
}

int main(void)
{
	int i,j;
	int t;
	int n;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n;
		int*price =new int[n];
		for(j=0;j<n;j++)
		{
			cin>>price[j];
		}
		sort(price,price+n,cmp);
		int sum=0;
		for(j=2;j<n;j=j+3)
		{
			sum=sum+price[j];
		}
		cout<<sum<<endl;
		delete []price;
	}
	return 0;
}

/*

1
6
400 100 200 350 300 250

400
*/