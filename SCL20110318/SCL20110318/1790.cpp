#include<iostream>
#include<string>
using namespace std;

const int maxsize=1100;
struct hp
{
    int len;
    int s[maxsize+1];
};

void inputhp(hp &a,string str)
{
    int i;
    while(str[0]=='0' && str.size()!=1)
        str.erase(0,1);
    a.len=(int)str.size();
    for(i=1;i<=a.len;++i)
        a.s[i]=str[a.len-i]-48;
    for (i=a.len+1;i<=maxsize;++i)
        a.s[i]=0;
}

void dividehp(const hp &a,int b,hp &c,int &d) //高精度/单精度{d为余数}
{
    int i,len;
    for(i=1;i<=maxsize;i++) c.s[i]=0;
    len=a.len;
    d=0;
    for(i=len;i>=1;i--)
    {
        d=d*10+a.s[i];
        c.s[i]=d/b;
        d%=b;
    }
    while(len>1&&c.s[len]==0) len--;
    c.len=len;
}




int main(void)
{
	int i;
	int t;
	int d;
	string n,m;
	hp a,c;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n>>m;
		if(n!=m) {cout<<"NO"<<endl;continue;}
		inputhp(a,n);
		dividehp(a,11,c,d);
		if(d==0 ) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;	
	}
	return 0;
}
/*
YES 和NO是大写，不要打成Yes和No
 two integer N and M (0<=N, M<=101000), 
 You are suggested to input the number with string. 


3
1 1
11 11
22 11


NO
YES
NO



*/