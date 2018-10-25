#include<iostream>
#include<algorithm>
using namespace std;

struct data
{
	int id;
	int score;
	int penal;
};

bool cmp(data a,data b)
{
	return (a.score>b.score);
}


int main(void)
{
	int c;
	int j,i,k;
	int n;
	cin>>c;
	for(i=0;i<c;i++)
	{
		cin>>n;
		data *team=new data[n];
		for(j=0;j<n;j++)
		{
			cin>>team[j].id>>team[j].score>>team[j].penal;
		}
		sort(team,team+n,cmp);
		for(j=0;j<n-1;j++)
		{
			cout<<team[j].id<<" ";
		}
		cout<<team[j].id<<endl;
		delete []team;
	}
	return 0;
}

/*
一次AC，水题
C (<=100) 
And then follow N lines.
Each line has three numbers
Ti, Si and Pi (1<=Ti<=N, 0<=Si<=20, 0<=Pi<=10000), 
which stand for the ID, Score and Penalty of the ith team of the contest respectively. 
Specially, all teams’ scores are distinct.


2
3
3 2 200
2 1 100
1 3 300
2
1 2 222
2 1 222



1 3 2
1 2

*/