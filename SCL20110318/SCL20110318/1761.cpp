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
�������Ϊ10����ʶ����Ϊ��д��ĸX
���ÿ��Caseһ�У����������ISBN�����ʶ������ȷ����ô�����Right����
���򣬰��չ涨�ĸ�ʽ�������ȷ��ISBN���루�����ָ�����-������ 


0-670-82162-4


*/