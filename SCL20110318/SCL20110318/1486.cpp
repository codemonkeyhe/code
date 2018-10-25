#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
int main(void)
{
	int n;
	int i,k;
	int s=1;
	bool en=false;
	while(cin>>n)
	{
		if(en)  
			printf("\n");
			//cout<<endl; 
		en=true;
		int *num=new int[n];
		for(i=0;i<n;i++){
			//cin>>num[i];
			scanf("%d",&num[i]);
		}
		sort(num,num+n);
		for(i=0;i<n;i++)
		{
			k=1;	
			while(num[i]==num[i+1]) {i++;k++;}
			printf("%d %d\n",num[i],k);
			//cout<<num[i]<<" "<<k<<endl;
		}
		delete []num;
	}
	return 0;
}

/*
此题必须用scanf和printf,否则会超时
//cout<<endl; 注意输出格式，是每两个案例之间输出一个空行，最后一个案例不要输出空行
8
2
4
2
4
5
100
2
100


2 3
4 2
5 1
100 2


*/

