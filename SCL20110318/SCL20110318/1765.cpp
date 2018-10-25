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
һ��AC

�����ж���Case,ÿ��Caseֻ��һ�У���һ�����ʣ�
����ֻ���ܳ���Сд��ĸ�����ҳ���С��100��


ÿ��Case��������У���һ����һ���ַ�����
��������ĵĵ�����Lucky Word����ô�����Lucky Word�������������No Answer����
�ڶ�����һ��������������뵥����Lucky Word�����maxn-minn��ֵ���������0��


error
Lucky Word
2



*/