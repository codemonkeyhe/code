#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#include<memory.h>
using namespace std;
int GetScores(int xpos,int ypos)
{
	int a;
	int b;
	a=abs(xpos-30);
	b=abs(ypos-30);
	if (a*a+b*b<400) return 1;
	a=abs(xpos-100);
	b=abs(ypos-30);
	if (a*a+b*b<100) return 2;
	a=abs(xpos-170);
	b=abs(ypos-30);
	if (a*a+b*b<25) return 3;
	return 0;
}

int main(void)
{
	int i,j;
	int tesN;
	int hitN;
	int scores;
	int xpos,ypos;
	cin>>tesN;
	for(i=0;i<tesN;i++)
	{
		cin>>hitN;
		scores=0;
		for(j=0;j<hitN;j++)
		{
			cin>>xpos>>ypos;
			scores=scores+GetScores(xpos,ypos);
		}
		cout<<scores<<endl;
	}
	return 0;
}


/*
水题，一次AC
3
2
30 31
100 32
1
30 50
3
30 30
99 30
170 30



3
0
6

*/