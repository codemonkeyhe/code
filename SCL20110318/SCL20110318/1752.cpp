#include<iostream>
#include<memory.h>
#include<ctime>
using namespace std;

bool Prime[1000000];
int PrimeInd[1000000];

//ɸѡ����1~10000������  
//����N�Ĳ�����1����С������������N��ƽ����
//Ҳ����˵Ҫ�ж�10000�ǲ���������ֻ���ж�����100���ڴ治�������ӣ��������ӵĿ϶���������
//���Է�����������100���ڵ�����Ϊ���ӣ����Ա����ı������Ϳ��԰�10000���ڵĺ���������
void PrimeTable()
{
	int i,j;
	memset(Prime,true,sizeof(Prime));
	Prime[0]=Prime[1]=false;
	for(i=2;i*i<=1000000;i++)
	{
		if(Prime[i]){ // ���I�������������ı����϶���������
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