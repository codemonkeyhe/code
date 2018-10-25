#include<iostream>
#include <stdio.h> 
#include<string>
using namespace std;
int main(void)
{
	int n;
	int i,j;
	cin>>n;
	//scanf("\n");
	cin.get();
	//fflush(stdin); //不能用这个，必须用scanf或者cin.get()，过滤掉缓冲区的回车字符
	string enco;
	string map;
	int dex;
	for(i=1;i<=n;i++){	
		getline(cin,enco);
		getline(cin,map);//必须用GETLINE，不能用CIN
		//cin>>map;
		for(j=0;j<(int)enco.size();j++)
		{
			if(enco[j]!=' '){
				dex=enco[j]-'A';
				enco[j]=map[dex];
			}		
		}
		cout<<i<<" "<<enco<<endl;
	}
	return 0;
}

    /* for(int i=0;i<s.length();i++)
        {
            if(isalpha(s[i]))
                s[i]=ch[s[i]-65];
        }*/



/*
 Only upper case letters will be used.
 Spaces may appear in the encoded message,
 and should be preserved in the output string. 

2 
HPC PJVYMIY 
BLMRGJIASOPZEFDCKWYHUNXQTV 
FDY GAI BG UKMY 
KIMHOTSQYRLCUZPAGWJNBVDXEF


1 ACM CONTEST 
2 THE SKY IS BLUE



*/