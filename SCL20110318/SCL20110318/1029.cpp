#include<iostream>
using namespace std;
#define MAXLen 100
struct hp
{
	int len;
	int s[MAXLen];
};
hp arr[100];
hp f1,f2,f3;
void plusf(const hp &a,const hp &b,hp &c) //高精度加法c=a+b
{
    int i,len;
    for(i=1;i<=MAXLen;i++) c.s[i]=0;
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


void outp(hp &y,hp &x)
{
	int i;
	y.len=x.len;
	for(i=0;i<MAXLen;i++)
	{
		y.s[i]=x.s[i];
	}
}

void print(const hp &y)
{
    int i;
    for(i=y.len;i>=1;i--)
        cout<<y.s[i];
    cout<<endl;
}

void Setar(hp arr[],int num)
{
	int i=1;
	int k;
	int ind=num-1;
	while(num!=0){
		arr[ind].s[i]=num%10;
		i++;	
		num=num/10;
	}
	arr[ind].len=i-1;
	for(k=i;k<MAXLen;k++)
	{
		arr[ind].s[k]=0;
	}
}

int main()
{
	int m,d;
	int i;
	while(cin>>m>>d,m!=0 && d!=0)
	{
		for(i=1;i<=m;i++)
		{
			Setar(arr,i+1);
		}
		if(d<=m) {
			print(arr[d]);
			continue;
		}
		int k=1;
		outp(f1,arr[k]);
		outp(f2,arr[m]);
		i=m;
		while(i<d)
		{
			plusf(f1,f2,f3);
			i++;
			k++;
			outp(arr[i],f3);
			outp(f2,arr[i]);
			outp(f1,arr[k]);
		}
		print(f3);
	}
	return 0;
}




/*
借助于高精度模板
2 3
3 5
1 100
0 0


5
9
1267650600228229401496703205376

*/