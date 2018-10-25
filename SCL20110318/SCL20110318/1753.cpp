#include<iostream>
#include<memory.h>
#include<stdlib.h>
#include<string>

using namespace std;
int main(void)
{
	string str;
	int i,j,l,k;
	int n;
	char num[100];
	char ch;
	int be;
	while(cin>>str,str!="XXX"){	
		memset(num,0,sizeof(char)*100);
		l=(int)str.size();
		k=0;
		
		for(i=0;i<l;i++)
		{
			if(str[i]>='0' && str[i]<='9') {
				num[k]=str[i];
				k++;
				if(i<l-1)
					continue;
			}
			n=atoi(num);
			if(n!=0){	
				str.erase(be+1,k);
				for(j=0;j<n-1;j++)
				{
					str.insert(be,1,ch);
				}
				l=l-k+n-1;
				i=i+n-1-k;
				memset(num,0,sizeof(char)*100);
				k=0;
			}
			ch=str[i];
			be=i;
		}
		cout<<str<<endl;
	}

	return 0;
}
/*
字符都是小写字母，数字表示字符出现次数N(1<=N<=10^4)；
a3
go12g4le
XXX



aaa
goooooooooooogle
*/