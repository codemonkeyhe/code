#include<iostream>
#include<queue>
using namespace std;
int main(void)
{
	int t;
	int n;
	
	cin>>t;
	queue<int> que;
	while(t>0)
	{
		t--;
		cin>>n;
		if(n==1) {cout<<"1 "<<endl;continue;}
		else if(n==2) {cout<<"1 2 "<<endl;continue;}
		for(int i=1;i<=n;i++)
			que.push(i);
		while(que.size()>2){
			cout<<que.front()<<" ";
			que.pop();
			que.push(que.front());
			que.pop();
		}	
		cout<<que.front()<<" ";
		que.pop();
		cout<<que.front()<<" "<<endl;
		que.pop();
	}
	return 0;
}