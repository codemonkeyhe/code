#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool cmp(string st1,string st2)
{
	if(st1+st2<st2+st1)
		return true;
	else
		return false;
}

int main(void)
{
	int tesN;
	int strN;
	int i,j;
	cin>>tesN;
	for(i=0;i<tesN;i++)
	{
		cin>>strN;
		string *str=new string[strN];
		for(j=0;j<strN;j++)
		{
			cin>>str[j];
		}
		sort(str,str+strN,cmp);
		for(j=0;j<strN;j++)
		{
			cout<<str[j];
		}
		cout<<endl;
	}
	return 0;
}

////陷阱 bba不是最小组合，而是bab,所以不能用set的默认排序功能
//1
//2
//b
//ba
//
//
//#include<iostream>
//#include<string>
//#include<set>
//using namespace std;
//int main(void)
//{
//	int tesN;
//	int strN;
//	int i,j;
//	set<string> str;
//	set<string> ::iterator pos;
//	cin>>tesN;
//	for(i=0;i<tesN;i++)
//	{
//		str.clear();
//		string tmp;
//		cin>>strN;
//		for(j=0;j<strN;j++)
//		{
//			cin>>tmp;
//			str.insert(tmp);
//		}
//		for(pos=str.begin();pos!=str.end();pos++)
//		{
//			tmp=*pos;
//			cout<<tmp;
//		}
//		cout<<endl;
//	}
//	return 0;
//}

/*
3
3
a
ab
ac
4
ad
dsgg
decs
gre
2
sad
cd

2
2
b
ba
2
d
de


*/



