#include<iostream>
#include<set>
#include<string>
using namespace std;

int main(void)
{
	int t;
	int i,j;
	int n;
	string str;
	set<string> tel;
	set<string>::iterator it;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n;
		tel.clear();
		for(j=0;j<n;j++)
		{
			cin>>str;
			tel.insert(str);
		}
		it=tel.begin();
		string pre=*it;
		string now="";
		it++;
		for(;it!=tel.end();it++)
		{
			now=*it;
			if(now.find(pre)!=string::npos)
			{
				cout<<"NO"<<endl;
				break;
			}
			pre=now;
		}
		if(it==tel.end())
			cout<<"YES"<<endl;
	}
	return 0;
}


/*
2
3
911
97625999
91125426
5
113
12340
123440
12345
98346


NO
YES

4
1234
12345
456
456789

*/