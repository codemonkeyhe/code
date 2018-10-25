#include<iostream>
#include<memory.h>
#include<iomanip>
using namespace std;

#define MaxLen 13
float PowerInv[MaxLen];

inline bool func(float pi)
{
	++pi;
	float sum=0;
	float d=pi;
	for(int i=1;i<MaxLen;i++)
	{
		if(PowerInv[i]!=0)
			sum+=PowerInv[i]*d;
		d=d*pi;
	}
	if((sum-PowerInv[0])<0)
		return false;
	else 
		return true;
}

int main(void)
{
	int num;	
	int k=1;
	while(cin>>num,num!=-1){
		float Invest[MaxLen];
		memset(Invest,0,MaxLen*sizeof(float));
		memset(PowerInv,0,MaxLen*sizeof(float));
		int month=0;
		float inv=0.0;
		for(int i=0;i<num;i++)
		{
			cin>>month>>inv;
			Invest[month]=inv;
		}
		int p=0;
		cin>>p>>PowerInv[0];

			//生成对应的幂指数表
		for(int i=0;i<MaxLen;i++)
		{
			if(Invest[i]!=0)
				PowerInv[p-i+1]=Invest[i];
		}

		float Lx=0.0,Rx=1.0;
		float Mx=0.0;
		while(Rx-Lx>=0.000001)
		{
			Mx=(Lx+Rx)/2.0;
			if(func(Mx)){
				Rx=Mx;
			}
			else{
				Lx=Mx;
			}
		}
		if(k>1 )
			cout<<endl;
		cout<<"Case "<<k<<": ";
		cout<<fixed<<setprecision(5)<<Mx<<endl;
		cout.unsetf(ostream::floatfield);
		k++;
	}
	return 0;
}

/*
误区1：不用从文件i.in输入数据
易错:格式控制，精度控制Rx-Lx>=0.000001

2   1   100.00    3
100.00    4   210.00

3
1 100.00
2 50.00
5 200.00
7 358.41

  -1


Case 1: 0.01635

Case 2: 0.00520

*/