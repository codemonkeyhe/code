#include<iostream>
using namespace std;
int main(void)
{
	int n;
	while(cin>>n,n!=0)
	{
		if(n>2)
			cout<<"Bob"<<endl;
		else
			cout<<"Alice"<<endl;
	}
	return 0;
}