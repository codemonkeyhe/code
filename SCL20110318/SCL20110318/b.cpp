#include<iostream>
#include<stdio.h>
#include<string>
#include<memory.h>
#include<algorithm>
using namespace std;

const int maxsize=1000;
struct hp
{
    int len;
    int s[maxsize+1];
};

void print(const hp &y)
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


void multiply10(hp &a)     //高精度*10
{
    int i;
    for(i=a.len;i>=1;i--)
        a.s[i+1]=a.s[i];
    a.s[1]=0;
    a.len++;
    while(a.len>1&&a.s[a.len]==0) a.len--;
}

int compare(const hp &a,const hp &b)
{
    int len;
    if(a.len>b.len) len=a.len;
    else len=b.len;
    while(len>0 && a.s[len]==b.s[len]) len--;
    if(len==0) return 0;
    else return a.s[len]-b.s[len];
}


void subtract(const hp &a,const hp &b,hp &c) //高精度减法c=a-b
{
    int i,len;
    for(i=1;i<=maxsize;i++) c.s[i]=0;
    if(a.len>b.len) len=a.len;
    else len=b.len;
    for(i=1;i<=len;i++)
    {
        c.s[i]+=a.s[i]-b.s[i];
        if(c.s[i]<0)
        {
            c.s[i]+=10;
            c.s[i+1]--;
        }
    }
    while(len>1&&c.s[len]==0) len--;
    c.len=len;
}



void divideh(const hp &a,const hp &b,hp &c,hp &d)//高精度/高精度{d为余数}
{
    hp e;
    int i,len;
    for(i=1;i<=maxsize;i++)
    {
        c.s[i]=0;
        d.s[i]=0;
    }
    len=a.len;
    d.len=1;
    for(i=len;i>=1;i--)
    {
        multiply10(d);
        d.s[1]=a.s[i];
        while(compare(d,b)>=0)
        {
            subtract(d,b,e);
            d=e;
            c.s[i]++;
        }
    }
    while(len>1&&c.s[len]==0) len--;
    c.len=len;
}

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

void outp(hp &y,hp &x)
{
	int i;
	y.len=x.len;
	for(i=0;i<maxsize;i++)
	{
		y.s[i]=x.s[i];
	}
}

void Setar(hp &arr,int num)
{
	int i=1;
	int k;
	while(num!=0){
		arr.s[i]=num%10;
		i++;	
		num=num/10;
	}
	arr.len=i-1;
	for(k=i;k<maxsize;k++)
	{
		arr.s[k]=0;
	}
}
	
void cal(unsigned long long int n,hp &p)
{
	hp k1;
	hp k2;
	hp k3;
	hp t1;
	unsigned long long int i=1;
	Setar(t1,1);
	Setar(k1,1);
	Setar(k2,2);
	while(i<n)
	{
		multiplyh(k1,k2,k3);
		outp(k1,k3);
		plushp(k2,t1,k3);//p2=p2+1;
		outp(k2,k3);
		i++;
	}
	outp(p,k1);
}



int main(void)
{
	int i,j,k;
	unsigned long long int n;
	unsigned long long int m;
	int t;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>n>>m;
		if(m<n/2) m=n-m;
		hp p1,p2,p3,p4,p5,p6;
	/*	cal(n,p1);
		cal(m,p2);
		cal(n-m,p3);
		multiplyh(p2,p3,p4);
		divideh(p1,p4,p5,p6);
		print(p5);*/
		cal2(n,m,p1);
		cal(m,p2);
		multiplyh(p1,p2,p3);
	}
	return 0;
}



/*
1
4 2


6


*/