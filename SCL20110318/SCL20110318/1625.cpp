#include<iostream>
#include<stdio.h>
using namespace std;




void change(int n,int t[])
{
	int i=5;
	int k=n;
	while(k!=0)
	{
		t[i]=k%2;
		k=k/2;
		i--;
	}
	while(i>=0)
	{
		t[i]=0;
		i--;
	}
}


int main(void)
{
	int i,j,k;
	int h,m,s;
	int ho[6];
	int mi[6];
	int se[6];
	int t;
	cin>>t;
	for(i=1;i<=t;i++)
	{
		scanf("%d:%d:%d",&h,&m,&s);
		change(h,ho);
		change(m,mi);
		change(s,se);
		cout<<i<<" ";
		for(j=0;j<6;j++)
			cout<<ho[j]<<mi[j]<<se[j];
		cout<<" ";
		for(j=0;j<6;j++)
			cout<<ho[j];
		for(j=0;j<6;j++)
			cout<<mi[j];
		for(j=0;j<6;j++)
			cout<<se[j];
		cout<<endl;
	}
	return 0;
}


/*
一次AC。水题
2 
10:37:49
00:00:01


1 011001100010100011 001010100101110001
2 000000000000000001 000000000000000001


*/