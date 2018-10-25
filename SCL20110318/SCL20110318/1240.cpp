#include<iostream>
using namespace std;
int main()
{
	int i,j,k;
	int n;
	int len;
	while(cin>>n,n!=0)
	{
		cout<<n<<": ";
		int dig[10];
		k=n;
		len=0;
		while(k!=0)
		{
			dig[len]=k%10;
			if(dig[len]>=5 && dig[len]<=9) dig[len]--;
			k=k/10;
			len++;
		}
		int sum=0;
		j=1;
		for(i=0;i<len;i++)
		{
			sum=sum+dig[i]*j;
			j=j*9;
		}
		cout<<sum<<endl;
	}
	return 0;
}


/*
a positive integer in the range 1..999999999 
13
15
2003
2005
239
250
1399
1500
999999
0



13: 12
15: 13
2003: 1461
2005: 1462
239: 197
250: 198
1399: 1052
1500: 1053
999999: 531440


*/