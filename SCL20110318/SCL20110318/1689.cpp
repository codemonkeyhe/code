#include<iostream>
#include<string>
#include<map>
using namespace std;

struct data
{
	int time;
	char id;
	string sta;
};

int main(void)
{
	int i,j;
	int t;
	int n;
	map<char,data> ma;
	map<char,data> ::iterator it;
	data pro;
	char ch;
	cin>>t;
	for(i=0;i<t;i++)
	{
		ma.clear();//注意不要漏了清空，否则会失败
		cin>>n;
		for(j=0;j<n;j++)
		{
			cin>>pro.time>>pro.id>>pro.sta;
			ch=pro.id;
			if(!ma.empty())
			{
				it=ma.find(ch);
				if(it==ma.end())//没找到
				{
						ma.insert(map<int,data>::value_type(ch,pro));
						
				}
				else
				{
					if(it->second.sta=="Wrong" ) {
						it->second.sta=pro.sta; 
						it->second.time=pro.time;
					}
				}
				continue;
			}
			ma.insert(map<int,data>::value_type(ch,pro));
		}

		cout<<"Accept: ";
		for(it=ma.begin();it!=ma.end();it++)
		{
			if(it->second.sta=="Accept") cout<<it->second.id;
		}
		cout<<endl;
		cout<<"Wrong: ";
		for(it=ma.begin();it!=ma.end();it++)
		{
			if(it->second.sta=="Wrong") cout<<it->second.id;
		}
		cout<<endl;
		cout<<endl;
	}
	return 0;
}

/*

integer T (T<=100
a positive integer N (N<=100), 
an integer t(0<=t<=300), the submission time. 
Then a character (from ‘A’ to ‘J’), the ID of submission problem follows. 
At last is a string (“Accept” or “Wrong”), the states of this submission. 



1
10
29 B Accept
85 A Accept
94 G Wrong
98 G Accept
120 D Wrong
170 C Wrong
183 C Accept
190 D Wrong
300 A Accept
300 B Wrong


Accept: ABCG
Wrong: D

*/