#include<iostream>
using namespace std;

int main(void)
{
	int N,M;
	cin>>N>>M;
	int sum=0;
	int max=0;
	int Lv=0,Rv=0,Mid=-1;
	int record[100000]={0};
	int DivN=0;
	for(int i=0;i<N;i++)
	{
		cin>>record[i];
		sum+=record[i];
		if(max<record[i])
			max=record[i];
	}
	int tmp=0;
	for(int i=0;i<N;i++)//����max���޷��飬�õ�������x,���Mλ��[x��N]֮�䣬��ֱ�����max
	{		
		tmp+=record[i];	
		if(tmp>max)
		{
			tmp=record[i];
			DivN++;
		}	
	}	
	if(M>DivN) {cout<<max<<endl; return 0;}
	Lv=max;
	Rv=sum;
	while(Lv<Rv)
	{
		Mid=(Lv+Rv)/2;	
		DivN=0;
		int k=0;
		sum=0;
		for( k=0;k<N;k++)//����Mid���޷��飬�ҳ�������Ԫ��֮��Max�ͷ�����DivN
		{		
			sum+=record[k];	
			if(sum>Mid)
			{
				sum=record[k];
				DivN++;
			}	
		}	
		DivN++;
		if(DivN<=M)
			Rv=Mid;
		else
			Lv=Mid+1;
	}//while
	cout<<Rv<<endl;
	return 0;	
}


/*
7 5
123
423
6345
1234
5075
1014
40

500

5 3
100
5
5
5
5


7 3
1
4
3
1
5
1
4

����˼·
7 X
1 4 3 1 5 1 4

����N  ����x   ��С�� ������ֵME
7	1	19
7	2	10
7	3	8
7	4	5
7	5	5
7	6	5
7	7	5
Ŀ�꣬������xΪMʱ�ߣ���ME

ME����M����������٣����е�����
ME���Ͻ�Rv�Ƿֳ�1��������Ϊ����Ԫ��֮��sum
ME���½�Lv�Ƿֳ�N����������ÿ��Ԫ��һ�飬���ֵ��Ԫ��Max(a[i])
�����ΪM ��ME�Ľ�ռ�λ��[Max(a[i]),sum],Ȼ���ö��ַ���С��ռ䣬ֱ��Lv>=Rv
Mid=(Lv+Rv)/2��Ϊ�·�������ֵ���ޣ�̰��˼�룩��ԭ���ݷֳ�x�飬
��x<=M,��ʾ��Mid�����޻����Լ����֣�������С���������ӷ���������Rv=Mid,�ų���ռ䣨Mid��֮ǰ��Rv]����ʾ���Լ����֡�
��x>M��˵����Mid�����޷���̫�࣬�������̫С�������������������ٷ����������Ը��ų���ռ�[Lv��Mid],��ռ�λ��[Mid+1,Rv]��
ֱ��Lv>=Rv�����������ռ����Lv����Rv






*/