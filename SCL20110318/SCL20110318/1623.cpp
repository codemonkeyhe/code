#include<iostream>
using namespace std;



int GCF(int a,int b)
{
	if (b==0) return -1;
    if(a%b==0)
		return b;
    else
        return GCF(b,a%b);
}

//最小公倍数是两数乘积处于最大公约数


int main(void)
{
	int t;
	int i,j;
	int a,b;
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cin>>a>>b;
		j=GCF(a,b);
		cout<<i<<" "<<a*b/j<<" "<<j<<endl;	
	}
	return 0;
}

/*
 N , (1≤N≤1000
 (1≤a, b≤1000) 
3 
5 10 
7 23 
42 56

1 10 5 
2 161 1 
3 168 14


*/