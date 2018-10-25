#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<algorithm>
#include<string>
using namespace std;
int main(void)
{
	int i,j;
	int tesN;
	int n;
	cin>>tesN;
	for(i=0;i<tesN;i++)
	{
		cin>>n;
		int *arr=new int [n];
		for(j=0;j<n;j++)
		{
			cin>>arr[j];
		}
		sort(arr,arr+n);
		for(j=0;j<n;j++)
		{
			cout<<arr[j]<<endl;
		}
		delete []arr;

	}
	return 0;
}



/*
2
3
1
2
3
1
1



1
2
3
1


*/