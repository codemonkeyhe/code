#include<iostream>
using namespace std;
int main(void)
{
	int t;
	int i,j,k;
	int n;
	int min;
	int len;
	int sum;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n;
		k=n;
		len=0;
		while(k!=0){
			k=k/10;
			len++;
		}
		bool find=false;
		for(j=n-len*9;j<=n;j++)
		{
			k=j;
			sum=j;
			while(k!=0){
				sum=sum+k%10;
				k=k/10;
			}
			if(sum==n) {
				find=true;
				min=j;
				break;
			}
		
		}
		if(find==true)
			cout<<min<<endl;
		else 
			cout<<'0'<<endl;
	}
	return 0;
}


/*
 1<N<100000 
3 
216 
121 
2005

198 
0 
1979


*/