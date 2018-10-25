#include<iostream>
#include<algorithm>
#include<memory.h>
using namespace std;

int main(void)
{
	int n;
	int i;
	while(!cin.eof())
	{
		cin>>n;
		if(n==0) break;
		int len[120];
		for(i=0;i<n;i++)
		{
			cin>>len[i];
		}
		sort(len,len+n);
		for(i=0;i<n;i++)
		{
			if(len[i]==len[i+1])
				i++;
			else{
				cout<<len[i]<<endl;
				break;
			}
		}
	}
	return 0;
}


/*
1<=n<=100, and n is odd
3
1
2
1
0


2

*/