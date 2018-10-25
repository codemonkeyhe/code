#include<iostream>
#include<string>
#include<cmath>
using namespace std;
string change(int num)
{
	int i;
	string str;
	char ch;
	int k=num;
	while(k!=0)
	{
		i=k%3;
		ch=i+48;
		str.insert(0,1,ch);
		k=k/3;
	}
	bool car=false;
	for(i=str.length()-1;i>=0;i--)
	{
		if(str[i]=='2' ){
			if(car==false)
				str[i]='-';
			else
				str[i]='0';
			car=true;
		}
		else if(str[i]=='1' ){
			if(car==true)
				str[i]='-';
		}else if(str[i]=='0'){
			if(car==true){
				str[i]='1';
				car=false;
			}
		}
	}
	if(car==true) str.insert(0,1,'1');
	return str;
}

string oppo(string str)
{
	for(int i=0;i<(int)str.size();i++)
	{
		if(str[i]=='1') str[i]='-';
		else if(str[i]=='-') str[i]='1';
	}
	return str;
}


int main(void)
{
	int n;
	string res;
	while(cin>>n)
	{
		if(n==0){ cout<<"0"<<endl;continue;}
		else if(n>0){
			res=change(n);
		} 
		else{
			res=change((abs((double)n));
			res=oppo(res);
		}
		cout<<res<<endl;

	}
	return 0;
}


/*
一次AC。使用abs时，sicily上没有abs(int)，要强制转换(abs((double)n)，且头文件为cmath
10
-3


101
-0



*/