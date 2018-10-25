#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool prime(int n)
{
	if(n < 2) 
		return false;
    if(n == 2) 
		return true;
    for(int i = 3; i*i <= n; i += 2)
        if(n%i == 0)
			return false;
    return true;
}


int main(void)
{
	string str;
	int i,j,k,l;
	char word[110];
	int maxn,minn;
	while(cin>>word)
	{
		str=word;
		l=(int)str.size();
		sort(word,word+l);
		maxn=0;
		minn=99999;
		j=1;
		for(i=0;i<l-1;i++)
		{
			
			if(word[i]==word[i+1]){
				j++;
				if(i!=l-2) continue;
			}
			if(maxn<j) maxn=j;
			if(minn>j) minn=j;
			j=1;
		}
		//cout<<maxn<<" "<<minn<<endl;
		if(prime(maxn-minn)){
			cout<<"Lucky Word"<<endl;
			cout<<maxn-minn<<endl;
		}else {
			cout<<"No Answer"<<endl;
			cout<<'0'<<endl;
		}
	}
	return 0;
}

/*
一次AC

输入有多组Case,每组Case只有一行，是一个单词，
其中只可能出现小写字母，并且长度小于100。


每组Case输出共两行，第一行是一个字符串，
假设输入的的单词是Lucky Word，那么输出“Lucky Word”，否则输出“No Answer”；
第二行是一个整数，如果输入单词是Lucky Word，输出maxn-minn的值，否则输出0。


error
Lucky Word
2



*/