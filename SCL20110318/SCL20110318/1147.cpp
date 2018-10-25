#include<iostream>
using namespace std;

struct data
{
	char name[22];
	int score;
	int clascore;
	char leader;
	char west;
	int lw;
	int money;
};


int main(void)
{
	int i;
	int stuN;
	int total=0;
	cin>>stuN;
	data* stu=new data[stuN];
	for(i=0;i<stuN;i++)
	{
		cin>>stu[i].name>>stu[i].score>>stu[i].clascore>>stu[i].leader>>stu[i].west>>stu[i].lw;
		stu[i].money=0;
	}
	for(i=0;i<stuN;i++)
	{
		if(stu[i].score>80 && stu[i].lw>=1 ) stu[i].money=stu[i].money+8000;
		if(stu[i].score>85 && stu[i].clascore>80 ) stu[i].money=stu[i].money+4000;
		if(stu[i].score>90 ) stu[i].money=stu[i].money+2000;
		if(stu[i].score>85 && stu[i].west=='Y' ) stu[i].money=stu[i].money+1000;
		if(stu[i].clascore>80 && stu[i].leader=='Y') stu[i].money=stu[i].money+850;
		total=total+stu[i].money;
	}
	int max=0;
	int id=0;
	for(i=0;i<stuN;i++)
	{
		if(max<stu[i].money) {
			max=stu[i].money;
			id=i;
		}	
	}
	cout<<stu[id].name<<endl;
	cout<<stu[id].money<<endl;
	cout<<total<<endl;
	delete []stu;
	return 0;
}




/*
¼òµ¥ Ò»´ÎAC
4
YaoLin 87 82 Y N 0
ChenRuiyi 88 78 N Y 1
LiXin 92 88 N N 0
ZhangQin 83 87 Y N 1


ChenRuiyi
9000
28700

*/