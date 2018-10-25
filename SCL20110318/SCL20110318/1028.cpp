#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

int DecStrDiv2(const string& DecStr,string& ResStr)
{
	bool ZeroBegin=true;
	string::const_iterator it=DecStr.begin();
	int rem=0;
	while(it!=DecStr.end())
	{
		int dec=*it-'0';
		rem=rem*10+dec;
		//int c=rem/2;
		int c=rem>>1;
		if(c!=0)
				ZeroBegin=false;
		if(c!=0 || ZeroBegin==false)
			ResStr+=(c+'0');
		rem=rem%2;
		it++;
	}
	return rem;
}

int GetBin1StrFromDecStr(string& DecStr)
{
	string ResStr="";
	int num=1;
	while( DecStrDiv2(DecStr,ResStr) ==0)
	{
		num++;
		DecStr=ResStr;
		ResStr.clear();
	}
	return num;
}

int main(void)
{
	int T;
	cin>>T;
	for(int i=1;i<T;i++)
	{
		string P;
		cin>>P;
		int BP=GetBin1StrFromDecStr(P);
		cout<<"Case "<<i<<": "<<BP<<endl<<endl;
	}
	string P;
	cin>>P;
	int BP=GetBin1StrFromDecStr(P);
	cout<<"Case "<<T<<": "<<BP<<endl;
	return 0;
}



/*
4
1
4
100
100000000000000

Case 1: 1
 
Case 2: 3
 
Case 3: 3
 
Case 4: 15


*/