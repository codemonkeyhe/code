#include<iostream>
#include<memory.h>
using namespace std;
int main(void)
{
	int i,j;
	int tree,area;
	int beg,end;
	int count=0;
	cin>>tree>>area;
	bool *num=new bool[tree+1];
	memset(num,false,sizeof(bool)*(tree+1));
	for(i=0;i<area;i++)
	{
		cin>>beg>>end;
		for(j=beg;j<=end;j++)
		{
			num[j]=true;
		}
	}
	for(i=0;i<=tree;i++)
	{
		if(num[i]==false)
			count++;
	}
	cout<<count<<endl;
	delete []num;
	return 0;
}





/*
¼òµ¥£¬Ò»´ÎAC
500 3
150 300
100 200
470 471


298
*/