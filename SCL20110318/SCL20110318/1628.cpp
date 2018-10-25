#include<iostream>
#include<string>
#include<stdio.h>
#include<memory.h>
#include<algorithm>
using namespace std;

string num="0123456789";
string upAlp="ABCDEFGHIJKLMOPQRSTUVWXYZ";
string loAlp="abcdefghijklmnopqrstuvwxyz";
string op="+-";


void upchange(string str)
{
	int ind=0;
	while(1){
	ind=str.find_first_of(loAlp,ind);
	if(ind==string::npos)
		break;
	else
		str[ind]=str[ind]+32;
	}
}

void sortnum(string str)
{
	int ind=0;
	ind=str.find_first_of(num,0);

}


int cmpa(string str1,string str2)
{



	return 0;
}

int main(void)
{
	int i,j,k;
	int n;
	cin>>n;
	for(i=0;i<n;i++)
	{
		string str1,str2;
		cin>>str1>>str2;
		if(str1.find_first_of(num,0)==string::npos 
			&& str2.find_first_of(num,0)==string::npos )
		{
			if(str1<str2)	
				cout<<i+1<<" -1"<<endl;
			else if(str1>str2) 
				cout<<i+1<<" 1"<<endl; 
			else
				cout<<i+1<<" "<<endl;
		}
		upchange(str1);
		upchange(str2);
		sortnum(str1);
		sortnum(str2);
		j=cmpa(str1,str2);
		cout<<i+1<<" "<<j<<endl;
	}
	return 0;
}

/*
5 
x-3 X0001 
123-456-7890 123+456+7890 
xYz000123J XyZ+123j 
#$%^&*[]- abcdefgh 
Abc47jKL+00123 ABC+47jkL123




1 -1 
2 1 
3 0 
4 -1 
5 0



*/