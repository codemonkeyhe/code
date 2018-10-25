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
	for(int i=0;i<N;i++)//按照max上限分组，得到分数组x,如果M位于[x，N]之间，则直接输出max
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
		for( k=0;k<N;k++)//按照Mid上限分组，找出最大的组元素之和Max和分组数DivN
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

解题思路
7 X
1 4 3 1 5 1 4

数量N  组数x   最小的 组和最大值ME
7	1	19
7	2	10
7	3	8
7	4	5
7	5	5
7	6	5
7	7	5
目标，当数组x为M时具，求ME

ME随着M的增多而减少，具有单调性
ME的上界Rv是分成1组的情况，为所有元素之和sum
ME的下界Lv是分成N组的情况，即每个元素一组，最大值的元素Max(a[i])
则分组为M 的ME的解空间位于[Max(a[i]),sum],然后用二分法缩小解空间，直至Lv>=Rv
Mid=(Lv+Rv)/2视为新分组的最大值上限（贪心思想）将原数据分成x组，
若x<=M,表示用Mid做上限还可以继续分，可以缩小上限来增加分组数，则Rv=Mid,排除解空间（Mid，之前的Rv]，表示可以继续分。
若x>M，说明用Mid做上限分组太多，这个上限太小，可以增加上限来减少分组数，所以该排除解空间[Lv，Mid],解空间位于[Mid+1,Rv]。
直到Lv>=Rv，则结束。解空间就是Lv或者Rv






*/