#include<iostream>
#include<string>
using namespace std;
const int maxsize=110;
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
void printhp(const hp &y)
{
    int i;
    for(i=y.len;i>=1;i--)
        cout<<y.s[i];
    cout<<endl;
}

void plushp(const hp &a,const hp &b,hp &c) //高精度加法c=a+b
{
    int i,len;
    for(i=1;i<=maxsize;i++) c.s[i]=0;
    if(a.len>b.len) len=a.len;
    else len=b.len;
    for(i=1;i<=len;i++)
    {
        c.s[i]+=a.s[i]+b.s[i];
        if(c.s[i]>=10)
        {
            c.s[i]-=10;
            c.s[i+1]++;
        }
    }
    if(c.s[len+1]>0) len++;
    c.len=len;
}

void equa(hp &x,const hp &a)
{
	int i;
	x.len=a.len;
	for(i=0;i<=maxsize;i++){
		x.s[i]=a.s[i];
	}
}


int main(void)
{
	int n;
	int i,j,k;
	string str1;
	string str2;
	hp n1,n2,n3;
	while(cin>>n)
	{
		cin>>str1;
		inputhp(n1,str1);
		if(n==1 ) {printhp(n1);continue;}
		for(i=1;i<n;i++){
			cin>>str2;
			inputhp(n2,str2);
			plushp(n1,n2,n3);
			equa(n1,n3);
		}
		printhp(n1);

	}
	return 0;
}

/*
 N (N<=100000),    The sum will not exceed 10^100
3 1 2 3
1 123
2 1111111111111111111111111111111111 1111111111111111111111111111111111


6
123
2222222222222222222222222222222222

*/