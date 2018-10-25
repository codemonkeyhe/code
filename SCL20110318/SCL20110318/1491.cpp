#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

string intochar(int num)
{
	string res("");
	while(num!=0){
		res.insert( res.begin(),1,num%10+'0');
		num=num/10;
	}
	return res;
}

int main(void)
{
	int n;
	string str;
	string::size_type head,tail;
	string res;
	cin>>n;
	char let[1000];
	while(n>0)
	{
		n--;
		res="";
		cin>>str;
		tail=head=0;
		while( (head=str.find_first_not_of(str[tail],tail))!=string::npos ){	
			res+=intochar(head-tail) ;
			res+=str[tail];
			tail=head;
		}
		res+=intochar(str.size()-tail);
		res+=str[tail];
		cout<<res<<endl;
	}
	return 0;
}



/*
sicily 不能识别 itoa 函数，得自己实现
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n,i,num;
    string s;
    cin>>n;
    while(n--)
    {
        cin>>s;
        string::iterator iter1,iter0 = s.begin();
        while(iter0!=s.end())
        {
            num = 1;
            for(iter1 = iter0+1;iter1!=s.end();iter1++)
            {
                if(*iter1 == *iter0)   { num++; continue; }
                else                     break;    
            }
            cout<<num<<*iter0;
            iter0+=num;
        }
        cout<<endl;
    }
    return 0;
}



  */                   