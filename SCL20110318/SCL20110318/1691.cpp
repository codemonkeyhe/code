#include<iostream>
#include<set>
#include<cmath>
using namespace std;

int sigma(int x)
{
	int i;
	int sum=0;
	for(i=1;i<=sqrt((float)x);i++)
	{
		if(x%i==0){ 
			if(x/i!=i){		
				sum=sum+i+x/i;
			}
			else
				sum=sum+i;
		}
	}
	sum=sum-2*x;
	return sum;
}


int main(void)
{
	int i,j,k;
	int t;
	int x,y;
	set<int> se;
	set<int> ::iterator it;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>x>>y;
		k=0;
		se.clear();
		for(j=x;j<=y;j++){
			k=sigma(j);
			if(k>0) se.insert(k);  //注意题意，必须是大于0才能插入
		}
		if(se.empty()){
			cout<<"-1"<<endl;
		}
		else{
			it=se.end();
			it--;
			cout<<*it<<endl;
		}
	}
	return 0;
}

/*
T (T<=20), 
 two positive integers x, y, (1<= x <= y <= 1024), indicating the range of n

3
1 1
10 12
1 1024


-1
4
1208



*/