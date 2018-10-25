//感觉这道题目有些可恶。。。
//设起点为S，终点为T，当S和T不在列表，且S！=T时，则输出-1；而当S==T时，则输出0
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<string>
using namespace std;

int findstr(string str,string *p,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		if(str==p[i])
			return i;
	}
	return -1;
}


int findpla(string str,string *p)
{
	int i=0;
	while(!p[i].empty())
	{
		if(str==p[i])
			return i;
		else
			i++;
	}
	p[i]=str;
	return i;
}

int ShortPath(int map[220][220],int x,int y,int nodenum,int *dist,bool *Ins)
{
	int i,j;
	int min;
	int mink;
	memset(Ins,false,nodenum*sizeof(bool));
	Ins[x]=true;
	for(i=0;i<nodenum;i++)
	{
		dist[i]=map[x][i];
	}
	for(i=0;i<nodenum-2;i++){
		min=100000;
		for(j=0;j<nodenum;j++)
		{
			if(Ins[j]==false && min>dist[j])
			{
				min=dist[j];
				mink=j;
			}
		}
		if(mink!=x)
			Ins[mink]=true;
		else 
			break;
		for(j=0;j<nodenum;j++)
		{
			if(Ins[j]==false && min+map[mink][j]<dist[j])
			{
				dist[j]=min+map[mink][j];
			}
		}
	}
	return dist[y];
}

int main(void)
{
	int n;
	int m;
	int i,j,k;
 	string place[220];
	string s;
	string t;
	int tmp;
	int dist[220];
	bool Ins[220];   //标记是否在集合S中
	int map[220][220];
	int nodenum;
	int x,y;
	cin>>n;
	for(i=0;i<n;i++)
	{
		for(j=0;j<220;j++)
		{
			place[j].clear();
		}
		cin>>m;
		for(j=0;j<2*m;j++)
		{
			for(k=0;k<2*m;k++)
			{
				map[j][k]=1000000;
			}
			map[j][j]=-1;
		}
		for(j=0;j<m;j++)
		{
			cin>>s>>t>>tmp;
			x=findpla(s,place);
			y=findpla(t,place);
			map[x][y]=tmp;
			map[y][x]=tmp;
		}
		nodenum=0;
		while(!place[nodenum].empty())
		{
			nodenum++;
		}
		cin>>s>>t;
		x=findstr(s,place,nodenum);
		y=findstr(t,place,nodenum);
		if(x==-1 || y==-1)
		{
			if(s==t)
					cout<<0<<endl;
			else
					cout<<-1<<endl;
			continue;
		} 		
		tmp=ShortPath(map,x,y,nodenum,dist,Ins);
		if(tmp == 1000000  )
			printf("-1\n");
		else if(tmp==-1)
			printf("0\n");
		else
			printf("%d\n",tmp);
	}
	return 0;
}


/*
8
2
South.xiaolitang South.xiongdelong 2
South.xiongdelong Zhuhai.liyuan 100
South.xiongdelong South.xiaolitang
2
South.xiaolitang South.xiongdelong 2
South.xiongdelong Zhuhai.liyuan 100
South.xiongdelong Zhuhai.liyuan

1
a b 2
a c

1 
a b 2
c d 

1 
a b 2
f f


12
0 1 100
0 2 1000
1 2 1000
1 3 2000
2 3 1200
2 4 2500
3 4 1250
3 5 1800
4 5 250
5 6 900
6 7 1000
5 7 1400
4 1

2
a b 2
c d 4
a c

1
a b 2
a a




*/