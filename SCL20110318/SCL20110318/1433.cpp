#include<iostream>
#include<algorithm>
using namespace std;
int main(void)
{
	int t;
	int n;
	int i,j;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n;
		int *shop=new int [n];
		for(j=0;j<n;j++)
		{
			cin>>shop[j];
		}
		sort(shop,shop+n);
		cout<<(shop[n-1]-shop[0])*2<<endl;
		delete []shop;
	}
	return 0;
}

/*
2
4
24 13 89 37
6
7 30 41 14 39 42

152
70


*/