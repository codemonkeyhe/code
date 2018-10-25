#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	string isbn;
	int sum;
	char ch;
	while(cin>>isbn)
	{
		sum=(isbn[0]-'0')*1+(isbn[2]-'0')*2+(isbn[3]-'0')*3+(isbn[4]-'0')*4+(isbn[6]-'0')*5+(isbn[7]-'0')*6+(isbn[8]-'0')*7+(isbn[9]-'0')*8+(isbn[10]-'0')*9;										
		sum=sum%11;
		if(sum==10) ch='X';
		else ch=sum+'0';
		if(ch==isbn[12])
			cout<<"Right"<<endl;
		else{
			isbn[12]=ch;
			cout<<isbn<<endl;
		}
	
	}
	return 0;
}


/*
如果余数为10，则识别码为大写字母X
输出每个Case一行，假如输入的ISBN号码的识别码正确，那么输出“Right”，
否则，按照规定的格式，输出正确的ISBN号码（包括分隔符“-”）。 


0-670-82162-4


*/