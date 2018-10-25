#include<iostream>
#include<memory.h>
#include<ctime>
using namespace std;

bool Prime[1000000];
int PrimeInd[1000000];

//筛选法求1~10000的素数  
//合数N的不等于1的最小正因数不大于N的平方根
//也就是说要判断10000是不是素数，只需判断在它100以内存不存在因子，存在因子的肯定不是素数
//所以反过来推理，让100以内的数作为因子，乘以倍数的便利，就可以把10000以内的合数跳出来
void PrimeTable()
{
	int i,j;
	memset(Prime,true,sizeof(Prime));
	Prime[0]=Prime[1]=false;
	for(i=2;i*i<=1000000;i++)
	{
		if(Prime[i]){ // 如果I是素数，求它的倍数肯定不是素数
			for(j=2;j*i<=1000000;j++)
			{
				Prime[i*j]=false;
			}
		}
	}
}

int main()
{	
	 PrimeTable();
	memset(PrimeInd,0,sizeof(int)*1000000);
	 int num=0;
	int j=0;
	for(j=0;j<1000000;j++)
	{
		if(Prime[j])
		{
			++num;
			PrimeInd[j]=num;
		}
	}
	int t;
	while(cin>>t,t!=-1)
		cout<<PrimeInd[t]<<endl;
	return 0;
}