#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int gcdn(int a,int b){
	if(b)//b!=0时递归，用辗转相除发计算最大公约数
		return gcdn(b,a%b);
	return a;//b==0,此时a即为最大公约数
}


int main(void)
{
	double k;
	unsigned long int gcd,lcm;
	unsigned long int a,b,c;
	//int a,b,c;
	while(cin>>gcd>>lcm, gcd!=0 && lcm!=0)
	{
		if(gcd==lcm) {
			printf("0 %d %d\n",gcd,lcm);
			continue;
		}
		k=sqrt((double)gcd)*sqrt((double)lcm);
		c=(int)floor(k);
		while(c>=1){
			if((gcd%c*lcm%c)%c==0 && c!=k){
				a=c;
				b=gcd*lcm/c;
				if(gcdn(a,b)==gcd)
					break;
				else c--;
			}
			else{
				c--;
			}
		}
		printf("%d %d %d\n",b-a,a,b);
	}
	return 0;
}

/*
one line containing two integers, 
the GCD and the LCM, both are between [1, 10^9].
Input is ended by GCD = LCM = 0.


6 36
1 35
0 0


6 12 18
2 5 7


*/