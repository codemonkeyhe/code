#include<iostream>
#include<algorithm>
using namespace std;

struct data
{
	int id;
	int yw;
	int sx;
	int en;
	int tol;
};

bool cmp(data s1,data s2)
{
	if(s1.tol>s2.tol) return true;
	if(s1.tol==s2.tol && s1.yw>s2.yw) return true;
	if(s1.tol==s2.tol && s1.yw==s2.yw &&s1.id<s2.id) return true;
	
	return  false;
}


int main(void)
{
	int i;
	int n;
	bool print=false;  
	while(cin>>n ){
		if(print)          
		cout<<endl;  
		data *stu=new data[n];
		for(i=0;i<n;i++)
		{
			cin>>stu[i].yw>>stu[i].sx>>stu[i].en;
			stu[i].id=i+1;
			stu[i].tol=stu[i].yw+stu[i].sx+stu[i].en;
		}
		sort(stu,stu+n,cmp);
		for(i=0;i<5;i++)
		{
			cout<<stu[i].id<<" "<<stu[i].tol<<endl;
		}
		//cout<<endl;
		print=true;
		delete []stu;
	}
	return 0;
}


/*
注意此题输出格式，最后一个案例不需要输出空行
6
90 67 80
87 66 91
78 89 91
88 99 77
67 89 64
78 89 98
8
80 89 89
88 98 78
90 67 80
87 66 91
78 89 91
88 99 77
67 89 64
78 89 98


6 265
4 264
3 258
2 244
1 237

8 265
2 264
6 264
1 258
5 258


*/




//#include<iostream>
//#include<algorithm>
//using namespace std;
//struct stu{    int id,w,s,y;    
//int total()    
//{        r
//eturn w+s+y;   
//}
//};
//bool comp_total(stu a,stu b){    
//	return a.total()>b.total()
//		;}
//bool comp_w(stu a,stu b){  
//	return a.w>b.w;}
//int main(){    int n;  
//bool print=false;    
//while( cin>>n && n )    {       
//	if(print)          
//		cout<<endl;     
//	stu *s=new stu[n];     
//	for(int i=0;i<n;i++)    
//	{           
//		s[i].id=i+1;    
//		cin>>s[i].w>>s[i].s>>s[i].y;   
//	}       
//	stable_sort(s,s+n,comp_w);   
//	stable_sort(s,s+n,comp_total);     
//	for(int i=0;i<5;i++)          
//		cout<<s[i].id<<" "<<s[i].total()<<endl;    
//	print=true;      
//	delete []s;   
//}   
//return 0;
//}