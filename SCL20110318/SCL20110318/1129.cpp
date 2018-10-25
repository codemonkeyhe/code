#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	int i,j,k;
	int sum;
	string str;
	char ch;
	while(cin>>str)
	{
		sum=0;
		j=10;
		int l=str.length();
		for(i=0;i<l;i++){
			if(str[i]!='-') { 
				ch=str[i];
				k=ch-'0';
				sum+=k*j;
				j--;
			}
		}
		i=sum%11;
		str=str+'-';
		if(i==0){str=str+'0';}
		else{
			i=11-i;
			if(i==10)
				str=str+'X';
			else{
				ch=i+'0';
				str=str+ch;
			}
		}
		cout<<str<<endl;
	
	}
	return 0;
}

/*
0-07-109219
0-534-95054
963-10-0604
1-890880-01


0-07-109219-6
0-534-95054-X
963-10-0604-2
1-890880-01-9


*/