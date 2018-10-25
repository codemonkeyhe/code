#include<iostream>
#include<string>
#include<memory.h>
#include<algorithm>
#include<vector>
#include <assert.h>
using namespace std;
int main(void)
{
	int fri,sed;
	int i,j;
	while(cin>>fri,fri!=0)
	{
		cin>>sed;
		int count=fri;
		string tmp;
		string *fried=new string [fri];
		string *sender=new string[sed];
		for(i=0;i<fri;i++)
		{
			cin>>fried[i];
			for(j=0;j<(int)fried[i].length();j++)
				fried[i][j]=tolower(fried[i][j]);
		}
		for(i=0;i<sed;i++)
		{
			cin>>sender[i];
			for(j=0;j<(int)sender[i].length();j++)
				sender[i][j]=tolower(sender[i][j]);
		}
		sort(sender,sender+sed);
		for(i=0;i<fri;i++)
		{
			if(binary_search(sender,sender+sed,fried[i]))
			{
				count--;
			}
		}
		cout<<count<<endl;
		delete []sender;
		delete []fried;	
	}
	return 0;
}

////大神的SET集合版
//#include <iostream>
//#include <string>
//#include <set>
//#include <cstring>
//using namespace std;
//
//string tolowercase(char *a)
//{
//    int length = strlen(a);
//    for(int i = 0; i < length; i++)
//    {
//        if(a[i] < 93)
//           a[i] = a[i] + 'a'-'A';
//    }
//    return string(a);
//}
//char a[100];
//int main()
//{
//    while(true)
//    {
//    set<string> fri;
//    int n,m;
//    cin >> n;if(n == 0)return 0;
//    cin>>m;
//    for(int i = 0; i < n; i++)
//    {
//        cin >> a;
//        fri.insert(tolowercase(a));
//    }
//    for(int i = 0; i < m; i++)
//    {
//        cin >> a;
//        fri.erase(tolowercase(a));
//    }
//    cout << fri.size()<<endl;
//    }
//
//    return 0;
//}
// 


//string upChange(string tmp)
//{
//	int i;
//	for(i=0;i<(int)tmp.size();i++)
//	{
//		if(tmp[i]>=65 && tmp[i]<=90)
//			tmp[i]=tmp[i]+32;
//	}
//	return tmp;
//}




//注意读清楚题意，一是大小写不敏感，而是一个有重复，一个无重复
//bool *find=new bool[fri];
//memset(find,false,sizeof(find));  
//典型错误，find是一个指针，所有的指针都是4字节大小，所以sizeof(find)=4，而并不是想要的find数组的大小
//所以	bool *find=new bool[fri]; 
//delete []find;  没错
//但中间插上一句bool *find=new bool[fri]; 有错，因为初始化4个，回收5个。。
//若改为memset(find,false,fri*sizeof(bool));则没错

//sort(fried,fried+fri);

//for(i=0;i<sed;i++)
//{
//	if(binary_search(fried,fried+fri,sender[i]) && find[i]==false )
//	{
//		count--;
//		find[i]=true;
//	}
//
//	/*if(binary_search(fristr.begin(),fristr.end(),sender[i]))
//		count--;*/

//}

/*
(1<=n, m<=20000),会超时，得改进算法，先排序，然后二分查找
for(i=0;i<sed;i++)
{
for(j=0;j<fri;j++)
{
if(sender[i]==fried[j] && find[j]==false){
	fri--;
	find[j]=true;
	break;
}
}
}*/



/*
5 3
Inkfish
Henry
Carp
Max
Jericho
Carp
Max
Carp
3 5
Inkfish
Henry
Carp
carp
Jericho
MAX
heNrY
hh

2 0
Inkfish
Henry


8 9
Inkfish
Henry
Carp
Max
Jericho
HH
ASCs
dfgs
Carp
Max
Carp
Carp
Max
Carp
Carp
Max
Carp



0




3

*/