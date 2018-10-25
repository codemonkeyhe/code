#include<iostream>
#include<memory.h>
#include<algorithm>
using namespace std;

int cal(int num)
{
	int len=1;
	while(num!=1)
	{
		if(num%2==1)
			num=3*num+1;
		else
			num=num/2;
		len++;
	}
	return len;
}


int main(void)
{
	int i,j,k;
	int h=0;
	cin>>i>>j;
	int len[10010];
	for(k=i;k<=j;k++)
	{
		len[h]=cal(k);
		h++;
	}
	sort(len,len+h);
	cout<<len[h-1]<<endl;
	return 0;
}



/*
0 < i ¡Ü j < 10,000
1 10


20

*/