#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	int i;
	int n;
	int pos;
	string str;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>pos>>str;
		str.erase(pos-1,1);
		cout<<i+1<<" "<<str<<endl;
	}

	return 0;
}


/*
4 
4 MISSPELL 
1 PROGRAMMING 
7 CONTEST 
3 BALLOON


1 MISPELL 
2 ROGRAMMING 
3 CONTES 
4 BALOON



*/