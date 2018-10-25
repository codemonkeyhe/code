#include<iostream>
#include<string>
#include<cmath>
#include <vector>
#include<algorithm>
using namespace std;
int GrayCode[65536][16];
int main(void)
{
	int lim=1;

	for(int j=0;j<16;j++)
	{
		
		for(int i=0;i<lim*2;i++)
		{
			if(i<lim) 
				GrayCode[i][j]=0;
			else 
				graycode[i][j]=1;	
		}
		int k=lim*2;
		
		while(k<65536){
			for(int r=k;r<k*2;r++)
			{
				graycode[r][j]=graycode[2*k-r-1][j];
			}
			k=k*2;
		}
		lim=lim*2;
	}

	/*int n;
	while(cin>>n,n!=0)
	{
		string gray(n,'0');
		for(int i=gray.size()-1;i>=0;--i)
		{
			
		}
	
	}*/
	return 0;
}