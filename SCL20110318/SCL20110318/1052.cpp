#include<iostream>
using namespace std;

int main(void)
{
	int i,j,k;
	int n;
	int round;
	while(cin>>n,n!=0)
	{
		round=0;
		int *child=new int [n];
		for(i=0;i<n;i++)
		{
			cin>>child[i];
		}
		bool end;
		while(1)
		{
			end=true;
			round++;		
			for(i=0;i<n;i++)
			{
				child[i]=child[i]/2;
			}
			int tmp=child[n-1];
			for(i=n-1;i>=1;i--)
			{
				child[i]=child[i]+child[i-1];
			}
			child[0]=child[0]+tmp;
			for(i=0;i<n;i++)
			{
				if(child[i]%2==1) child[i]++;
			}
			for(i=0;i<n-1;i++){
				if(child[i]!=child[i+1]){ 
					end=false;
					break;
				} 
			}
			if(end==true) break;
		}
		cout<<round<<" "<<child[0]<<endl;
		delete []child;
	}
	return 0;
}


/*
Ò»´ÎAC
6
36
2
2
2
2
2

11
22
20
18
16
14
12
10
8
6
4
2

4
2
4
6
8
0


15 14
17 22
4 8



*/