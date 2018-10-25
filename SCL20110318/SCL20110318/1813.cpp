#include<iostream>
#include<string>
using namespace std;

int conver(string str,int m)
{
	int len=(int)str.size();
	int i;
	int sum=0;
	int k=1;
	int tmp;
	for(i=len-1;i>=0;i--)
	{
		if(str[i]>='0' && str[i]<='9') tmp=str[i]-48;
		else tmp=str[i]-55;
		sum=sum+tmp*k;
		k=k*m;
	}
	return sum;
}

string conts(int num,int m)
{
	string str;
	int k=num;
	int tmp=0;
	char ch;
	while(k!=0)
	{
		tmp=k%m;
		if(tmp>=0 &&tmp<=9) ch=tmp+48;
		else ch=tmp+55;
		str.insert(0,1,ch);
		k=k/m;
	}
	return str;
}

int main(void)
{
	int i;
	int t;
	int m;
	string n1,n2;
	cin>>t;
	for(i=0;i<t;i++)
	{
		cin>>m;
		cin>>n1>>n2;
		int num1=conver(n1,m);
		int num2=conver(n2,m);
			if(num2!=0){
				string res;
				int tmp=num1/num2;
				if(tmp==0) cout<<"0"<<endl;
				else {
				res=conts(tmp,m);
				cout<<res<<endl;
				}
				tmp=num1%num2;
				if(tmp==0) cout<<"0"<<endl;
				else{
					res=conts(tmp,m);
					cout<<res<<endl;
				}
			}
	}
	return 0;
}
	



/*
主要考虑0除以a的情况
所有 m 进制数的10进制表示均不超出int范围
1
16
29FA5
7

5FF3
0


*/

//#include <iostream>
//#include<string>
//using namespace std;
//
//long long divide(string , int);
//string combine(long long , int);
//
//int main()
//{
//    int xxxxxxxx;
//    cin >> xxxxxxxx;
//    while (xxxxxxxx != 0)
//    {
//        xxxxxxxx--;
//        int kk;
//        long long a,b,c,d;
//        cin >> kk;
//        string s1,s2;
//        cin>>s1;
//        a = divide(s1,kk);
//        cin >> s2;
//        b = divide(s2,kk);
//        c = a/b;
//        d = a%b;
//        s1 = combine(c,kk);
//        s2 = combine(d,kk);
//        cout << s1 << endl;
//        cout << s2 << endl;
//    }
//    return 0;
//}
//
//long long divide(string s , int k)
//{
//    int n = s.length();
//    int c = 1;
//    long long cc = 0;
//    for (int i = n-1 ; i >= 0 ; i--)
//    {
//        if (s[i]>= 'A' && s[i] <= 'Z') cc += (s[i]-55)*c;
//        else cc += (s[i]-48)*c;
//        c = c*k;
//    }
//    return cc;
//}
//
//string combine(long long c , int k)
//{
//    string ss = "";
//    int cc;
//    if (c == 0) return "0";
//    while (c != 0)
//    {
//        cc = c%k;
//        if (cc < 10) ss = (char)(cc+48) + ss;
//        else ss = (char)(cc+55) + ss;
//        c = c/k;
//    }
//    return ss;
//}
//
