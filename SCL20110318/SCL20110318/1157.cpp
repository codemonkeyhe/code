#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(int a,int b)
{
	return (a>b);
}
int main(void)
{
	int n;
	int i,j;
	while(cin>>n,n!=0)
	{
		int *a=new int [n];
		for(i=0;i<n;i++)
		{
			cin>>a[i];
		}
		sort(a,a+n,cmp);
		cout<<a[0]<<endl;
	}
	return 0;
}


/*
Ò»´ÎAC
1<=n<=4
1 1
2 1 2
3 1 3 2
4 1 2 3 4
0


1
2
3
4


*/