#include<iostream>
using namespace std;

int main(void)
{
	int t;
	int n;
	int num[100];
	int min=0;
	int minI=0;
	int count=0;
	cin>>t;
	while(t>0)
	{
		--t;
		cin>>n;
		for(int i=0;i<n;i++)
			cin>>num[i];
		count=0;
		for(int i=0;i<n-1;i++)
		{
			min=num[i];
			minI=i;
			for(int j=i+1;j<n;j++)
				if(num[j]<min){
					++count;
					min=num[j];
					minI=j;
				}
			swap(num[i],num[minI]);
		}
		cout<<count<<endl;
	}
	return 0;
}