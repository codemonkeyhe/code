#include<iostream>
#include<string>
using namespace std;
#define MAXL 450

struct hp
{
	int len;
	int s[MAXL];
};
	hp x;
void inputhp(hp &a,string str)
{
    int i;
    while(str[0]=='0' && str.size()!=1)
        str.erase(0,1);
    a.len=(int)str.size();
    for(i=1;i<=a.len;++i)
        a.s[i]=str[a.len-i]-48;
    for (i=a.len+1;i<=MAXL;++i)
        a.s[i]=0;
}

void dividehp(const hp &a,int b,int &d) //高精度/单精度{d为余数}
{
    int i,len;
    len=a.len;
    d=0;
    for(i=len;i>=1;i--)
    {
        d=d*10+a.s[i];
        d%=b;
    }
}


int main(void)
{
	int t;
	int n;
	int i,j;
	string str;
	cin>>t;
	for(i=0;i<t;i++){
		cin>>n;
		int *b=new int[n];
		int *d=new int[n];
		for(j=0;j<n;j++){
			cin>>b[j];
		}
		cin>>str;
		inputhp(x,str);
		for(j=0;j<n;j++){
			dividehp(x,b[j],d[j]);
		}
		j=0;
		cout<<"("<<d[j];
		for(j=1;j<n;j++){
			cout<<","<<d[j];
		}
		cout<<")"<<endl;
		delete []d;
		delete []b;
		
	}
	return 0;
}


/*

2

3
2 3 5
10

4
2 3 5 7
13


(0,1,0)
(1,1,3,6)



*/