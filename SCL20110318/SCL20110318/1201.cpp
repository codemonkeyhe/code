#include<iostream>
#include<string>
using namespace std;

#define maxsize 100


struct bina
{
	int len;
	int s[maxsize+1];
};

//void inputbi(bina & b, string & str)
//{
//	 int i;
//    while(str[0]=='0' && str.size()!=1)
//        str.erase(0,1);
//    b.len=(int)str.size();
//    for(i=1;i<=b.len;++i)
//        b.s[i]=str[b.len-i]-48;
//    for (i=b.len+1;i<=maxsize;++i)
//        b.s[i]=0;
//
//}

//void plusbi(const bina &a,const bina &b,bina &c) //高精度加法c=a+b
//{
//    int i,len;
//    for(i=1;i<=maxsize;i++) c.s[i]=0;
//    if(a.len>b.len) len=a.len;
//    else len=b.len;
//    for(i=1;i<=len;i++)
//    {
//        c.s[i]+=a.s[i]+b.s[i];
//        if(c.s[i]>=2)
//        {
//            c.s[i]-=2;
//            c.s[i+1]++;
//        }
//    }
//    if(c.s[len+1]>0) len++;
//    c.len=len;
//}


void inputbi(bina & b,string & str)    //有错,错在对数组的初始化，还有去0的判断
{
	int i=0;
	b.len=str.length();
	while(i<(int)str.length() && str[i]=='0')
	{
		i++;
		b.len--;
	}
	if(b.len==0) {b.len=1;}
	for(i=1;i<=b.len;i++)
	{
		b.s[i]=str[str.length()-i]-'0';
	}
	for(i=b.len+1;i<=maxsize;i++)
	{
		b.s[i]=0;
	}	
}


void plusbi(const bina &b1,const bina &b2 ,bina & b3)   //没错
{
	int i;
	int tmp;
	for(i=0;i<=maxsize;i++) b3.s[i]=0;
	b3.len=(b1.len>b2.len)? b1.len:b2.len;
	for(i=1;i<=b3.len;i++)
	{
		tmp=b1.s[i]+b2.s[i]+b3.s[i];
		if(tmp>=2) {
			b3.s[i+1]++;
			b3.s[i]=tmp-2;
		}
		else
			b3.s[i]=tmp;
	}
	if(b3.s[i]==1) b3.len++;
}

void printbi(const bina &b )
{
	int i;
	for(i=b.len;i>=1;i--)
	{
		cout<<b.s[i];
	}
	cout<<endl;
}

int main(void)
{
	int t;
	int i;
	string st1,st2;
	cin>>t;
	for(i=0;i<t;i++)
	{		
		cin>>st1>>st2;
		bina b1,b2,b3;
		inputbi(b1,st1);
		inputbi(b2,st2);
		plusbi(b1,b2,b3);
		cout<<i+1<<" ";
		printbi(b3);
	}
	return 0;
}





/*
The maximum length of each binary value is 80 bits (binary digits). 
Note: The maximum length result could be 81 bits (binary digits). 
留意000 000 
留意0010 00101

10 
1001101 10010 
1001001 11001 
1000111 1010110
0000 00
0 0
1 1
1 0
0 1




1 1011111 
2 1100010 
3 10011101

*/

//
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//int main()
//{
//    int t,i,j,a[100],b[100],c[100];
//    string s1,s2;
//    cin>>t;
//    for(i=1;i<=t;i++)
//    {
//        for(j=0;j<100;j++)
//        {
//            a[j]=0;
//            b[j]=0;
//            c[j]=0;
//        }
//        cin>>s1>>s2;
//        int len1=s1.length();
//        int len2=s2.length();
//        for(j=len1-1;j>=0;j--)
//            a[100+j-len1]=s1[j]-'0';
//        for(j=len2-1;j>=0;j--)
//            b[100+j-len2]=s2[j]-'0';
//  int max=(len1>len2)?len1:len2;
//  max = 99-max;
//        for(j=99;j>=max;j--)
//        {
//            c[j]=c[j]+a[j]+b[j];
//            if(c[j]>1)
//            {
//                 c[j]=c[j]%2;
//                 c[j-1]++;
//            }
//        }
//        cout<<i<<" ";
//        bool notzero = false;
//        for(j=0;j<100;j++)
//        {
//          if(c[j]!=0)
//              notzero = true;
//          if(notzero)
//             cout<<c[j];
//        }
//        if(!notzero)
//            cout<<0;
//        cout<<endl;
//    }
//    return 0;
//} 
//
//
//


