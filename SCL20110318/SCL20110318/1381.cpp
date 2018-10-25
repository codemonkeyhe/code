#include<iostream>
#include<string>
using namespace std;


const int maxsize=400;
struct hp
{
    int len;
    int s[maxsize+1];
};

void multiplyh(const hp &a,const hp &b,hp &c) //高精度*高精度
{
    int i,j,len;
    for(i=1;i<=maxsize;i++) c.s[i]=0;
    for(i=1;i<=a.len;i++)
        for(j=1;j<=b.len;j++)
        {
            c.s[i+j-1]+=a.s[i]*b.s[j];
            c.s[i+j]+=c.s[i+j-1]/10;
            c.s[i+j-1]%=10;
        }
    len=a.len+b.len+1;
    while(len>1&&c.s[len]==0) len--;
    c.len=len;
}

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


void printhp(const hp &y)
{
    int i;
    for(i=y.len;i>=1;i--)
        cout<<y.s[i];
    cout<<endl;
}



int main(void)
{
	int t;
	string a,b;
	int i,j,k;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>a>>b;
		hp A;
		hp B;
		hp C;
		inputhp(A,a);
		inputhp(B,b);
		multiplyh(A,B,C);
		printhp(C);
	}
	return 0;
}


/*

(0<=a<=10^100, 0<=b<=10,000)
1
2 7

14

*/