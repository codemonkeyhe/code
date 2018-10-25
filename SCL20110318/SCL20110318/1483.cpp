#include<iostream>
#include<algorithm>
using namespace std;
int main(void)
{
	int w;
	int n;
	int g;
	int i,j,k;
	bool op=false;
	while(cin>>w)
	{
		cin>>n;
		if(op==true)
			cout<<endl;
		op=true;
		int* pri=new int[n];
		for(i=0;i<n;i++)
		{
			cin>>pri[i];
		}
		sort(pri,pri+n);
		i=0;
		j=n-1;
		g=0;
		while(i<=j){
			if(pri[i]+pri[j]>w) {
				j--;
				g++;
			}else{
				i++;
				j--;
				g++;
			}
			if(i==j){
				g++;
				break;
			}
		}
		cout<<g<<endl;
		delete []pri;
	}
	return 0;
}


/*
注意输出格式
相邻两个测试数据间用一个空行隔开。
 1 <= n <= 30000, 80 <= w <= 200 
 pi (5 <= pi <= w)，

100
9
90
20
20
30
50
60
70
80
90

6

*/