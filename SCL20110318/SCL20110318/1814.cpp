#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

int month[13]={-10000,31,28,31,30,31,30,31,31,30,31,30,31};

struct date{
	int y;
	int m;
	int d;
	int days;
	bool leap;
};


bool leapyear(int year)
{
	if(((year%4==0) && (year%100!=0))||(year%400==0))
		return true;
	else
		return false;
}

void passday(date &da)
{
	int i=1;
	da.days=0;
	for(i=1;i<da.m;i++)
		da.days=da.days+month[i];
	if(da.leap==true && (da.m>=3 || (da.m==2 && da.d==29)) ) da.days++;
	da.days=da.days+da.d;
}

int main()
{
	int t;
	int i,j;
	int days;
	int miny;int maxy;
	cin>>t;
	for(i=0;i<t;i++)
	{
		date d1,d2;
		scanf("%d.%d.%d",&d1.y,&d1.m,&d1.d);
		scanf("%d.%d.%d",&d2.y,&d2.m,&d2.d);
		if(leapyear(d1.y))
			d1.leap=true;
		else
			d1.leap=false;
		if(leapyear(d2.y))
			d2.leap=true;
		else
			d2.leap=false;
		passday(d1);
		passday(d2);
		days=0;
		if(d1.y<d2.y){
			maxy=d2.y;
			miny=d1.y;
			days=days+d2.days+365-d1.days;
			if(d1.leap==true) days++;
		}
		else if(d1.y>d2.y){
			maxy=d1.y;
			miny=d2.y;
			days=days+d1.days+365-d2.days;
			if(d2.leap==true) days++;
		}
		else{
			days=abs((double)(d1.days-d2.days));
			cout<<days<<endl;
			continue;
		}
		for(j=miny+1;j<maxy;j++)
		{
			days=days+365;
			if(leapyear(j)) days++;
		}
		cout<<days<<endl;
	}
	return 0;
}

/*
基本一次AC
2
2000.02.28
2000.03.01
6297.01.21
2351.11.27


2
2
1440938

*/