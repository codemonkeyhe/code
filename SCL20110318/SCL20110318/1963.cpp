#include<iostream>
#include<algorithm>
using namespace std;
int main(void)
{
	int n;
	cin>>n;
	int *num=new int[n];
	for(int i=0;i<n;i++)
	{
		cin>>num[i];
	}
	sort(num,num+n);
	cout<<num[n-1]<<endl;
	delete []num;
	return 0;
}
/*

5
5 0 3 -5 7

7
*/