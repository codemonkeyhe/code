#include<iostream>
#include<string>
#include<memory.h>
#include<stdio.h>
#include<algorithm>
using namespace std;

struct node
{
	int have;
	int lack;
};

bool cmp(node a ,node b)
{
	if(a.lack < b.lack) 
		return true;
	else 
		return false;
}

int main(void)
{
	int i;
	int n,s;
	while(cin>>n>>s,n!=0 || s!=0)
	{
		if(n==0) {cout<<"YES"<<endl;continue;}
		node* child=new node[n];
		for(i=0;i<n;i++)
		{
			cin>>child[i].have>>child[i].lack;
		}
		sort(child,child+n,cmp);
		for(i=0;i<n-1;i++)
		{
			if(s<child[i].lack) {
				cout<<"NO"<<endl;
				break;
			} 
			if(s+child[i].have>=child[i+1].lack)
			{
				s=s+child[i].have;
			}
			else {
				cout<<"NO"<<endl;
				break;
			}
		}
		if(i==n-1) cout<<"YES"<<endl;
		delete []child;
	}
	return 0;
}


/*


注意n=0.s!=0和n!=0,s=0的情况
2 2
1 4
2 1
2 2
1 4
1 1
0 0


YES
NO



*/