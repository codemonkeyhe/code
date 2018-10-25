#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
int si[305];
int main(void)
{
	int i,j,k;
	int n;

	int t;
	cin>>t;
	while(t>0){
		cin>>n;
		for(i=0;i<n;i++)
			cin>>si[i];
		k=n;
		vector<int> v;
		//set<int> v;
		for(i=0;i<n;i++){	
			j=si[i]%k;
			//if(!binary_search(v.begin(),v.end(),j))
				//v.insert(j);
		if(find(v.begin(),v.end(),j)==v.end())   
			v.push_back(j);
			else{
				v.clear();
				k++;
				i=-1;
				continue;
			}
		}
		cout<<k<<endl;
		t--;
	}
	return 0;
}

/*
 //不能用SET，用Set会超时,而用vector则不会超时
N, telling the number of test cases (groups) to follow
 G (1 ≤ G ≤ 300)
4

1
124866
3
124866
111111
987651

10
999999
999998
999997
999996
999995
999994
999993
999992
999991
999990
6
9990
9980
9970
9960
9950
9940

1
8
10
7

*/

