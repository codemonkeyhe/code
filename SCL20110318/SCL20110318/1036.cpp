#include<iostream>
#include<string>
#include<algorithm>
#include<memory.h>
using namespace std;
int main(void)
{
	int i,j;
	string kw;
	while(cin>>kw,kw!="THEEND"){
		string text;
		cin>>text;
		int col=kw.length();
		int row=text.length()/col;
		char ** chang=new char*[row];
		for(i=0;i<row;i++)
		{
			chang[i]=new char[col];
		}
		int index=0;
		int k=0;
		char ch='A';
		while(1){
			while(ch<='Z'){
				index=kw.find(ch,index);
				if(index==string::npos) {	
					ch++;
					index=0;
					continue;
				}
				else {
					break;
				}
			}
			if(ch>'Z') break;
			for(i=0;i<row;i++)
			{
				chang[i][index]=text[k];
				k++;
			}
			index++;
		}
		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
				cout<<chang[i][j];
		cout<<endl;
		for(i=0;i<row;i++)
		{
			delete []chang[i];
			chang[i]=NULL;
		}
		delete []chang;
		chang=NULL;

	}
	return 0;
}

/*
Ò»´ÎAC
BATBOY
EYDEMBLRTHANMEKTETOEEOTH
HUMDING
EIAAHEBXOIFWEHRXONNAALRSUMNREDEXCTLFTVEXPEDARTAXNAARYIEX
THEEND


MEETMEBYTHEOLDOAKTREENTH
ONCEUPONATIMEINALANDFARFARAWAYTHERELIVEDTHREEBEARSXXXXXX


*/