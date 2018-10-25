#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;
bool cmp(char a,char b)
{
	return (a>b);
}


int main(void)
{
	int i,j,l;
	int t;
	int be,en;
	char num[120];
	string str;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>num;
		str=num;
		l=str.size();
		be=0;
		en=str.find('0');
		if(en==string::npos) {
			sort(num,num+l,cmp);
			cout<<num<<endl;
			continue;
		}
		while(1){
			sort(num+be,num+en,cmp);
			while(str[en]=='0') 
				en++;
			be=en;
			en=str.find('0',be);
			if(en==string::npos) {
				sort(num+be,num+l,cmp);
				break;
			}
		}
		cout<<num<<endl;	
	}
	return 0;
}

/*
No integer consists of more than 100 digits. 
3
1
123
1012400198

1
321
1042100981
*/