#include<iostream>
#include<string>
#include<set>
using namespace std;
int main(void)
{
	int i,j,k;
	int n,l;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>l;
		set<string> st;
		string str;
		for(j=0;j<l;j++)
		{
			cin>>str;
			st.insert(str);
		}
		set<string>::iterator p1,p2;
		int count=0;
		p1=st.begin();
		while(p1!=st.end())
		{
			str=*p1;
			for(j=0;j<(int)str.length();j++)
			{
				if(str[j]=='A') str[j]='T';
				else if(str[j]=='T') str[j]='A';
				else if(str[j]=='C') str[j]='G';
				else if(str[j]=='G') str[j]='C';
			}
			p2=st.find(str);
			if(p2!=st.end())
			{
				count++;
				st.erase(p2);
				st.erase(p1);
				p1=st.begin();
			}
			else
			{
				p1++;
			}		
		}
		cout<<count<<endl;
	}
	return 0;
}





/*
一次AC，意外
2
3
ATCG
TAGC
TAGG
2
AATT
ATTA




1
0




*/