#include<iostream>
using namespace std;

unsigned long int Powmod( int a, int b,int c)
{
	if(b==0)
		return 1;
	unsigned long int res=Powmod((a*a)%c,b/2,c);
	if( (b & 1) != 0 )
	{
		res=(res*a)%c;
	}
	return res;
}

int main(void)
{
	int a,b,c;
	cin>>a>>b>>c;
	unsigned long int result;
	result=Powmod(a,b,c);
	cout<<result<<endl;
	return 0;
}


/*
1<=a,b<c<=32,768¡£
2 6 11

9



*/