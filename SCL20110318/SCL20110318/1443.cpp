#include<iostream>
#include<queue>
using namespace std;

struct job
{
	int pri;
	int pos;
};

int main(void)
{
	int i,j,k;
	queue<job> que;
	int t;
	int pri;
	int n,m;
	int max;
	job tmp;
	cin>>t;
	for(i=0;i<t;i++)
	{
		while(!que.empty()) que.pop();
		cin>>n>>m;
		max=0;
		for(j=0;j<n;j++)
		{
			cin>>pri;
			tmp.pri=pri;
			tmp.pos=j;
			if(max<pri) max=pri;
			que.push(tmp);
		}
		k=0;
		while(1){
			while(que.front().pri!=max)
			{
				que.push(que.front());
				que.pop();
			}
			k++;
			if(que.front().pos!=m)
			{
				que.pop();
				max=0;
				int len=que.size();
				for(j=0;j<len;j++){
					if(max<que.front().pri) max=que.front().pri;
					que.push(que.front());
					que.pop();
				}		
			}
			else
				break;
			
		}
		cout<<k<<endl;
	}
	return 0;
}


/*
 n is the number of jobs in the queue (1 ≤ n ≤ 100) 
 and m is the position of your job (0 ≤ m ≤ n −1). 
3
1 0
5
4 2
1 2 3 4
6 0
1 1 9 1 1 1


1
2
5

*/