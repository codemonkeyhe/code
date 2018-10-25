#include<iostream>
#include<set>
#include<algorithm>
#include<stdio.h>
using namespace std;


int pig[1000010];
bool locked[1000010];
int main(void)
{
	int n;
	int count;
	int i,j,k;
	set<int> sa;
	set<int> ::iterator it;
	bool con;
	while(cin>>n){
		count=0;
		for(i=1;i<=n;i++){
			scanf("%d",&pig[i]);
			if(pig[i]==i){ locked[i]=false;count++;}
			else locked[i]=true;
		}
		for(i=1;i<=n;i++){
			con=false;
			if(locked[i]==true){
				j=pig[i];
				sa.insert(j);
				sa.insert(i);	
				while(locked[j]!=false){
					j=pig[j];
					if(!binary_search(sa.begin(),sa.end(),j))
						sa.insert(j);
					else{//弹出容器每个元素，并改为false;
						while(!sa.empty()){
							it=sa.begin();
							locked[*it]=false;
							sa.erase(it);
						}
						count++;
						con=true;
						break;
					}
						
				}
				if(con==true) continue;
				//弹出容器每个元素，并改为false;
				while(!sa.empty()){
							it=sa.begin();
							locked[*it]=false;
							sa.erase(it);
				}			
			}
			
		}
	cout<<count<<endl;
	}
	return 0;
}


/*
并查集
注意：输入包含多个测试数据。
N (1 <= N <= 1.000.000)
4
2
1
2
4

2

7
1
6
3
5
4
3
1




*/