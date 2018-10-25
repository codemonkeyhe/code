#include<iostream>
#include<string>
using namespace std;
int main(void)
{
	int col;
	int i,j;
	string str;
	while(cin>>col,col!=0)
	{
		cin>>str;
		int row=str.length()/col;
		char** sen=new char*[row];
		for(i=0;i<row;i++)
		{
			sen[i]=new char[col];
		}
		for(i=0;i<row;i++)
		{				
			if(i%2==0){
				for(j=0;j<col;j++)
				{
					sen[i][j]=str[i*col+j];
				}
			}
			else
			{
				int end=(i+1)*col-1;
				for(j=0;j<col;j++)
				{
					sen[i][j]=str[end-j];
				}
			}
		}
		for(j=0;j<col;j++)
		{
			for(i=0;i<row;i++)
			{
				cout<<sen[i][j];
			}
		}
		cout<<endl;
		for(i=0;i<row;i++)
		{
			delete [col]sen[i];  //此行在sicily上应改为delete []sen[i]
			sen[i]=NULL;
		}
		delete []sen;
		sen=NULL;

	}
	return 0;
}



/*
5
toioynnkpheleaigshareconhtomesnlewx
3
ttyohhieneesiaabss
0



theresnoplacelikehomeonasnowynightx
thisistheeasyoneab




*/