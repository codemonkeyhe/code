#include<iostream>
#include<string>
using namespace std;

int main(void)
{
	int i;
	int app[10];
	int heigh;
	int count=0;
	for(i=0;i<10;i++)
	{
		cin>>app[i];
	}
	cin>>heigh;
	for(i=0;i<10;i++)
	{

		if(heigh+30>=app[i]) count++;
	}
	cout<<count<<endl;
	return 0;
}




/*
100 200 150 140 129 134 167 198 200 111
110


5

*/