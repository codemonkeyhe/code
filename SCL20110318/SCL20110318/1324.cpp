#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	int T;
	int i,j,k;
	string str;
	cin>>T;
	for(i=0;i<T;i++)
	{
		cin>>str;
		int len=str.size();
		int scores=0;
		int p=1;
		for(j=0;j<len;j++)
		{
			if(str[j]=='X'){
				p=1;			
				continue;
			}
			else {
				scores=scores+p;
				p++;
			}
		}
		cout<<scores<<endl;
	
	
	}
	return 0;
}


/*
水题，一次AC
the length of the string is more than 0 and less than 80. 
There is no spaces between `O' and `X'.
5 
OOXXOXXOOO
OOXXOOXXOO 
OXOXOXOXOXOXOX 
OOOOOOOOOO 
OOOOXOOOOXOOOOX

10 
9 
7 
55 
30


*/