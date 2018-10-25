#include<iostream>
using namespace std;

int calsum(int i,int dec)
{
	int sum=0;
	int j;
	while(i!=0)
	{
		j=i%dec;
		sum=sum+j;
		i=i/dec;
	}
	return sum;
}

int main(void)
{
	int i;
	for(i=2992;i<=9999;i++)
	{
		int c=calsum(i,10);
		if(c==calsum(i,16) && calsum(i,12)==c)
			cout<<i<<endl;

	}
	return 0;
}

/*
ÃëÉ±£¬Ò»´ÎAC
2992
2993
2994
2995
2996
2997
2998
2999


*/