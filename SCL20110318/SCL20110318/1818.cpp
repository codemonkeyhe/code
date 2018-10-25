#include<iostream>
#include<map>
#include<string>
using namespace std;
int main()
{
	int t;
	int n,m;
	int i,j;
	string name;
	int sco;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n>>m;
		map<string,char> stu;
		map<string,char>::iterator it;
		char ch;
		for(j=0;j<n;j++){
		
			cin>>name>>sco;
			if(sco>100 || sco <0 ) ch='X';
			else if(sco>=90 && sco <=100 ) ch='A';
			else if(sco>=80 && sco <=89 ) ch='B';
			else if(sco>=70 && sco <=79 ) ch='C';
			else if(sco>=60 && sco<=69) ch='D';
			else ch='E';
			//if(!stu.empty()){
				it=stu.find(name);
				if(it!=stu.end()){	//找到
					stu.erase(it);
				}	
			//}
			stu.insert(map<string,char>::value_type(name,ch));	
		}
		for(j=0;j<m;j++)
		{
			cin>>name;
			 //要查找的Key
			//定义一个条目变量(实际是指针)		
			it=stu.find(name);
			if(it!=stu.end()) {	//找到
				if(it->second=='X') 
					cout<<"Score is error!"<<endl;
				else 
					cout<<it->second<<endl;	
			}
		}
	}
	return 0;
}


/*
90~100 为 A;
80~89 为 B;
70~79 为 C;
60~69 为 D;
0~59 为 E;


如果输入数据不在 0~100 范围内,请输出一行:“Score is error!”。
 n(1<n<=15000)和 m(1<m<=10000)，n 表示学生个数，m 表示查询次数
 数据有可能有重复名字的学生，以最后一次出现的成绩为准
1
4 3
cigam 56
cxw 67
xzz 100
daxia 123
daxia
cigam
xzz


5 3
cigam 56
cxw 67
xzz 100
daxia 123
daxia 97
daxia
cigam
xzz

Score is error!
E
A
*/