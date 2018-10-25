#include<iostream>
#include<stdio.h>
#include<string>
#include<memory.h>
#include<algorithm>
using namespace std;
int main(void)
{
	long i,j,k;
	long N,T;
	while(!cin.eof()){
		cin>>N>>T;
		if(N==0) {cout<<"-1"<<endl;continue;}
		long r[100020];
		//long len[100000];
		for(i=0;i<N;i++)
		{
			cin>>r[i];
		}
		i=0;
		j=0;
		k=0;
		long l=0;
		long sum=0;
		bool s=false;
		bool find=true;
		int min=9999;
		while(1){
			if(s==false){
				sum=sum+r[j];
				l++;
			}
			if(sum>T) {
				find=false;
				//len[k]=l;
				if(min>l) min=l;
				k++;
				sum=sum-r[i];
				i++;
				l--;
				s=true;
			}
			else {
				j++;
				if(j>N-1) break; 
				s=false;
			}
		
		}
		//sort(len,len+k);
		if(find==false)
			cout<<min<<endl;
		else 
			cout<<"-1"<<endl;

	}


return 0;
}


/*
 
7 18
5 8 4 9 10 5 2
经验不足，T没有给出下界，说明T可以为负值，所以算法存在缺陷
two integer N(N <= 100000) and T(T <= 2 * 10^9). 
If there’s no solution, print out -1 in one line.

2

*/