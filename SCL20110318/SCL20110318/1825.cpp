#include<iostream>
#include<string>
#include<algorithm>
#include<cctype>
#include<map>
using namespace std;

int main(void)
{
	int T,N;
	map<string , int> ma;
	map<string , int>::iterator it;
	string name;
	cin>>T;
	while(T>0)
	{
		ma.clear();
		--T;
		cin>>N;
		for(int i=0;i<N;i++)
		{
			cin>>name;
			for(int j=0;j<name.size();j++)
				name[j]=tolower(name[j]);	
			++ma[name];
		}
		for(it=ma.begin();it!=ma.end();it++)
		{
			cout<<it->first<<" "<<it->second<<endl;
		}
		cout<<endl;
	}
	return 0;
}

/*
1
4
carp
inkfish
peipei
CArp


carp 2
inkfish 1
peipei 1

*/