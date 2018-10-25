#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	string str;
	int sum;
	int pos;
	int val;
	while(getline(cin,str,'\n'),str!="#"){
		sum=0;
		pos=0;
	
		for(pos=0;pos<(int)str.size();pos++)
		{
			if(str[pos]==' ') 
				val=0;
			else 
				val=str[pos]-'@';
			sum=sum+(pos+1)*val;	
		}
		cout<<sum<<endl;
	}
	return 0;
}

/*
ACM
MID CENTRAL
REGIONAL PROGRAMMING CONTEST
ACN
A C M
ABC
BBC
#

46
650
4690
49
75
14
15


*/