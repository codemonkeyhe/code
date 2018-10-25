#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int main(void)
{
	int n;
	int i;
	string str;
	double num;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>num>>str;
		if(str=="kg"){ str="lb";num=num*2.2046;}
		else if(str=="lb"){ str="kg";num=num*0.4536;}
		else if(str=="l"){ str="g";num=num*0.2642;}
		else if(str=="g"){ str="l";num=num*3.7854;}
		printf("%d %.4f %s\n",i,num,str.c_str());
		//cout<<i<<" "<<num<<" "<<str<<endl;
	}
	return 0;
}

/*
a floating point (double precision) number, a space and the unit specification for the measurement to be converted. 
The unit specification is one of kg, lb, l, or g referring to kilograms, pounds, liters and gallons respectively. 
Type		Metric				English equivalent  
Weight		1.000 kilograms		2.2046 pounds  
			0.4536 kilograms	1.0000 pound  
Volume		1.0000 liter		0.2642 gallons  
			3.7854 liters		1.0000 gallon  


5 
1 kg 
2 l 
7 lb 
3.5 g 
0 l


1 2.2046 lb 
2 0.5284 g 
3 3.1752 kg 
4 13.2489 l 
5 0.0000 g


*/