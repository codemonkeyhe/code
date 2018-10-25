#include<iostream>
using namespace std;
int main(void)
{
	int m,n;
	int c;
	int i,j,k;
	while(cin>>m>>n)
	{
		int h=n;	
		j=0;
		int left=0;
		int down=1;
		while(1){
			c=n%m;	
			k=n/m;
			if(c==0 && left==0){
				j=j+k-1;
				if(k%2==0){
					 if(down==1)
						cout<<"D "<<j<<endl;
					else 
						cout<<"C "<<j<<endl;
				}else 
				{
					if(down==1)
						cout<<"C "<<j<<endl;
					else 
						cout<<"D "<<j<<endl;

				}
				break;
			}else if(c==0 && left==1){
				j=j+k-1;
				if(k%2==0){
					 if(down==1)
						cout<<"A "<<j<<endl;
					else 
						cout<<"B "<<j<<endl;
				}else
				{
					if(down==1)
						cout<<"B "<<j<<endl;
					else 
						cout<<"A "<<j<<endl;
				}
				break;
			}
			else{
				if(k%2==0)
					down=0;
				else 
					down=1;
				j=j+n/m+2;
				n=h-(m-c);
				left=(left+1)%2;
				//j=j+2;
				continue;
			}
		}
	
	}
	return 0;
}


/*
6 10


C 6

*/