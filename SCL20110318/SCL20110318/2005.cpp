#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> s;
vector<int> ::iterator it;
int main(void)
{
	int i,j;
	int n;
	while(cin>>n){
		s.clear();
		for(i=0;i<n;i++){
			cin>>j;
			it=find(s.begin(),s.end(),j);
			if(it==s.end())
			{
				s.push_back(j);
			}
			else{
				s.erase(it);
			}
		}
		cout<<s[0]<<endl;
	
	}
	return 0;
}

/*
1 <= N <= 10001, and N % 2 = 1
3
1 2 1
5
7 7 7 7 3
7
2 2 4 4 4 2 2


2
3
4

*/