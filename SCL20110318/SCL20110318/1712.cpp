#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(void)
{
	string str;
	while(cin>>str,str!="#")
	{
		int num=0;
		string::size_type i;
		for(i=0;i<str.size()-1;i++)
			if(str[i]=='1') ++num;
		if(str[i]=='e')
		{
			if(num%2)
				str[i]='1';
			else
				str[i]='0';
		}else{
			if(num%2)
				str[i]='0';
			else
				str[i]='1';
		}
		cout<<str<<endl;
	}

	return 0;
}