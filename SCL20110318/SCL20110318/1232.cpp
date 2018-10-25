#include<iostream>
using namespace std;
int main(void)
{
	int n;
	int k;
	int i,j;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>k;
		int *strip=new int[k];
		int sum=0;
		for(j=0;j<k;j++)
		{
			cin>>strip[j];
			sum=sum+strip[j];
		}
		sum=sum-k+1;
		cout<<sum<<endl;
		delete []strip;
	}
	return 0;
}


/*
1 <= N <= 20
1 <= K <= 10
O1 O2 . . . OK, where 2 <= Oi <= 10

3
3 2 3 4
10 4 4 4 4 4 4 4 4 4 4
4 10 10 10 10

7
31
37

*/