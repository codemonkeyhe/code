#include<iostream>
using namespace std;
int main(void)
{
	int i,j,k;
	int n;
	int e;
	int tol;
	int lay;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>e;
		tol=0;
		lay=0;
		k=1;
		for(j=1;j<=e;j++)
		{
			lay=lay+k;
			tol=tol+lay;
			k++;
		}
		cout<<i<<": "<<e<<" "<<tol<<endl;
	}
	return 0;
}


/*
 for a maximum of 100 cases
 a number less than 1000
5
3
5
27
999
1


1: 3 10
2: 5 35
3: 27 3654
4: 999 166666500
5: 1 1

*/