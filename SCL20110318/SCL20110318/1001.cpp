#include<iostream>
#include<stdio.h>
using namespace std;
int main(void)
{
	char ch1,ch2;
	int n1,n2,n3;
	while(1){
		scanf("%c",&ch1);
			n2=1;
			n3=1;
		if(ch1!='0')
		{
			
			while(scanf("%c",&ch2),ch2!='\n')
			{			
				if((ch1=='1' && ch2>='0' && ch2<='9') || 
					(ch1=='2' && ch2>='0' && ch2<='6' ))
						n1=n2;
					else
						n1=0;
				if(ch2>='1' && ch2<='9') 
					n2=n3;
				else 
					if(ch2=='0')
					n2=0;
				n3=n2+n1;
				ch1=ch2;
			}	
			cout<<n3<<endl;
		}
		else break;
	}
	return 0;
}


