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
				if(it!=stu.end()){	//�ҵ�
					stu.erase(it);
				}	
			//}
			stu.insert(map<string,char>::value_type(name,ch));	
		}
		for(j=0;j<m;j++)
		{
			cin>>name;
			 //Ҫ���ҵ�Key
			//����һ����Ŀ����(ʵ����ָ��)		
			it=stu.find(name);
			if(it!=stu.end()) {	//�ҵ�
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
90~100 Ϊ A;
80~89 Ϊ B;
70~79 Ϊ C;
60~69 Ϊ D;
0~59 Ϊ E;


����������ݲ��� 0~100 ��Χ��,�����һ��:��Score is error!����
 n(1<n<=15000)�� m(1<m<=10000)��n ��ʾѧ��������m ��ʾ��ѯ����
 �����п������ظ����ֵ�ѧ���������һ�γ��ֵĳɼ�Ϊ׼
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