#include<iostream>
#include<memory.h>
using namespace std;

bool Prime[1300000];

void PrimeTable()
{
	int i,j;
	memset(Prime,true,sizeof(Prime));
	Prime[0]=Prime[1]=false;
	for(i=2;i*i<=1300000;i++)
	{
		if(Prime[i]){ // 如果I是素数，求它的倍数肯定不是素数
			for(j=2;j*i<=1300000;j++)
			{
				Prime[i*j]=false;
			}
		}
	}
}

int main(void)
{
	PrimeTable();
	int n;
	int i;
	while(cin>>n,n!=0)
	{
		if(Prime[n]==true) cout<<"0"<<endl;
		else
		{
			i=1;
			while(!Prime[n-i]){
				i++;
			}
			while(!Prime[n])
			{
				i++;
				n++;
			}
			cout<<i<<endl;
		}
	
	}
	return 0;
}

/*

10
11
27
2
492170
0


4
0
6
0
114


*/